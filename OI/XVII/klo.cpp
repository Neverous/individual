/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int numbers,
	questions,
	height;
long long int number[1048576],
			  min[1048576],
			  max[1048576];

inline static int solve(const int &h);
inline static long long int prefSum(const long long int &start, const long long int &end, const long long int &k){return number[end] - number[start - 1] - k * (end - start + 1);}

int main(void)
{
	scanf("%d %d", &numbers, &questions);
	for(int n = 1; n <= numbers; ++ n)
	{
		scanf("%lld", &number[n]);
		number[n] += number[n - 1];
	}

	for(int q = 0; q < questions; ++ q)
	{
		scanf("%d", &height);
		printf("%d%c", solve(height), q + 1 == questions?'\n':' ');
	}
	return 0;
}

inline static int solve(const int &h)
{
	int best = 0;
	for(int s = 1; s <= numbers; ++ s)
		for(int e = numbers; e >= s + best; -- e)
			if(prefSum(s, e, h) >= 0)
				best = e - s + 1;

	for(int n = 1; n <= numbers; ++ n)
		number[n] += (long long int) n * h;

	return best;
}
