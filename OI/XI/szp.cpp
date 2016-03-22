/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<queue>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int spies,
	spy,
	followed[1048576],
	following[1048576],
	result;
std::queue<int> que;

int main(void)
{
	scanf("%d", &spies);
	for(int s = 0; s < spies; ++ s)
	{
		scanf("%d", &spy);
		-- spy;
		++ followed[spy];
		following[s] = spy;
	}

	for(int s = 0; s < spies; ++ s)
		if(!followed[s])
			que.push(s);

	while(!que.empty())
	{
		spy = que.front();
		que.pop();

		if(following[spy] == -1)
			continue;

		if(following[following[spy]] == -1)
			continue;

		++ result;
		if(!-- followed[following[following[spy]]])
			que.push(following[following[spy]]);

		following[following[spy]] = -1;
		following[spy] = -1;
	}

	for(int s = spy = 0, count, o; s < spies; spy = ++ s)
	{
		count = 0;
		while(following[spy] != -1)
		{
			++ count;
			o = spy;
			spy = following[spy];
			following[o] = -1;
		}

		result += count / 2;
	}

	printf("%d\n", result);
	return 0;
}

