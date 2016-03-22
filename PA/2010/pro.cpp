/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int width,
	height,
	round,
	result;

int main(void)
{
	scanf("%d %d %d", &width, &height, &round);
	for(int w = 1; w <= width; ++ w)
		for(int h = 1; h <= height; ++ h)
			for(int w2 = 0; w2 < w; ++ w2)
				for(int h2 = 0; h2 < h; ++ h2)
					if(2 * (w - w2 + h - h2) >= round)
						++ result;

	printf("%d\n", result);
	return 0;
}

