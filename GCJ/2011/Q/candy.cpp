/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	numbers,
	number,
	res, sum, min;

inline static const int MIN(const int &a, const int &b){return a<b?a:b;}

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &numbers);
		res = sum = 0;
		min = 1048576;
		for(int n = 0; n < numbers; ++ n)
		{
			scanf("%d", &number);
			res ^= number;
			sum += number;
			min = MIN(min, number);
		}

		printf("Case #%d: ", t + 1);
		if(res)
			puts("NO");

		else
			printf("%d\n", sum - min);

	}

	return 0;
}

