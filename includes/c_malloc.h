#ifndef C_MALLOC
# define C_MALLOC

# define MEMSIZE = 5000
# include <sys/mman.h>

struct page
{
	size_t num;
	struct *page next;
	struct *page prev;
}

struct mem_block
{
	size_t page;
	size_t size;
	bool is_free;
	struct *mem_block prev;
	struct *mem_block next;
}

void * malloc(void *adr, size_t size);
//void * realloc(void *adr, size_t size);
//void * calloc(void *adr, size_t size);
//void free(void *adr);

#endif
