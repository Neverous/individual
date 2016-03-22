/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#define DEBUG(args...) fprintf(stderr, args)
//#define DEBUG(args...)

int tests,
	food,
	days,
	expire[2002],
	pieces[2002],
	quality[2002],
	result[2002][2002];

inline static int MAX(const int &A, const int &B);
bool compare(const int &A, const int &B);
int solve(void);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d", &food, &days);
		for(int f = 1; f <= food; ++ f)
			scanf("%d %d %d", &expire[f], &pieces[f], &quality[f]);

		printf("%d\n", solve());
	}

	return 0;
}

int solve(void)
{
	int best = 0;
	for(int f = 1; f <= food; ++ f)
		for(int d = 1; d <= days; ++ d)
		{
			result[f][d] = 0;
			if(d > expire[f])
				continue;

			for(int p = 1; p <= pieces[f] && p <= d; ++ p)
				for(int e = 0; e < f; ++ e)
					result[f][d] = MAX(result[f][d], result[e][d - p] + quality[f] * p);
		}

	for(int f = 0; f <= food; ++ f)
		best = MAX(best, result[f][days]);

	//for(int f = 0; f <= food; ++ f)
	//{
	//for(int d = 0; d <= days; ++ d)
	//DEBUG("%3d", result[f][d]);
	//
	//DEBUG("\n");
	//}

	return best;
}

inline static int MAX(const int &A, const int &B)
{
	return (int)(A>B?A:B);
}
