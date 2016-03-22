/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
#include<set>


class iTree
{
	private:
		static const int SIZE = 131072;
		int size,
			data[SIZE * 2];
		bool cmp(const int &a, const int &b) const;

	public:
		iTree(void);
		bool empty(void) const;
		void insert(const int &key, const int &value);
		int getBest(int start, int end, int pos = 1, int rootStart = 1, int rootEnd = SIZE);

};

int bricks,
	brick[100010],
	result[100010],
	remov[100010],
	position[100010],
	sortMe[100010],
	best,
	res,
	p;
iTree tree;

bool compare(const int &a, const int &b);

int main(void)
{
	scanf("%d", &bricks);
	for(int b = 1; b <= bricks; ++ b)
		scanf("%d", &brick[b]);

	for(int s = 0; s < bricks; ++ s)
		sortMe[s] = s + 1;

	std::sort(sortMe, sortMe + bricks, compare);
	for(int s = 0, b; s < bricks; ++ s)
	{
		b = sortMe[s];
		if(b < brick[b])
		{
			result[b] = 0;
			continue;
		}

		result[b] = 1;
		if(!tree.empty())
		{
			p = tree.getBest(1, b - brick[b] + 1);
			result[b] = result[p] + 1;
			position[b] = p;
		}

		tree.insert(b - brick[b], b);
		if(result[best] < result[b])
			best = b;
	}

	while(result[best])
	{
		for(int j = 0; j < best - brick[best] - position[best] + brick[position[best]]; ++ j)
			remov[res ++] = position[best] + 1 + j;

		best = position[best];
	}

	printf("%d\n", res);
	for(int r = 0; r < res; ++ r)
		printf("%d ", remov[r]);

	puts("");
	return 0;
}

bool compare(const int &a, const int &b)
{
	if(brick[a] < brick[b])
		return true;

	if(brick[a] > brick[b])
		return false;

	return a > b;
}

iTree::iTree(void)
{
	for(int d = 0; d < SIZE * 2; ++ d)
		data[d] = 0;

	size = 0;
}

bool iTree::empty(void) const
{
	return !size;
}

bool iTree::cmp(const int &a, const int &b) const
{
	if(result[a] > result[b])
		return true;

	if(result[a] < result[b])
		return false;

	return a > b;
}

void iTree::insert(const int &key, const int &value)
{
	int v = SIZE + key;
	size += !data[v];
	data[v] = value;
	v /= 2;
	for(; v; v /= 2)
		if(cmp(data[v * 2], data[v * 2 + 1]))
			data[v] = data[v * 2];

		else
			data[v] = data[v * 2 + 1];

	return;
}

int iTree::getBest(int start, int end, int pos, int rootStart, int rootEnd)
{
	if(start == rootStart && end == rootEnd)
		return data[pos];

	int max = 0,
		middle = (rootStart + rootEnd) / 2,
		temp;

	if(start > middle)
		return getBest(start, end, pos * 2 + 1, middle + 1, rootEnd);

	if(end <= middle)
		return getBest(start, end, pos * 2, rootStart, middle);

	max = getBest(start, middle, pos * 2, rootStart, middle);
	temp = getBest(middle + 1, end, pos * 2 + 1, middle + 1, rootEnd);
	return cmp(max, temp)?max:temp;
}
