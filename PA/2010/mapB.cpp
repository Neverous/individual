/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define DEBUG(args...) fprintf(stderr, args)
//#define DEBUG(args...)

using namespace std;

struct iTree
{
	int * data,
		size,
		SIZE;

	iTree(int maxValue)
	{
		SIZE = 1;
		while(SIZE < maxValue)
			SIZE *= 2;

		data = new int[SIZE * 2];
		clear();
	}

	~iTree(void)
	{
		delete data;
	}

	inline void clear(void)
	{
		size = 0;
		for(int s = 0; s < 2 * SIZE; ++ s)
			data[s] = 0;
	}

	inline int getSize(void)
	{
		return size;
	}

	inline int getCount(int pos)
	{
		return data[pos + SIZE - 1];
	}

	inline void insert(int pos)
	{
		++ size;
		pos += SIZE - 1;
		for(;pos > 0; pos /= 2)
			data[pos] += 1;

		return;
	}

	int getInterval(int start, int end, int rootStart = 1, int rootEnd = -1, int p = 1)
	{
		if(rootEnd == -1)
			rootEnd = SIZE;

		//DEBUG("[%d, %d] [%d, %d]\n", start, end, rootStart, rootEnd);
		if(rootStart == start && rootEnd == end)
			return data[p];

		int middle = (rootStart + rootEnd) / 2;
		if(middle >= end)
			return getInterval(start, end, rootStart, middle, p * 2);

		if(middle < start)
			return getInterval(start, end, middle + 1, rootEnd, p * 2 + 1);

		return getInterval(start, middle, rootStart, middle, p * 2) + getInterval(middle + 1, end, middle + 1, rootEnd, p * 2 + 1);
	}
};

int points,
	range,
	result,
	temp;
bool left[1000010];
pair<int, int> point[1000010];
iTree * tree;

const int BUFFER = 4096;
int b = BUFFER - 1;
char buffer[BUFFER];

inline int getInt(void);
inline void compress(void);
inline bool ndCompare(const pair<int, int> &A, const pair<int, int> &B);

int main(void)
{
	points = getInt();
	range = getInt();
	range = 0;
	for(int p = 0; p < points; ++ p)
	{
		point[p].first = getInt() + 2;
		point[p].second = getInt() + 2;
		if(range < point[p].second)
			range = point[p].second;
	}

	if(range - 2 > points)
		compress();

	++ range;
	tree = new iTree(range);

	sort(point, point + points);
	for(int p = 0; p < points; ++ p)
	{
		if(p && point[p].first != point[p - 1].first)
			for(int pp = p - 1; pp >= 0 && point[pp].first == point[p - 1].first; -- pp)
				tree->insert(point[pp].second);

		temp = tree->getInterval(point[p].second + 1, range);
		if(temp && tree->getSize() - temp - tree->getCount(point[p].second))
			left[p] = true;
	}

	tree->clear();
	for(int p = points - 1; p >= 0; -- p)
	{
		if(p < points - 1 && point[p].first != point[p + 1].first)
			for(int pp = p + 1; pp < points && point[pp].first == point[p + 1].first; ++ pp)
				tree->insert(point[pp].second);

		if(!left[p])
			continue;

		temp = tree->getInterval(point[p].second + 1, range);
		if(temp && tree->getSize() - temp - tree->getCount(point[p].second))
			++ result;
	}

	printf("%d\n", result);
	return 0;
}

inline void compress(void)
{
	sort(point, point + points, ndCompare);
	for(int p = 0, n = 1, old = -1; p < points; ++ p)
	{
		if(point[p].second != old)
		{
			range = ++ n;
			old = point[p].second;
		}

		point[p].second = n;
	}
}

inline bool ndCompare(const pair<int, int> &A, const pair<int, int> &B)
{
	if(A.second < B.second)
		return true;

	if(A.second > B.second)
		return false;

	return A.first < B.first;
}

inline int getInt(void)
{
	int number = 0;
	while((buffer[b] < '0' || buffer[b] > '9') && ++ b)
		if(b == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			b = 0;
		}

	while(buffer[b] >= '0' && buffer[b] <= '9')
	{
		number = number * 10 + buffer[b] - '0';
		++ b;

		if(b == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			b = 0;
		}
	}

	return number;
}
