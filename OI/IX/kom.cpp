/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...) 
#define inInterval(a, i) (preorder[a] >= preorder[i] && preorder[a] < preorder[i] + count[i])

int cities,
	start,
	end,
	trip,
	city,
	last,
	result,
	preorder[32768],
	count[32768],
	level[32768],
	order,
	speedup[32768][16];
std::vector<int> graph[32768];

void preprocess(void);
int LCA(int vertA, int vertB);
void dfs(int v, int l);

int main(void)
{
	scanf("%d", &cities);
	for(int c = 0; c < cities - 1; ++ c)
	{
		scanf("%d %d", &start, &end);
		-- end;
		-- start;
		graph[start].push_back(end);
		graph[end].push_back(start);
	}

	preprocess();
	last = 0;
	scanf("%d", &trip);
	for(int t = 0; t < trip; ++ t)
	{
		scanf("%d", &city);
		-- city;
		result += level[last] + level[city] - 2 * level[LCA(last, city)];
		last = city;
	}

	printf("%d\n", result);
	return 0;
}

void preprocess(void)
{
	dfs(0, 0);
	for(int l = 1, p = 2; p <= cities; p *= 2, ++ l)
		for(int c = 0; c < cities; ++ c)
			speedup[c][l] = speedup[speedup[c][l - 1]][l - 1];
}

void dfs(int v, int l)
{
	level[v] = l;
	preorder[v] = ++ order;
	for(unsigned int s = 0; s < graph[v].size(); ++ s)
		if(!preorder[graph[v][s]])
		{
			dfs(graph[v][s], l + 1);
			speedup[graph[v][s]][0] = v;
		}

	count[v] = order - preorder[v] + 1;
}

int LCA(int vertA, int vertB)
{
	if(inInterval(vertA, vertB))
		return vertB;

	if(inInterval(vertB, vertA))
		return vertA;

	for(int c = 1; !inInterval(vertA, vertB); ++ c)
		if(inInterval(vertA, speedup[vertB][c]))
		{
			vertB = speedup[vertB][c - 1];
			c = 0;
		}

	return vertB;
}
