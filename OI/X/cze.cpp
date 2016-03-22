/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int width,
	height,
	cost,
	sort[1001][2],
	result,
	horizParts = 1,
	vertParts = 1;

int main(void)
{
	scanf("%d %d", &width, &height);
	for(int w = 0; w < width - 1; ++ w)
	{
		scanf("%d", &cost);
		++ sort[cost][0];
	}

	for(int h = 0; h < height - 1; ++ h)
	{
		scanf("%d", &cost);
		++ sort[cost][1];
	}

	for(int c = 1000; c > 0; -- c)
	{
		if(sort[c][0])
		{
			result += c * horizParts * sort[c][0];
			vertParts += sort[c][0];
		}

		if(sort[c][1])
		{
			result += c * vertParts * sort[c][1];
			horizParts += sort[c][1];
		}
	}

	printf("%d\n", result);

	return 0;
}

