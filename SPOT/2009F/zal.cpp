/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#define MAP(a) map[(a).second.first][(a).second.second]
#define ABS(a) ((a) > 0?(a):-(a))
 
using namespace std;
 
int height,
	width,
	actLevel,
	result,
	actFlooded,
	map[1002][1002];
bool visited[1002][1002];
priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > que;
pair<int, pair<int, int> > act;
 
int main(void)
{
	scanf("%d %d", &height, &width);
	for(int h = 0; h <= height + 1; ++ h)
		for(int w = 0; w <= width + 1; ++ w)
			map[h][w] = -20000;
 
	for(int h = 1; h <= height; ++ h)
		for(int w = 1; w <= width; ++ w)
		{
			scanf("%d", &map[h][w]);
			if(map[h][w] == 0)
			{
				visited[h][w] = true;
				que.push(make_pair(0, make_pair(h, w)));
			}
		}
 
	while(!que.empty())
	{
		act = que.top();
		que.pop();
 
		if(act.first > actLevel)
		{
			result = actFlooded;
			actLevel = MAP(act);
		} // ITS A TRAP!!!
 
		if(MAP(act) < 0)
			break; // ITS A TREE!!!
 
		MAP(act) = 0;
		++ actFlooded;
 
		for(int i = -1; i < 2; ++ i)
			for(int j = ABS(i) - 1; j < 2; j += 2)
			{
				if(act.second.first + i < 0
				  || act.second.second + j < 0
				  || act.second.first + i > height
				  || act.second.second + j > width
				  || visited[act.second.first + i][act.second.second + j])
					continue;
 
				visited[act.second.first + i][act.second.second + j] = true;
				que.push(make_pair(ABS(map[act.second.first + i][act.second.second + j]), make_pair(act.second.first + i, act.second.second + j)));
			}
	}
 
	printf("%d\n", result);
	return 0;
}

