/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int villages,
			 paths,
			 from,
			 to,
			 visited[100010];
bool result;
std::vector<unsigned int> graph[100010];
inline static bool dfs(unsigned int &v, unsigned int f, unsigned int o);

int main(void)
{
	srand(42);
	scanf("%u %u", &villages, &paths);
	for(unsigned int p = 0; p < paths; ++ p)
	{
		scanf("%u %u", &from, &to);
		graph[from].push_back(to);
		graph[to].push_back(from);
	}

	for(unsigned int f = rand() % villages, s = 0; !result && s < 50; ++ s, f = rand() % villages)
	{
		for(unsigned int v = 0; v < villages; ++ v)
		{
			visited[v] = 0;
			random_shuffle(graph[v].begin(), graph[v].end());
		}

		result |= dfs(f, (1 << 30), 1);
		for(unsigned int v = 0; !result && v < villages; ++ v)
			result |= (!visited[v] && dfs(v, (1 << 30), 1));

	}

	printf("%s\n", result?"JEST":"BRAK");
	return 0;
}

inline static bool dfs(unsigned int &v, unsigned int f, unsigned int o)
{
	bool res = false;
	visited[v] = o;
	for(unsigned int n = 0; !res && n < graph[v].size(); ++ n)
	{
		if(graph[v][n] == f)
			continue;

		if(!visited[graph[v][n]])
			res |= dfs(graph[v][n], v, o + 1);

		else if((visited[v] - visited[graph[v][n]]) % 2)
			res = true;
	}

	return res;
}
