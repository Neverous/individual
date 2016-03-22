/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int c;
bool bylo[1010];

int main(void)
{
	scanf("%*d");
	c = 0;
	while(scanf("%d", &c) != -1)
	{
		if(bylo[c])
		{
			printf("NIE\n");
			return 0;
		}

		bylo[c] = true;
	}

	printf("TAK\n");
	return 0;
}

