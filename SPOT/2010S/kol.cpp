/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<set>

int tests,
	size,
	tab[100010],
	result[100010];

std::set<int> secik;
std::set<int>::iterator temp;

struct iTree
{
	static const int SIZE = 262144;
	int data[SIZE];

	iTree(void)
	{
		for(int s = 0; s < SIZE; ++ s)
			data[s] = 0;

		return;
	}

	void insert(int start, int end = SIZE / 2, int rootStart = 1, int rootEnd = SIZE / 2, int index = 1)
	{
		if(start == rootStart && end == rootEnd)
		{
			++ data[index];
			return;
		}

		int half = (rootStart + rootEnd) / 2;

		if(end <= half)
			insert(start, end, rootStart, half, index * 2);

		else if(start > half)
			insert(start, end, half + 1, rootEnd, index * 2 + 1);

		else if(start <= half && end > half)
		{
			insert(start, half, rootStart, half, index * 2);
			insert(half + 1, end, half + 1, rootEnd, index * 2 + 1);
		}

		return;
	}

	int get(int pos)
	{
		int res = 0;
		pos += SIZE / 2;
		while(pos)
		{
			res += data[pos];
			pos /= 2;
		}

		return res;
	}
};

iTree tree;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		tree = iTree();
		scanf("%d", &size);
		for(int s = 0; s < size; ++ s)
		{
			scanf("%d", &tab[s]);
			secik.insert(s);
		}

		for(int s = size - 1; s >= 0; -- s)
		{
			//printf("%d: %d; %d\n", s + 1, tab[s], tree.get(tab[s] + 1));
			temp = secik.lower_bound(tab[s] + tree.get(tab[s] + 1));
			result[s] = *temp + 1;
			//printf("%d => %d\n", s + 1, *temp + 1);
			secik.erase(temp);
			tree.insert(tab[s] + 2);
		}

		for(int s = 0; s < size; ++ s)
			printf("%d ", result[s]);

		puts("");
	}

	return 0;
}

