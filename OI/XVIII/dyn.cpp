/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<cstdlib>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int shelves,
	maxShots,
	shots,
	start,
	end,
	mid;
bool dynamite[300003];
std::vector<int> graph[300003];

inline static const std::pair<int, int> shootEmAll(const int &v, const int &range, const int &father = -1);

int main(void)
{
	srand(1510);
	scanf("%d %d", &shelves, &maxShots);
	for(int s = 0; s < shelves; ++ s)
		scanf("%d", &dynamite[s]);

	for(int s = 1; s < shelves; ++ s)
	{
		scanf("%d %d", &start, &end);
		-- start;
		-- end;
		graph[start].push_back(end);
		graph[end].push_back(start);
	}

	start = 0;
	end = shelves / 2;
	while(start < end)
	{
		mid = (start + end) / 2;
		shots = 0;
		shots += shootEmAll(rand() % shelves, mid, -1).first > 0;
		if(shots <= maxShots)
			end = mid;

		else
			start = mid + 1;
	}

	printf("%d\n", start);
	return 0;
}

inline static const std::pair<int, int> shootEmAll(const int &v, const int &range, const int &father)
{
	std::pair<int, int> res(dynamite[v]?0:-300003, 300003), // maxbomb, minshot
						temp;

	for(unsigned int n = 0; n < graph[v].size(); ++ n)
		if(graph[v][n] != father)
		{
			temp = shootEmAll(graph[v][n], range, v);
			if(temp.first > res.first)
				res.first = temp.first;

			if(temp.second < res.second)
				res.second = temp.second;
		}

	if(range - res.second >= res.first)
		res.first = -300003;

	if(res.first == range)
	{
		++ shots;
		res.first = -300003;
		res.second = 0;
	}

	++ res.first;
	++ res.second;
	return res;
}
