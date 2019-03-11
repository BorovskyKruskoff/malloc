#include "malloc.h"

void create_block(void *adr, size_t size, void *next, void *prev)
{
	t_mem_block *block = adr;

	block->size = size;
	block->is_free = true;
	block->next = next;
	block->prev = prev;
	block->next->prev = block;
	block->prev->next = block;
}

void *create_first_page(t_page *first, t_mem_block *first_block, size_t size)
{
	size_t mult = 1;
	size_t sizeblock = sizeof(t_mem_block);
	size_t sizepage = sizeof(t_page);

	while (PAGESIZE * mult < size + sizeblock + sizepage)
		mult += 1;
	first = mmap(first, PAGESIZE * mult, PROT_NONE,
		MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	first->next = first;
	first->prev = first;
	first->size = PAGESIZE * mult;
	first->page_num = 1;
	first_block = (void *)(first + sizepage);
	first_block->size = size;
	first_block->is_free = false;
	first_block->prev = first_block;
	first_block->next = first_block;
	if (PAGESIZE * mult - (size + sizepage + sizeblock) > sizeblock)
	{
		create_block((char *)(first_block + sizeblock + size),
			PAGESIZE * mult - (size + sizepage + sizeblock * 2),
			first_block, first_block);
	}
	return (first_block + sizeblock);
}

void *new_page(size_t size, t_page *old_page)
{
	t_mem_block *new_block;
	t_page *new_page;
	size_t mult = 1;
	size_t sizeblock = sizeof(t_mem_block);
	size_t sizepage = sizeof(t_page);

	while (PAGESIZE * mult < size + sizeblock + sizepage)
		mult += 1;
	new_page = mmap(NULL, PAGESIZE * mult, PROT_NONE,
		MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	new_page->next = old_page->next;
	new_page->prev = old_page;
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
		create_block((char *)(new_block + sizeblock + size),
			PAGESIZE * mult - (size + sizepage + sizeblock * 2),
			new_block, new_block);
	}
	return (new_block + sizeblock);
}

void take_block(t_mem_block *current, size_t size)
{
	size_t sizeblock = sizeof(t_mem_block);
	size_t size_left = current->size - size - sizeblock;

	current->is_free = false;
	current->size = size;
	if (size_left > sizeblock)
	{
		create_block((char *)(current + sizeblock + current->size), 
			size_left - sizeblock, current->next, current);
	}
}

void *test_free(size_t size, t_page *first_page, t_mem_block *first_block)
{
	bool searching = true;
	t_page *test_page = first_page;
	t_mem_block *test_block = first_block;
	t_mem_block *start_block = first_block;

	while (searching)
	{
		if (test_block->size >= size && test_block->is_free == true)
		{
			take_block(test_block, size);
			searching = false;
			return (test_block + sizeof(t_mem_block));
		}
		else if (test_block->next != start_block)
			test_block = test_block->next;
		else if (test_page->next != first_page)
		{
			test_page = test_page->next;
			start_block = (void *)(test_page + sizeof(t_page));
			test_block = start_block;
		}
		else
			searching = false;
	}
	return (new_page(size, first_page));
}

void *malloc(size_t size)
{
	static t_mem_block *first_block;
	static t_page *first_page;

	if (!(first_page->next))
		return (create_first_page(first_page, first_block, size));
	else
		return (test_free(size, first_page, first_block));
}
