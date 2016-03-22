/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

using namespace std;

long long int MAX(long long int a, long long int b)
{
	return a > b?a:b;
}

struct iTree
{
	static const int SIZE = 131072;
	long long int data[SIZE * 2];

	iTree(void)
	{
		for(int s = 0; s < SIZE * 2; ++ s)
			data[s] = 0;
	}

	void insert(int where, long long int what)
	{
		where += SIZE - 1;
		if(data[where] >= what)
			return;

		while(where)
		{
			data[where] = MAX(data[where], what);
			where /= 2;
		}

		return;
	}

	long long int get(int end, int start = 1, int rootStart = 1, int rootEnd = SIZE, int index = 1)
	{
		if(start == rootStart && end == rootEnd)
			return data[index];

		int middle = (rootStart + rootEnd) / 2;
		if(start > middle)
			return get(end, start, middle + 1, rootEnd, index * 2 + 1);

		if(end <= middle)
			return get(end, start, rootStart, middle, index * 2);

		return MAX(get(middle, start, rootStart, middle, index * 2), get(end, middle + 1, middle + 1, rootEnd, index * 2 + 1));
	}

};

int height,
	width,
	points;
long long int result;
pair<pair<int, int>, long long int> point[100010];
iTree tree;

void compress(void);
bool yCmp(const pair<pair<int, int>, int> &A, const pair<pair<int, int>, int> &B);

int main(void)
{
	scanf("%d %d %d", &height, &width, &points);
	for(int p = 0; p < points; ++ p)
		scanf("%d %d %lld", &point[p].first.first, &point[p].first.second, &point[p].second);

	compress();
	sort(point, point + points);
	for(int p = 0; p < points; ++ p)
	{
		point[p].second += tree.get(point[p].first.second);
		if(result < point[p].second)
			result = point[p].second;

		tree.insert(point[p].first.second, point[p].second);
	}

	printf("%lld\n", result);
	return 0;
}

void compress(void)
{
	sort(point, point + points, yCmp);
	for(int p = 0, n = 0, last = 0; p < points; ++ p)
	{
		if(last != point[p].first.second)
			++ n;

		last = point[p].first.second;
		point[p].first.second = n;
	}

	return;
}

bool yCmp(const pair<pair<int, int>, int> &A, const pair<pair<int, int>, int> &B)
{
	if(A.first.second < B.first.second)
		return true;

	if(A.first.second > B.first.second)
		return false;

	return A.second > B.second;
}
