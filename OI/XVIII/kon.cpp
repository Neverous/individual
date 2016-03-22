/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

const int BUFFER = 4096;
int p = BUFFER - 1;
char buffer[BUFFER];

unsigned int getNumber(void);

unsigned int verts,
			 count,
			 conspiracyToBe,
			 neighbours,
			 shuffle[5050];
bool good,
	 visited[5050];
std::vector<unsigned int> graph[5050],
	best,
	act;

inline static void find(unsigned int v);
inline static unsigned int dfs(unsigned int v);
inline static unsigned int MAX(unsigned int a, unsigned int b);

int main(void)
{
	srand(42);
	verts = getNumber();
	for(unsigned int v = 0; v < verts; ++ v)
	{
		shuffle[v] = v;
		neighbours = getNumber();
		for(unsigned int n = 0; n < neighbours; ++ n)
			graph[v].push_back(getNumber() - 1);
	}

	std::random_shuffle(shuffle, shuffle + verts);
	for(unsigned int v = 0; v < verts; ++ v)
		if(!visited[v])
			count = MAX(count, dfs(v));

	for(unsigned int v = 0; v < verts; ++ v)
		visited[v] = false;

	for(unsigned int v = 0; best.size() < count && v < verts; ++ v)
		find(shuffle[v]);

	for(unsigned int b = 0; b < best.size(); ++ b)
		visited[best[b]] = true;

	count = 0;
	for(unsigned int v = 0; v < verts; ++ v)
		if(!visited[v])
			count += dfs(v) > 1;

	if(count)
	{
		puts("0");
		return 0;
	}

	conspiracyToBe = best.size();
	if(conspiracyToBe == 1)
	{
		printf("%u\n", verts);
		return 0;
	}

	for(unsigned int v = 0; v < verts; ++ v)
		visited[v] = false;

	for(unsigned int b = 0; b < best.size(); ++ b)
		visited[best[b]] = true;

	if(best.size() > 2)
		for(unsigned int b = 0; b < best.size(); ++ b)
		{
			good = true;
			for(unsigned int n = 0; good && n < graph[best[b]].size(); ++ n)
				good = visited[graph[best[b]][n]];

			if(!good)
				-- conspiracyToBe;
		}


	printf("%u\n", conspiracyToBe + (conspiracyToBe != verts));
	return 0;
}

inline static void find(unsigned int v)
{
	act.clear();
	act.push_back(v);
	for(unsigned int n = 0; n < verts; ++ n)
	{
		if(n == v)
			continue;

		if(graph[n].size() < act.size())
			continue;

		good = true;
		for(unsigned int a = 0; good && a < act.size(); ++ a)
			good = std::binary_search(graph[n].begin(), graph[n].end(), act[a]);

		if(good)
			act.push_back(n);
	}

	if(act.size() > best.size())
		best = act;

	return;
}

inline static unsigned int dfs(unsigned int v)
{
	unsigned int res = 1;
	visited[v] = true;
	for(unsigned int n = 0; n < graph[v].size(); ++ n)
		if(!visited[graph[v][n]])
			res += dfs(graph[v][n]);

	return res;
}

inline static unsigned int MAX(unsigned int a, unsigned int b)
{
	return a>b?a:b;
}

unsigned int getNumber(void)
{
	unsigned int number = 0;
	while((buffer[p] < '0' || buffer[p] > '9') && ++ p)
		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
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

	return number;
}

