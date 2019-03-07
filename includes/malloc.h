#ifndef MALLOC
# define MALLOC

# include <sys/mman.h>

typedef struct page
{
	size_t page_num = 0;
	struct page *next;
	struct page *prev;
}t_page;

typedef struct mem_block
{
	size_t size;
	bool is_free;
	struct mem_block *prev;
	struct mem_block *next;
}t_mem_block;

void * malloc(void *adr, size_t size);
//void * realloc(void *adr, size_t size);
//void * calloc(void *adr, size_t size);
//void free(void *adr);

#endif
