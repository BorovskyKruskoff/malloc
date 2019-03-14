#include "malloc.h"
#include "unistd.h"

int main(void)
{
	char *lol;
	char *test;

	test = (char *)malloc(100);
	write(1, "malloc done\n", 12);
	for (int i = 0; i < 99; i++)
		test[i] = 'e';
	write(1, "things put in\n", 14);
	lol = (char *)malloc(350);
	lol[0] = 'o';
	return (0);
}
