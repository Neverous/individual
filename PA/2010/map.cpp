/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
#include<vector>
#define DEBUG(args...) fprintf(stderr, args)
//#define DEBUG(args...)

int points,
	range,
	result,
	temp,
	min,
	max;
bool left[1000010];
std::pair<int, int> point[1000010];

const int BUFFER = 4096;
int b = BUFFER - 1;
char buffer[BUFFER];

inline int getInt(void);

int main(void)
{
	points = getInt();
	range = getInt();
	for(int p = 0; p < points; ++ p)
	{
		point[p].first = getInt();
		point[p].second = getInt();
	}

	std::sort(point, point + points);
	min = 1000000010;
	max = 0;
	for(int p = 0; p < points; ++ p)
	{
		if(p && point[p].first != point[p - 1].first)
			for(int pp = p - 1; pp >= 0 && point[pp].first == point[p - 1].first; -- pp)
			{
				if(max < point[pp].second)
					max = point[pp].second;

				if(min > point[pp].second)
					min = point[pp].second;
			}


		if(max > point[p].second && min < point[p].second)
			left[p] = true;
	}

	min = 1000000010;
	max = 0;
	for(int p = points - 1; p >= 0; -- p)
	{
		if(p < points - 1 && point[p].first != point[p + 1].first)
			for(int pp = p + 1; pp < points && point[pp].first == point[p + 1].first; ++ pp)
			{
				if(max < point[pp].second)
					max = point[pp].second;

				if(min > point[pp].second)
					min = point[pp].second;
			}

		if(!left[p])
			continue;

		if(max > point[p].second && min < point[p].second)
			++ result;
	}

	printf("%d\n", result);
	return 0;
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
