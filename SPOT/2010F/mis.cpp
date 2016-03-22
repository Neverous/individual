/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	workers,
	level[100001],
	result;
int boss;
std::vector<int> tree[100001];

inline static void DFS(int v, int l = 0);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &workers);
		for(int w = 0; w < workers; ++ w)
		{
			scanf("%d", &boss);
			if(boss == -1)
				boss = 0;

			tree[boss].push_back(w + 1);
		}

		DFS(0);
		for(int l = 100000, rest = 0, more = 0; l >= 0; -- l)
		{
			if(level[l] > 1 && rest)
			{
				more = rest<level[l] - 1?rest:level[l] - 1;
				level[l] -= more;
				rest -= more;
				result += more;
			}

			result += level[l] / 2;
			rest += level[l] % 2;
		}

		printf("%d\n", result);
		for(int w = 0; w < 100001; ++ w)
		{
			tree[w].clear();
			level[w] = 0;
		}
		result = 0;

	}

	return 0;
}

inline static void DFS(int v, int l)
{
	++ level[l];
	for(unsigned int s = 0; s < tree[v].size(); ++ s)
		DFS(tree[v][s], l + 1);

	return;
}
