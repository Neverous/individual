/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#define DEBUG(args...) fprintf(stderr, args)
//#define DEBUG(args...)

int size,
	prop,
	left[1000010],
	right[1000010],
	best;
char string[1000010];

inline int max(int a, int b);

int main(void)
{
	scanf("%d %d", &size, &prop);
	scanf("%s", string);
	for(int s = 1; s <= size; ++ s)
	{
		if(string[s - 1] == 'R')
			++ left[s];

		else
			++ right[s];

		left[s + 1] = left[s];
		right[s + 1] = right[s];
	}

	for(int e = prop + 1; e <= size; ++ e)
		for(int s = e % (prop + 1) + 1; best < e - s + 1 && s < e; ++ s)
			if((left[e] - left[s - 1]) * prop == (right[e] - right[s - 1]))
				best = max(best, e - s + 1);

	printf("%d\n", best);
	return 0;
}

inline int max(int a, int b)
{
	return a > b?a:b;
}
