/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	crayons,
	crayon,
	have[16];

int main(void)
{
	scanf("%d", &tests);
	for(int t = 1; t <= tests; ++ t)
	{
		scanf("%d", &crayons);
		for(int c = 0; c < crayons; ++ c)
		{
			scanf("%d", &crayon);
			have[crayon] = t;
		}

		for(int c = 1; c <= 10; ++ c)
			if(have[c] != t)
				printf("%d%c", c, c == 10?'\n':' ');
	}

	return 0;
}

