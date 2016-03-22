/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	size,
	number,
	res;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &size);
		res = 0;
		for(int s = 0; s < size; ++ s)
		{
			scanf("%d", &number);
			res += number != s + 1;
		}

		printf("Case #%d: %d\n", t + 1, res);
	}

	return 0;
}

