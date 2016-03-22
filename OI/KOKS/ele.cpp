/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<queue>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int length,
	result;
std::priority_queue<std::pair<int, int> > que;
std::pair<int, int> act,
					tmp;

int main(void)
{
	scanf("%*d");
	while(scanf("%d", &length) != -1)
		que.push(std::make_pair(-length, 1));

	while(!que.empty())
	{
		act = que.top();
		que.pop();
		while(!que.empty() && (tmp = que.top()).first == act.first)
		{
			act.second += tmp.second;
			que.pop();
		}

		result += act.second % 2;
		if(act.second / 2)
			que.push(std::make_pair(act.first * 2, act.second / 2));
	}

	printf("%d\n", result);
	return 0;
}

