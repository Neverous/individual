/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int tests,
			 size,
			 steps;

int main(void)
{
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		scanf("%u %u", &size, &steps);
		if(size == 1)
			printf("%u", steps);
		else for(unsigned int s = 1, a = 2 * (size - 1), b = 0; s <= size; ++ s, b += 2, a -= 2)
			printf("%u ", (steps < s)?0:1 + (steps - s) / (a + b) * (a&&b?2:1) + (a&&b?(steps - s) % (a + b) >= a:0));

		puts("");
	}

	return 0;
}

