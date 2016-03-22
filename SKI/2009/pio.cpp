/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int tests,
	numbers,
	result,
	number;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d", &numbers, &result);
		result %= 2;
		for(int n = 1; n < numbers; ++ n)
		{
			scanf("%d", &number);
			result ^= number % 2;
		}

		printf("%s\n", result?"BOB":"ALICJA");

	}
}
