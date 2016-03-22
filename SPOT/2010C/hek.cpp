/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#define MIN(a, b) ((a) > (b)?(b):(a))

int tests,
	what,
	mod;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d", &mod, &what);
		printf("%d\n", MIN(what % mod, mod - what % mod));
	}

	return 0;
}

