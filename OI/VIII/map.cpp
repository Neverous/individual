/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#define MIN(a, b) ((a) < (b)?(a):(b))
#define MAX(a, b) ((a) > (b)?(a):(b))
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int size,
	range,
	map[256][256];

inline int getResult(int &h, int &w, int &r);

int main(void)
{
	scanf("%d %d", &size, &range);
	for(int h = 1; h <= size; ++ h)
		for(int w = 1; w <= size; ++ w)
		{
			 scanf("%d", &map[h][w]);
			 map[h][w] += map[h][w - 1];
			 map[h][w] += map[h - 1][w];
			 map[h][w] -= map[h - 1][w - 1];
		}

	for(int h = 1; h <= size; ++ h)
		for(int w = 1; w <= size; ++ w)
			printf("%d%c", getResult(h, w, range), w == size?'\n':' ');

	return 0;
}

inline int getResult(int &h, int &w, int &r)
{
	return map[MIN(h + r, size)][MIN(w + r, size)] +
		map[MAX(h - r - 1, 0)][MAX(w - r - 1, 0)] -
		map[MAX(h - r - 1, 0)][MIN(w + r, size)] -
		map[MIN(h + r, size)][MAX(w - r - 1, 0)];

}
