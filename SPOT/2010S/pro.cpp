/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	actions;
long long int interval,
			  start,
			  end,
			  number[1024];
char action[1024][4];

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %lld %lld", &actions, &interval, &start);
		end = start + 1;
		for(int a = 0; a < actions; ++ a)
			scanf("%s %lld", action[a], &number[a]);

		//printf("D: %lld %lld\n", start, end);
		for(int a = actions - 1; a >= 0; -- a)
		{
			switch(action[a][0])
			{
				case '+':
					start -= number[a];
					end -= number[a];
					break;

				case '-':
					start += number[a];
					end += number[a];
					break;

				case '*':
					start = (start + number[a] - 1) / number[a];
					end = (end + number[a] - 1) / number[a];
					break;

				case '/':
					start *= number[a];
					end *= number[a];
					break;
			}
			//printf("D: %lld %lld\n", start, end);
		}

		if(start < 0)
			start = 0;

		if(end < 0)
			end = 0;

		if(end > interval)
			end = interval + 1;

		if(start > interval)
			start = interval + 1;

		printf("%lld\n", end - start);
	}
	return 0;
}

