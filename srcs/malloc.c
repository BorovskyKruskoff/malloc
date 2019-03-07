void *create_block(size_t size, void *adr, void *next, void *prev)
{
	t_mem_block *block;

	block = adr;
	block.size = size;
	block.is_free = true;
	block->next = next;
	block->previous = previous
	return (&block);
}

void initiate_linked_chain(struct mem_block first, void *adr, size_t size)
{
	int mult = 1;

	while (PAGESIZE * mult < size + sizeof(t_mem_block) + sizeof(t_page))
		mult += 1;
	&first = mmap(adr, PAGESIZE * page_mult, PROT_NONE,
		MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	first.size = size;
	if (PAGESIZE * page_mult - ((sizeof(t_mem_block) * 2) + size) > 0)
	{
		first->next = create_block((PAGESIZE * page_mult)
			- (size + sizeof(t_mem_block)), , &first, &first);
	}
	else
		first->next = &first;
	first->previous = first->next;
	first->is_free = false;
}

void *malloc(void *adr, size_t size)
{
	static t_mem_block *first;

	if (!(first->next))
		initiate_linked_chain(first, adr);
}
