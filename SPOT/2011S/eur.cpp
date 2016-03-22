/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<queue>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	size,
	act,
	number;
std::queue<int> que;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &size);
		act = 1;
		que = std::queue<int>();
		for(int n = 0; n < size; ++ n)
		{
			while(!que.empty() && que.front() == act)
			{
				que.pop();
				++ act;
			}

			scanf("%d", &number);
			if(number == act)
				++ act;

			else
				que.push(number);
		}

		while(!que.empty() && que.front() == act)
		{
			que.pop();
			++ act;
		}

		puts(que.empty()?"TAK":"NIE");
	}
	return 0;
}

