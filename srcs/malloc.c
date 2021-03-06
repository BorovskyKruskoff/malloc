#include "malloc.h"

//creates a free block
void init_block(void *adr, size_t size, void *next, void *prev)
{
	t_mem_block *block = adr;

	write(1, "start block init\n", 17);
	block->size = size;
	block->is_free = true;
	block->next = next;
	block->prev = prev;
	block->next->prev = block;
	block->prev->next = block;
	write(1, "ended block init\n", 17);
}

//fills every field in the first page and its first block, and mmaps
void *init_first_page(t_page **first, t_mem_block **first_block, size_t size)
{
	size_t mult = 1;
	size_t sizeblock = sizeof(t_mem_block);
	size_t sizepage = sizeof(t_page);

	mult = ((size + sizeblock + sizepage) / PAGESIZE) + 1;
	*first = mmap(NULL, PAGESIZE * mult,
		PROT_WRITE | PROT_READ | PROT_EXEC,
		MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	(*first)->next = *first;
	(*first)->prev = *first;
	(*first)->size = PAGESIZE * mult;
	(*first)->page_num = 1;
	(*first_block) = (void *)(*first + sizepage);
	(*first_block)->size = size;
	(*first_block)->is_free = false;
	(*first_block)->prev = *first_block;
	(*first_block)->next = *first_block;
	if (PAGESIZE * mult - (size + sizepage + sizeblock) > sizeblock)
	{
		init_block((char *)(*first_block + sizeblock + size),
			PAGESIZE * mult - (size + sizepage + sizeblock * 2),
			*first_block, *first_block);
	}
	return (*first_block + sizeblock);
}

//creates a new page and its first block, and mmaps it
void *new_page(size_t size, t_page **old_page)
{
	t_mem_block *new_block;
	t_page *new_page;
	size_t mult = 1;
	size_t sizeblock = sizeof(t_mem_block);
	size_t sizepage = sizeof(t_page);

	mult = ((size + sizeblock + sizepage) / PAGESIZE) + 1;
	new_page = mmap(NULL, PAGESIZE * mult,
		PROT_WRITE | PROT_READ | PROT_EXEC,
		MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	new_page->next = (*old_page)->next;
	new_page->prev = *old_page;
	new_page->prev->next = new_page;
	new_page->next->prev = new_page;
	new_page->size = PAGESIZE * mult;
	new_page->page_num = new_page->prev->page_num + 1;
	new_block = (void *)(new_page + sizepage);
	new_block->size = size;
	new_block->is_free = false;
	new_block->next = new_block;
	new_block->next = new_block;
	if (PAGESIZE * mult - (size + sizepage + sizeblock) > sizeblock)
	{
		init_block((char *)(new_block + sizeblock + size),
			PAGESIZE * mult - (size + sizepage + sizeblock * 2),
			new_block, new_block);
	}
	return (new_block + sizeblock);
}

//occupy a free block with enough space
void take_block(t_mem_block *current, size_t size)
{
	size_t sizeblock = sizeof(t_mem_block);
	size_t size_left = current->size - size - sizeblock;

	write(1, "taking 1\n", 9);
	current->is_free = false;
	current->size = size;
	write(1, "taking 2\n", 9);
	if (size_left > sizeblock)
	{
		init_block((char *)(current + sizeblock + current->size), 
			size_left - sizeblock, current->next, current);
		write(1, "taking 3\n", 9);
	}
}

void *find_free_block(size_t size, t_page *first_page, t_mem_block *first_block)
{
	write (1, "start find free\n", 16);
	bool searching = true;
	t_page *test_page = first_page;
	t_mem_block *test_block = first_block;
	t_mem_block *start_block = first_block;

	while (searching)
	{
		//tests if block is free and big enough
		if (test_block->size >= size && test_block->is_free)
		{
			write (1, "free block found\n", 17);
			take_block(test_block, size);
			searching = false;
			return (test_block + sizeof(t_mem_block));
		}
		//goes to next block
		else if (test_block->next != start_block)
		{
			write (1, "goes next block\n", 16);
			test_block = test_block->next;
		}
		//goes to next page
		else if (test_page->next != first_page)
		{
			write (1, "goes next page\n", 15);
			test_page = test_page->next;
			start_block = (void *)(test_page + sizeof(t_page));
			test_block = start_block;
		}
		//stops searching and creates a new page
		else
			searching = false;
	}
	write (1, "create new page\n", 16);
	return (new_page(size, &first_page));
}

void *malloc(size_t size)
{
	static t_mem_block *first_block;
	static t_page *first_page;

	write(1, "KF\n", 3);
	if (!(first_page))
	{
		write(1, "First\n", 6);
		return (init_first_page(&first_page, &first_block, size));
	}
	else
	{
		write(1, "New\n", 4);
		return (find_free_block(size, first_page, first_block));
	}
}
