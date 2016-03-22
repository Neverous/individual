/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)
#define INSIDE(a, b) (b.first < a.first && b.second > a.second)

unsigned int tests,
			 bridges,
			 from,
			 to,
			 sortMe[8192];
std::pair<unsigned int, unsigned int> bridge[8192];

bool bridgeCompare(const unsigned int &A, const unsigned int &B);

int main(void)
{
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		scanf("%u", &bridges);
		for(unsigned int b = 0; b < bridges; ++ b)
		{
			scanf("%u %u", &bridge[b].first, &bridge[b].second);
			sortMe[b] = b;
		}

		std::sort(sortMe, sortMe + bridges, bridgeCompare);
		for(unsigned int s = 1, w = 1; s < bridges; w = ++ s)
		{
			for(unsigned int p = s; p && !INSIDE(bridge[sortMe[p - 1]], bridge[sortMe[s]]); -- p)
				if(sortMe[p - 1] > sortMe[s])
					w = p - 1;

			for(unsigned int p = s; p > w; -- p)
				std::swap(sortMe[p], sortMe[p - 1]);
		}

		for(unsigned int b = 0; b < bridges; ++ b)
			printf("%u%c", sortMe[b] + 1, b + 1 == bridges?'\n':' ');
	}

	return 0;
}

bool bridgeCompare(const unsigned int &A, const unsigned int &B)
{
	return bridge[A].second < bridge[B].second;
}
