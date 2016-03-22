/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<queue>
#include<list>
#include<vector>
#define FIELD(number) std::pair<int,int>((number) / 1000, (number) % 1000)
#define REPR(a, b) ((a) * 1000 + (b))
#define ABS(a) ((a) > 0?(a):-(a))

int height,
	width,
	map[1024][1024],
	pumps;
bool dried[1048576],
	 pushed[1058576];
std::list<int> must[1024],
			   can[1024];
std::queue<int> que;
std::pair<int, int> act, pstart;

inline void bfsDry(int &start);

int main(void)
{
	scanf("%d %d", &height, &width);
	for(int h = 0; h < height; ++ h)
		for(int w = 0; w < width; ++ w)
		{
			scanf("%d", &map[h][w]);
			if(map[h][w] > 0)
				must[map[h][w]].push_back(REPR(h, w));

			map[h][w] = ABS(map[h][w]);
			dried[REPR(h, w)] = false;
			pushed[REPR(h, w)] = false;
		}

	for(int l = 1; l < 1001; ++ l)
	{
		for(std::list<int>::iterator i = can[l].begin(); i != can[l].end(); ++ i)
			if(!dried[*i])
				bfsDry(*i);

		for(std::list<int>::iterator i = must[l].begin(); i != must[l].end(); ++ i)
			if(!dried[*i])
			{
				++ pumps;
				bfsDry(*i);
			}
	}

	printf("%d\n", pumps);
	return 0;
}

inline void bfsDry(int &start)
{
	pstart = FIELD(start);
	que.push(start);
	dried[start] = true;

	while(!que.empty())
	{
		act = FIELD(que.front());
		que.pop();
		for(int h = -1; h < 2; ++ h)
			for(int w = (h&1) - 1; w < 2; w += 2)
			{
				if(act.first + h < 0 ||
						act.first + h > height - 1 ||
						act.second + w < 0 ||
						act.second + w > width - 1 ||
						pushed[REPR(act.first + h, act.second + w)] ||
						dried[REPR(act.first + h, act.second + w)])
					continue;

				if(map[act.first + h][act.second + w] > map[pstart.first][pstart.second])
					can[map[act.first + h][act.second + w]].push_back(REPR(act.first + h, act.second + w));

				else
				{
					dried[REPR(act.first + h, act.second + w)] = true;
					que.push(REPR(act.first + h, act.second + w));
				}

				pushed[REPR(act.first + h, act.second + w)] = true;
			}
	}

	return;
}
