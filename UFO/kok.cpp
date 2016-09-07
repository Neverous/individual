/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int verts,
			 from,
			 to;
std::vector<unsigned int> graph[100010],
						  result;

void letsDoIt(unsigned int v, unsigned int f = -1);

int main(void)
{
	srand(42);
	scanf("%u", &verts);
	for(unsigned int v = 0; v < verts; ++ v)
		scanf("%*u");

	for(unsigned int e = 1; e < verts; ++ e)
	{
		scanf("%u %u", &from, &to);
		-- from;
		-- to;
		graph[from].push_back(to);
		graph[to].push_back(from);
	}

	for(unsigned int v = 0; v < verts; ++ v)
		random_shuffle(graph[v].begin(), graph[v].end());

	letsDoIt(0);
	printf("%u\n", (unsigned int)result.size());
	for(unsigned int r = 0; r < result.size(); ++ r)
		printf("%u%c", result[r], r + 1 == result.size()?'\n':' ');

	return 0;
}

void letsDoIt(unsigned int v, unsigned int f)
{
	result.push_back(v + 1);
	for(unsigned int c = 0; c < graph[v].size(); ++ c)
		if(graph[v][c] != f)
		{
			letsDoIt(graph[v][c], v);
			result.push_back(v + 1);
		}

	return;
}
