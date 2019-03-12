#include "malloc.h"

int main(void)
{
	char *test;

	test = (char *)malloc(500);
	test[0] = 'e';
	return (0);
}
