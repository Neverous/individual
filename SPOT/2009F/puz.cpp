/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#define isNeighbour(a, b) ((a) == graph[b][0] || (a) == graph[b][1] || (a) == graph[b][2] || (a) == graph[b][3])

short int width,
		  height,
		  map[1001][1001],
		  a, b, c, d;
std::vector<short int> graph[1001];
bool solve(void);

int main(void)
{
	scanf("%hd %hd", &height, &width);
	for(short int p = 1; p <= width * height; ++ p)
	{
		scanf("%hd %hd %hd %hd", &a, &b, &c, &d);
		graph[p].push_back(a);
		graph[p].push_back(b);
		graph[p].push_back(c);
		graph[p].push_back(d);
	}

	scanf("%hd %hd", &map[1][1], &map[1][2]);
	if(!solve())
	{
		printf("NIE\n");
		return 0;
	}

	for(short int h = 1; h <= height; ++ h)
		for(short int w = 1; w <= width; ++ w)
			printf("%hd%c", map[h][w], w == width?'\n':' ');

	return 0;
}

bool solve(void)
{
	short int possible = 0;
	for(short int w = 3; w <= width; ++ w)
	{
		possible = 0;
		for(unsigned int s = 0; s < graph[map[1][w - 1]].size(); ++ s)
		{
			if(graph[map[1][w - 1]][s] != map[1][w - 2] && graph[map[1][w - 1]][s] && isNeighbour(0, graph[map[1][w - 1]][s]))
			{
				if(possible)
					return false;

				possible = graph[map[1][w - 1]][s];
			}
		}

		map[1][w] = possible;
	}
	
	for(short int h = 2; h <= height; ++ h)
		for(short int w = 1; w <= width; ++ w)
		{
			possible = 0;
			for(unsigned int s = 0; s < graph[map[h - 1][w]].size(); ++ s)
			{
				if(graph[map[h - 1][w]][s] != map[h - 1][w - 1] && graph[map[h - 1][w]][s] != map[h - 1][w + 1] && graph[map[h - 1][w]][s] != map[h - 2][w])
				{
					if(possible)
						return false;
	
					possible = graph[map[h - 1][w]][s];
				}
			}

			map[h][w] = possible;
		}

	return true;
}
