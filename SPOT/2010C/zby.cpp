/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

void solve(void);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &size);
		for(int s = 0; s < size; ++ s)
		{
			scanf("%d", &need[s]);
		}

		solve();
	}

	return 0;
}

void solve(void)
{
	int lines = 0;
	for(int v = 0; v < size; ++ v)
	{
	}
}
