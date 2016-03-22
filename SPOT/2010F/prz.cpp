/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	intervals,
	result;
int end;
std::pair<int, int> interval[1000000];

const int BUFFER = 4096;
int p = BUFFER - 1;
char buffer[BUFFER];

int getNumber(void);

inline static int MAX(int a, int b);

int main(void)
{
	tests = getNumber();
	for(int t = 0; t < tests; ++ t)
	{
		intervals = getNumber();
		for(int i = 0; i < intervals; ++ i)
		{
			interval[i].first = getNumber();
			interval[i].second = getNumber();
		}

		std::sort(interval, interval + intervals);
		end = interval[0].first - 1;
		result = 0;
		for(int i = 0; i < intervals; ++ i)
		{
			if(end < interval[i].first)
				result += interval[i].second - interval[i].first + 1;

			else if (end < interval[i].second)
				result += interval[i].second - end;

			end = MAX(end, interval[i].second);
		}

		printf("%d\n", result);

	}
	return 0;
}

inline static int MAX(int a, int b)
{
	return a>b?a:b;
}

int getNumber(void)
{
	int number = 0;
	bool above = true;
	while(buffer[p] != '-' && (buffer[p] < '0' || buffer[p] > '9') && ++ p)
		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}

	if(buffer[p] == '-')
	{
		above = false;
		++ p;
		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}
	}

	while(buffer[p] >= '0' && buffer[p] <= '9')
	{
		number = number * 10 + buffer[p] - '0';
		++ p;
		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}
	}

	return above?number:-number;
}

