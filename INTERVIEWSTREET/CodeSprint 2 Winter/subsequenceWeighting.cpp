/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
#include<algorithm>

class iTree
{
	private:
		static const int SIZE = 262144;
		long long int data[SIZE * 2];

	public:
		iTree(void);
		void clear(void);
		inline void update(const int &pos, const long long int &value);
		inline long long int getMax(const int &start, const int &end, const int &iStart = 0, const int &iEnd = SIZE - 1, const int &pos = 1);
};

inline static long long int MAX(const long long int &a, const long long int &b){return a>b?a:b;}

int tests,
	length,
	sequence[262144],
	value[262144];
std::pair<int, int> rebound[262144];
long long int result,
	 		  act;
iTree tree;
int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &length);
		for(int l = 0; l < length; ++ l)
		{
			scanf("%d", &sequence[l]);
			rebound[l] = std::make_pair(sequence[l], l);
		}

		std::sort(rebound, rebound + length);
		for(int l = 0, k = 1; l < length; ++ l)
		{
			if(l && rebound[l].first != rebound[l - 1].first)
				++ k;

			sequence[rebound[l].second] = k;
		}

		for(int l = 0; l < length; ++ l)
			scanf("%d", &value[l]);

		result = 0;
		tree.clear();
		for(int l = 0; l < length; ++ l)
		{
			act = tree.getMax(0, sequence[l] - 1)  + value[l];
			if(result < act)
				result = act;

			tree.update(sequence[l], act);
		}

		printf("%lld\n", result);
	}

	return 0;
}

iTree::iTree(void)
{
	this->clear();
}

void iTree::clear(void)
{
	for(int s = 0; s < 2 * this->SIZE; ++ s)
		this->data[s] = 0;

	return;
}

inline void iTree::update(const int &pos, const long long int &value)
{
	if(value <= this->data[SIZE + pos])
		return;

	this->data[SIZE + pos] = value;
	for(int p = (SIZE + pos) / 2; p > 0; p /= 2)
		this->data[p] = MAX(this->data[p * 2], this->data[p * 2 + 1]);

	return;
}

inline long long int iTree::getMax(const int &start, const int &end, const int &iStart, const int &iEnd, const int &pos)
{
	if(iStart == start && iEnd == end)
		return this->data[pos];

	const int iMiddle = (iStart + iEnd) / 2;
	if(end <= iMiddle)
		return this->getMax(start, end, iStart, iMiddle, pos * 2);

	if(start > iMiddle)
		return this->getMax(start, end, iMiddle + 1, iEnd, pos * 2 + 1);

	return MAX(this->getMax(start, iMiddle, iStart, iMiddle, pos * 2),
			   this->getMax(iMiddle + 1, end, iMiddle + 1, iEnd, pos * 2 + 1));
}
