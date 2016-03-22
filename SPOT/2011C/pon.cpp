/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int tests,
			 year,
			 week,
			 started;

int main(void)
{
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		scanf("%u %u %u", &year, &week, &started);
		printf("%u\n", (year - (week + 1 - started) % week + week - 1) / week);
	}

	return 0;
}

