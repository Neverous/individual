/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
#include<algorithm>
#include<vector>

class iTree
{
	private:
		static const long long unsigned int SIZE = 16384;
		std::pair<int, long long unsigned int> data[2 * SIZE];

	public:
		iTree(void);
		inline void clear(void);
		inline void update(const long long unsigned int &pos, const long long unsigned int &value);
		inline std::pair<long long unsigned int, long long unsigned int> getInterval(const long long unsigned int &start, const long long unsigned int &end, const long long unsigned int &iStart = 0, const long long unsigned int &iEnd = SIZE - 1, const long long unsigned int &pos = 1);
};


long long unsigned int tests,
	cities,
	population[262144],
	position[262144],
	sortMe[262144];
long long unsigned int result;
std::pair<long long unsigned int, long long unsigned int> act;
iTree tree;

inline static bool posCompare(const long long unsigned int &a, const long long unsigned int &b){return position[a] < position[b];}

int main(void)
{
	scanf("%llu", &tests);
	for(long long unsigned int t = 0; t < tests; ++ t)
	{
		scanf("%llu", &cities);
		for(long long unsigned int c = 0; c < cities; ++ c)
		{
			scanf("%llu", &position[c]);
			sortMe[c] = c;
		}

		for(long long unsigned int c = 0; c < cities; ++ c)
			scanf("%llu", &population[c]);

		result = 0;
		std::sort(sortMe, sortMe + cities, posCompare);
		tree.clear();
		for(long long unsigned int s = 0, c = sortMe[s]; s < cities; c = sortMe[++ s])
		{
			act = tree.getInterval(0, population[c]);
			result = (result + ((position[c] * act.first) % 1000000007 - act.second) * population[c]) % 1000000007;
			tree.update(population[c], position[c]);
		}

		tree.clear();
		for(long long int s = cities - 1, c = 0; s >= 0; -- s)
		{
			c = sortMe[s];
			act = tree.getInterval(0, population[c] - 1);
			result = (result + (act.second - (position[c] * act.first) % 1000000007) * population[c]) % 1000000007;
			tree.update(population[c], position[c]);
		}

		printf("%llu\n", result % 1000000007);
	}

	return 0;
}

iTree::iTree(void)
{
	this->clear();
}

inline void iTree::clear(void)
{
	for(long long unsigned int s = 0; s < 2 * this->SIZE; ++ s)
		this->data[s] = std::make_pair(0, 0);

	return;
}

inline void iTree::update(const long long unsigned int &pos, const long long unsigned int &value)
{
	for(long long int p = this->SIZE + pos; p > 0; p /= 2)
	{
		++ this->data[p].first;
		this->data[p].second += value;
		this->data[p].second %= 1000000007;
	}

	return;
}

inline std::pair<long long unsigned int, long long unsigned int> iTree::getInterval(const long long unsigned int &start, const long long unsigned int &end, const long long unsigned int &iStart, const long long unsigned int &iEnd, const long long unsigned int &pos)
{
	if(iStart == start && iEnd == end)
		return this->data[pos];

	const long long unsigned int iMiddle = (iStart + iEnd) / 2;
	if(end <= iMiddle)
		return this->getInterval(start, end, iStart, iMiddle, pos * 2);

	if(start > iMiddle)
		return this->getInterval(start, end, iMiddle + 1, iEnd, pos * 2 + 1);

	std::pair<long long unsigned int, long long unsigned int> a = this->getInterval(start, iMiddle, iStart, iMiddle, pos * 2),
								  b = this->getInterval(iMiddle + 1, end, iMiddle + 1, iEnd, pos * 2 + 1);

	return std::make_pair(a.first + b.first, (a.second + b.second) % 1000000007);
}
