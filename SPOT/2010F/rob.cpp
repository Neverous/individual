/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)
#define inInterval(a, i) (preorder[a] >= preorder[i] && preorder[a] < preorder[i] + count[i])

unsigned int tests,
			 actions,
			 verts,
			 vertex,
			 result[1000000],
			 res,
			 preorder[1000000],
			 count[1000000],
			 father[1000000],
			 order,
			 snail;
char action[2];
std::vector<unsigned int> tree[1000000];

inline static void dfs(int v);
inline static unsigned int moveSnail(unsigned int &destination);

int main(void)
{
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		/* CLEARING */
		for(unsigned int v = 0; v < verts; ++ v)
		{
			tree[v].clear();
			preorder[v] = 0;
			count[v] = 0;
			father[v] = 0;
		}

		res = 0;
		verts = 1;
		order = 0;
		snail = 0;

		/* SOLVING */
		scanf("%u", &actions);
		for(unsigned int a = 0; a < actions; ++ a)
		{
			scanf("%s %u", action, &vertex);
			-- vertex;
			if(action[0] == 'J')
				result[res ++] = vertex;

			else
				tree[vertex].push_back(verts ++);
		}

		dfs(0);
		for(unsigned int r = 0; r < res; ++ r)
			printf("%u\n", moveSnail(result[r]) + 1);
	}

	return 0;
}

inline static void dfs(int v)
{
	preorder[v] = ++ order;
	for(unsigned int n = 0; n < tree[v].size(); ++ n)
		if(!preorder[tree[v][n]])
		{
			dfs(tree[v][n]);
			father[tree[v][n]] = v;
		}

	count[v] = order - preorder[v] + 1;
}

inline static unsigned int moveSnail(unsigned int &destination)
{
	if(snail == destination)
		return snail;

	if(!inInterval(destination, snail))
		return snail = father[snail];

	unsigned int f = 0, t = tree[snail].size() - 1, mid;
	while(f != t)
	{
		mid = (f + t + 1) / 2;
		if(preorder[tree[snail][mid]] > preorder[destination])
			t = mid - 1;

		else
			f = mid;
	}

	return snail = tree[snail][f];
}

