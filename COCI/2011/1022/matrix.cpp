/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int size,
	matrix[512][512],
	maind[512][512],
	other[512][512],
	result;

inline static const int MAX(const int &a, const int &b){return a>b?a:b;}

int main(void)
{
	scanf("%d", &size);
	for(int h = 1; h <= size; ++ h)
		for(int w = 1; w <= size; ++ w)
			scanf("%d", &matrix[h][w]);

	/* PREPROCESS */
	for(int h = 1; h <= size; ++ h)
		for(int w = 1; w <= size; ++ w)
		{
			maind[h][w] = matrix[h][w] + maind[h-1][w-1];
			other[h][w] = matrix[h][w] + other[h-1][w+1];
		}

	for(int h = 1; h <= size; ++ h)
		for(int w = 1; w <= size; ++ w)
			for(int k = 1; h + k <= size && w + k <= size; ++ k)
				result = MAX(result, maind[h+k][w+k] + other[h-1][w+k+1] - maind[h-1][w-1] - other[h+k][w]);

	printf("%d\n", result);
	return 0;
}

