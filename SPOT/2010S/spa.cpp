/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int tests,
	size,
	horiz,
	vertic;
char word[500050];

static int ABS(int a)
{
	return a > 0?a:- a;
}

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %s", &size, word);
		horiz = vertic = 0;
		for(int w = 0; w < size; ++ w)
		{
			switch(word[w])
			{
				case 'N':
					-- vertic;
					break;

				case 'S':
					++ vertic;
					break;

				case 'W':
					++ horiz;
					break;

				case 'E':
					-- horiz;
					break;
			}
		}

		printf("%d\n", ABS(horiz) + ABS(vertic));
	}

	return 0;
}

