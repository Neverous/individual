/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int number;

int main(void)
{
	scanf("%d", &number);
	printf("%d\n", number % 5);
	return 0;
}

