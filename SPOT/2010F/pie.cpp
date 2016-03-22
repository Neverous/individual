/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	number;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &number);
		while(number >= 10)
			number /= 10;

		printf("%d\n", number);
	}

	return 0;
}

