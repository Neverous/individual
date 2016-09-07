/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int height,
	width,
	map[1010][1010],
	highest = 0,
	lowest = (1 << 30);

inline static bool isHill(const int &h, const int &w);

int main(void)
{
	scanf("%d %d", &height, &width);
	for(int h = 0; h < height; ++ h)
		for(int w = 0; w < width; ++ w)
			scanf("%d", &map[h][w]);

	for(int h = 0; h < height; ++ h)
		for(int w = 0; w < width; ++ w)
			if(isHill(h, w))
			{
				if(map[h][w] > highest)
					highest = map[h][w];

				if(map[h][w] < lowest)
					lowest = map[h][w];
			}

	printf("%d %d\n", highest, lowest);
	return 0;
}

inline static bool isHill(const int &h, const int &w)
{
	for(int r = -1; r < 2; ++ r)
		for(int c = -1; c < 2; c += 1 + !r)
			if(h + r >= 0 && h + r < height &&
			   w + c >= 0 && w + c < width &&
			   map[h + r][w + c] >= map[h][w])
				return false;

	return true;
}
