/* 2011
 * Maciej Szeptuch
 * -*-*-*-*-*-*-*-*-
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	hektor,
	wiktor;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d", &hektor, &wiktor);
		puts(hektor == wiktor?"REMIS":hektor<wiktor?"WIKTOR":"HEKTOR");
	}

	return 0;
}

