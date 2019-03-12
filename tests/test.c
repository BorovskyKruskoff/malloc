#include "malloc.h"

int main(void)
{
	char *test;

	test = (char *)malloc(100);
	for (int i = 0; i < 75; i++)
		test[i] = 'e';
	return (0);
}
