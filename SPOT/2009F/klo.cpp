/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#define max(a, b) ((a) > (b)?(a):(b))

int tests,
	size,
	window,
	result;
char word[1000002];

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d %s", &size, &window, word);
		result = 0;
		for(int s = 0, e = 0, act = 0; s <= e && e < size;)
		{
			for(; e < size && act <= window; ++ e)
				act += word[e] == 'K';

			result = max(result, e - s - (act > window));
			for(; s <= e && act > window; ++ s)
				act -= word[s] == 'K';
		}

		printf("%d\n", result);
	}

	return 0;
}
