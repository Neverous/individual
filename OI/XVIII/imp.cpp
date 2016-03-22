/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int people,
	connections,
	start,
	end;
bool removed[3003];
std::vector<int> graph[3003];

int main(void)
{
	scanf("%d %d", &people, &connections);
	for(int c = 0; c < connections; ++ c)
	{
		scanf("%d %d", &start, &end);
		-- start;
		-- end;
		graph[start].push_back(end);
		graph[end].push_back(start);
	}

	for(int p = 0; p < people; ++ p)
		if(!removed[p])
		{
			std::sort(graph[p].begin(), graph[p].end());
			for(int s = 0, g = 0; s < people; ++ s) if(p != s)
			{
				while(g < graph[p].size() && graph[p][g] < s)
					++ g;

				if(!removed[s] && (g >= graph[p].size() || s != graph[p][g]))
				{
					removed[p] = removed[s] = true;
					break;
				}
			}
		}

	for(int p = 0, r = people / 3; p < people && r; ++ p)
		if(!removed[p])
		{
			printf("%d ", p + 1);
			-- r;
		}

	puts("");
	return 0;
}

