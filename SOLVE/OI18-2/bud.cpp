/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int apartments,
	height,
	width,
	map[155][155],
	pref[155][155];

inline static int MAX(const int &a, const int &b){return a>b?a:b;}
inline static int MIN(const int &a, const int &b){return a<b?a:b;}
inline static int solve(const int &level, const int &start, const int &end, const int &left);

int main(void)
{
	scanf("%d %d %d", &apartments, &height, &width);
	for(int h = height; h; -- h)
		for(int w = 1; w <= width; ++ w)
		{
			scanf("%d", &map[h][w]);
			pref[h][w] = map[h][w] + pref[h][w - 1];
		}

	printf("%d\n", solve(1, 1, width, apartments));
	return 0;
}

inline static int solve(const int &level, const int &start, const int &end, const int &left)
{
	if(level > height || !left)
		return 0;

	int act,
		best = 0;

	for(int aps = 1; aps <= width && aps <= left; ++ aps)
		for(int p = MAX(1, start - aps + 1), e = MIN(width, end + aps - 1); p + aps - 1 <= e; ++ p)
		{
			act = pref[level][p + aps - 1] - pref[level][p - 1] + solve(level + 1, p, p + aps - 1, left - aps);
			if(act > best)
				best = act;
		}

	return best;
}
