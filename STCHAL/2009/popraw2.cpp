/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)
#define MIN(a, b) ((a) < (b)?(a):(b))

int number;

int main(void)
{
	scanf("%d", &number);
	printf("%d\n", MIN(number % 5, 5 - (number % 5)));
	return 0;
}

