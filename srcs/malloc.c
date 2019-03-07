#include "malloc.h"

void create_block(void *adr, size_t size, void *next, void *prev)
{
	t_mem_block *block = adr;

	block->size = size;
	block->is_free = true;
	block->next = next;
	block->previous = previous
}

void *first_page(t_page *first, t_page *next, t_page *prev size_t size)
{
	void *return_adr;
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
	create_block(first + sizepage, size);
}

void *malloc(void *adr, size_t size)
{
	static t_page *first;

	if (!(first->next))
		new_page(first, first, first, size);
}
