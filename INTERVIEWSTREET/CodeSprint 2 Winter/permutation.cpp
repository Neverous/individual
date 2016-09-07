/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdlib>
#include<cstdio>
#include<algorithm>

int size,
	point[64][64],
	best,
	points,
	permutation[64],
	result[64];

inline void copy(int *to, int *from);
inline long long int count(int *start, int *end);

int main(void)
{
	scanf("%d", &size);
	for(int s = 0; s < size; ++ s)
		permutation[s] = s;

	for(int h = 0; h < size; ++ h)
		for(int w = 0; w < size; ++ w)
			scanf("%d", &point[h][w]);

	best = count(permutation, permutation + size);
	copy(result, permutation);
	if(size < 11)
		do
		{
			points = count(permutation, permutation + size);
			if(points > best)
			{
				best = points;
				copy(result, permutation);
			}
		}
		while(std::next_permutation(permutation, permutation + size));

	else
		for(int t = 0; t < 50000000 / size; ++ t)
		{
			std::random_shuffle(permutation, permutation + size);
			points = count(permutation, permutation + size);
			if(points > best)
			{
				best = points;
				copy(result, permutation);
			}
		}

	for(int s = 0; s < size; ++ s)
		printf("%d%c", result[s], s + 1 == size?'\n':' ');
}

inline void copy(int *to, int *from)
{
	for(int s = 0; s < 64; ++ s)
		to[s] = *(from + s);

	return;
}

inline long long int count(int *start, int *end)
{
	long long int res = 0;
	for(int *s = start, *n = start + 1; n != end; ++ s, ++ n)
		res += point[*s][*n];

	return res;
}
