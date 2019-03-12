#ifndef MALLOC
# define MALLOC

# ifndef PAGESIZE
#  define PAGESIZE 4096
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/mman.h>
# include <stddef.h>

typedef struct page
{
	size_t page_num;
	size_t size;
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

void * malloc(size_t size);
//void * realloc(void *adr, size_t size);
//void * calloc(void *adr, size_t size);
//void free(void *adr);

#endif
