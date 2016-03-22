/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int tests,
			 number;

int main(void)
{
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		scanf("%u", &number);
		while(number % 2 == 0)
			number /= 2;

		printf("%s\n", number == 1?"TAK":"NIE");
	}

	return 0;
}

