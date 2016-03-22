/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<list>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)
#define MIN(a, b) ((a) < (b)?(a):(b))

int stations,
	start,
	end,
	count[1048576],
	result;
unsigned int trains;
bool visited[1048576];
std::vector<int> graph[1048576];
std::list<int> *layer = new std::list<int>(),
			   *newLayer;

int main(void)
{
	scanf("%d %u", &stations, &trains);
	for(int s = 0; s < stations - 1; ++ s)
	{
		scanf("%d %d", &start, &end);
		-- start;
		-- end;
		++ count[start];
		++ count[end];
		graph[start].push_back(end);
		graph[end].push_back(start);
	}

	for(int s = 0; s < stations; ++ s)
		if(count[s] == 1)
		{
			visited[s] = true;
			layer->push_back(s);
		}

	while(!layer->empty())
	{
		result += MIN(2 * trains, layer->size());
		newLayer = new std::list<int>();
		for(std::list<int>::iterator l = layer->begin(); l != layer->end(); ++ l)
			for(unsigned int v = 0; v < graph[*l].size(); ++ v)
				if(!visited[graph[*l][v]])
				{
					-- count[graph[*l][v]];
					if(count[graph[*l][v]] == 1)
					{
						visited[graph[*l][v]] = true;
						newLayer->push_back(graph[*l][v]);
					}

					break;
				}

		delete layer;
		layer = newLayer;
	}

	printf("%d\n", result);
	return 0;
}

