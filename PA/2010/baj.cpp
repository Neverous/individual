/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

const int BUFFER = 4096;
int p = BUFFER - 1;
char buffer[BUFFER];
int getInt(void);

int result;
std::pair<int, int> recurse(void);

int main(void)
{
	result = 1;
	recurse();
	printf("%d\n", result);
	return 0;
}

std::pair<int, int> recurse(void)
{
	int count;
	std::pair<int, int> ret;
	std::vector<std::pair<int, int> > sth;
	count = getInt();
	if(!count)
	{
		ret.first = getInt();
		ret.second = getInt();

		return ret;
	}

	for(int c = 0; c < count; ++ c)
		sth.push_back(recurse());

	std::sort(sth.begin(), sth.end());
	for(unsigned int s = 1; s < sth.size(); ++ s)
		if(sth[s].first > sth[s - 1].second)
			++ result;

	return sth[0];
}

int getInt(void)
{
	int number = 0;
	while((buffer[p] < '0' || buffer[p] > '9') && ++ p)
		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
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

	return number;
}
