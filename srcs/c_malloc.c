void *create_block(size_t size, void *adr, void *next, void *prev)
{
	struct mem_block block;

	&block = adr;
	block.size = size;
	block.is_free = true;
	block->next = next;
	block->previous = previous
	return (&block);
}

void initiate_linked_chain(struct mem_block first, void *adr, size_t size)
{
	if (size > MEMSIZE)
		&first = mmap(adr, size,
			PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	else
		&first = mmap(adr, MEMSIZE,
			PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	first.size = size;
	if (size < MEMSIZE)
	{
		first->next = create_block(MEMSIZE - size, , &first, &first)
	
	}
	first->next = &first;
	first->previous = &first;
}

void *malloc(void *adr, size_t size)
{
	static struct mem_block first;

	if (!(first->next))
		initiate_linked_chain(first, adr);
}
