#include "malloc.h"

void create_block(void *adr, size_t size, void *next, void *prev)
{
	t_mem_block *block = adr;

	block->size = size;
	block->is_free = true;
	block->next = next;
	block->previous = previous;
	block->next->previous = block;
	block->previous->next = block;
}

void *first_page(t_page *first, t_mem_block *first_block, size_t size)
{
	size_t mult = 1;
	size_t sizeblock = sizeof(t_mem_block);
	size_t sizepage = sizeof(t_page);

	while (PAGESIZE * mult < size + sizeblock + sizepage)
		mult += 1;
	first = mmap(adr, PAGESIZE * mult, PROT_NONE,
		MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	first->next = next;
	first->prev = prev;
	first->page_num = 1;
	first_block->size = size;
	first_block->is_free = false;
	first_block->previous = first_block;
	first_block->next = first_block;
	if (PAGESIZE * mult - (size + sizepage + sizeblock) > sizeblock)
	{
		create_block(size + sizepage + sizeblock,
			PAGESIZE * mult - (size + sizepage + sizeblock * 2),
			first_block, first_block);
	}
	return (first_block + sizeblock);
}

void *test_free(void *adr, size_t size, t_page *first, t_mem_block *first_block)
{

}

void *malloc(void *adr, size_t size)
{
	static t_mem_block *first_block;
	static t_page *first_page;

	if (!(first_page->next))
		return (first_page(first_page, first_block, size));
	else
		return(test_free(adr, size, first_page, first_block));
}
