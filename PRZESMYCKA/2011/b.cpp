/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	n, s, k;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d %d", &n, &s, &k);
		puts((s >= k*(k + 1) / 2 && s <= (n*(n+1) - (n-k)*(n-k+1))/2)?"TAK":"NIE");
	}
	return 0;
}

