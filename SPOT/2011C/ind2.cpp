/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

const int BUFFER = 4096;
int p = BUFFER - 1;
char buffer[BUFFER];
 
int getInt(void)
{
	bool over = true;
	int number = 0;
	while((buffer[p] < '0' || buffer[p] > '9'))
	{
		if(buffer[p] == '-')
			over = false;
 
		++ p;
		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}
	}
 
	while(buffer[p] >= '0' && buffer[p] <= '9')
	{
		number = number * 10 + buffer[p] - '0';
		++ p;
 
		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}
	}
 
	return over?number:-number;
}
 
unsigned int tests,
			 verts,
			 edges,
			 start,
			 end,
			 result,
			 level[1048576];
bool visited[1048576];
std::vector<std::pair<unsigned int, unsigned int> > graph[1048576];
 
std::queue<unsigned int> que;
unsigned int act;
static inline void BFS(void);
static inline void DFS(const unsigned int &v, unsigned int l = 0);
static inline unsigned int MIN(const unsigned int &A, const unsigned int &B){return A<B?A:B;}
 
int main(void)
{
	//scanf("%u", &tests);
	tests = getInt();
	for(unsigned int t = 0; t < tests; ++ t)
	{
		//scanf("%u %u", &verts, &edges);
		verts = getInt();
		edges = getInt();
		result = 0;
		for(unsigned int v = 0; v < verts; ++ v)
		{
			visited[v] = false;
			graph[v].clear();
		}
 
		for(unsigned int e = 0; e < edges; ++ e)
		{
			//scanf("%u %u", &start, &end);
			start = getInt();
			end = getInt();
			-- start;
			-- end;
			graph[start].push_back(std::make_pair(end, e + 1));
			graph[end].push_back(std::make_pair(start, e + 1));
		}
 
		BFS();
		for(unsigned int v = 0; v < verts; ++ v)
		{
			visited[v] = false;
			level[v] = 0;
		}
 
		for(unsigned int n = 0; n < graph[0].size(); ++ n)
		{
			bzero(level, verts);
			DFS(graph[0][n].first);
			for(unsigned int lev = verts, temp; lev > 0; -- lev)
			{
				temp = MIN(level[lev], level[lev - 1]);
				result += temp;
				level[lev] -= temp;
				level[lev - 1] -= temp;
			}
			//puts("");
		}
 
		printf("%u\n", result);
	}
 
	return 0;
}
 
static inline void BFS(void)
{
	unsigned int best;
	que = std::queue<unsigned int>();
	que.push(0);
	visited[0] = true;
	while(!que.empty())
	{
		act = que.front();
		que.pop();
		best = 0;
		for(unsigned int n = 0; n < graph[act].size(); ++ n)
		{
			if(visited[graph[act][n].first])
			{
				if(level[graph[act][best].first] + 1 != level[act] || (level[act] == level[graph[act][n].first] + 1 && graph[act][best].second > graph[act][n].second))
					best = n;
 
				continue;
			}
 
			//printf("%u wrzucil %u\n", act, graph[act][n].first);
			level[graph[act][n].first] = level[act] + 1;
			visited[graph[act][n].first] = true;
			que.push(graph[act][n].first);
		}
 
		//printf("%u:\n", act);
		if(graph[act].size() && level[act] == level[graph[act][best].first] + 1)
		{
			//printf("%u <- %u\n", act, graph[act][best].first);
			for(unsigned int n = 0; n < graph[graph[act][best].first].size(); ++ n)
				if(act == graph[graph[act][best].first][n].first)
				{
					graph[graph[act][best].first][n].second = 0;
					break;
				}
		}
	}
 
	return;
}
 
static inline void DFS(const unsigned int &v, unsigned int l)
{
	//printf("->%u\n", v + 1);
	visited[v] = true;
	for(unsigned int n = 0; n < graph[v].size(); ++ n)
	{
		if(graph[v][n].second || visited[graph[v][n].first])
			continue;
 
		DFS(graph[v][n].first, l + 1);
		//puts("--");
	}
 
	++ level[l];
	return;
}
 
