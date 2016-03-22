/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int points,
	range,
	min,
	max,
	leftMin[1000010],
	leftMax[1000010],
	rightMin[1000010],
	rightMax[1000010];
std::pair<int, int> point[1000010];
long long int result;

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

		leftMin[p] = min;
		leftMax[p] = max;
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

		rightMin[p] = min;
		rightMax[p] = max;
	}

	//DEBUG("x => p: L R ^ L R\n");
	for(int x = point[0].first + 1, p = 0, pp = 0; x < point[points - 1].first; ++ x)
	{
		while(x > point[p].first && p < points - 1)
			++ p;

		pp = p;
		if(point[pp].first > x)
			-- pp;

		//DEBUG("%d => %d: %d %d ^ %d %d\n", x, p, leftMin[p], rightMin[pp], leftMax[p], rightMax[pp]);
		min = leftMin[p] > rightMin[pp]?leftMin[p]:rightMin[pp];
		max = leftMax[p] < rightMax[pp]?leftMax[p]:rightMax[pp];

		if(max - min - 1 > 0)
		{
			//DEBUG("D: %d[%d]: %d %d", x, p, point[p].first, point[pp].first);
			//DEBUG(" => %d", max - min - 1);
			//DEBUG("\n");
			//printf("%d: %d %d => %d\n", x, min, max, max - min - 1);
			result += (long long int)(max - min - 1) * (point[p].first - x + (pp >= p));
		}


		x = point[p].first - (pp && pp != p);
		//DEBUG("R: %d: %lld\n", x, result);
	}

	printf("%lld\n", result);
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
