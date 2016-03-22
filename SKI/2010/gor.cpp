/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int tests,
			 chambers,
			 entrance,
			 from,
			 to,
			 height,
			 miners,
			 result,
			 miner[200020],
			 cHeight[200020];
bool extraction[200020];
std::vector<unsigned int> toSort;
std::vector<std::pair<unsigned int, unsigned int> > graph[200020];

inline static unsigned int MIN(unsigned int &a, unsigned int &b);
inline static bool heightCompare(const unsigned int &A, const unsigned int &B);
inline static void setHeights(unsigned int &c, unsigned int f);

int main(void)
{
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		result = 0;
		toSort.clear();
		for(unsigned int c = 0; c < chambers; ++ c)
		{
			graph[c].clear();
			extraction[c] = false;
			cHeight[c] = 0;
		}

		scanf("%u %u", &chambers, &entrance);
		-- entrance;
		for(unsigned int c = 0; c < chambers - 1; ++ c)
		{
			scanf("%u %u %u", &from, &to, &height);
			-- from;
			-- to;
			graph[from].push_back(std::make_pair(to, height));
			graph[to].push_back(std::make_pair(from, height));
		}

		scanf("%u", &miners);
		for(unsigned int m = 0; m < miners; ++ m)
			scanf("%u", &miner[m]);

		std::sort(miner, miner + miners);
		cHeight[entrance] = 1000000;
		setHeights(entrance, 1000000);
		extraction[entrance] = false;
		for(unsigned int c = 0; c < chambers; ++ c)
			if(extraction[c])
				toSort.push_back(c);

		std::sort(toSort.begin(), toSort.end(), heightCompare);
		for(unsigned int c = 0, m = 0; m < miners && c < toSort.size();)
		{
			if(miner[m] <= cHeight[toSort[c]])
			{
				++ result;
				++ m;
			}

			++ c;
		}

		printf("%u\n", result);
	}
	return 0;
}

inline static bool heightCompare(const unsigned int &A, const unsigned int &B)
{
	return cHeight[A] < cHeight[B];
}

inline static void setHeights(unsigned int &c, unsigned int f)
{
	for(unsigned int n = 0; n < graph[c].size(); ++ n)
	{
		if(graph[c][n].first == f)
			continue;

		cHeight[graph[c][n].first] = MIN(cHeight[c], graph[c][n].second);
		setHeights(graph[c][n].first, c);
	}

	if(graph[c].size() == 1)
		extraction[c] = true;
}

inline static unsigned int MIN(unsigned int &a, unsigned int &b)
{
	return a<b?a:b;
}
