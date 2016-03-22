/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	size,
	seq[1048576],
	pal[1048576],
	ant[1048576];

inline static void solve(void);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &size);
		for(int s = 0; s < size; ++ s)
			scanf("%d", &seq[s]);

		solve();
	}

	return 0;
}

inline static void solve(void)
{
	for(int s = 0, e = size / 2; s < e; ++ s)
	{
		if((seq[s] + seq[size - 1 - s]) & 1)
		{
			puts("NIE");
			return;
		}

		pal[s] = pal[size - 1 - s] = (seq[s] + seq[size - 1 - s]) / 2;
		ant[size - 1 - s] = -(ant[s] = seq[s] - pal[s]);
	}

	for(int s = 0; s < size; ++ s)
		printf("%d ", pal[s]);

	puts("");
	for(int s = 0; s < size; ++ s)
		printf("%d ", ant[s]);

	puts("");
	return;
}
