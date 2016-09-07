/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>

long long int leftSize,
	rightSize,
	left[304],
	right[304];

long long int time;

inline static const long long int moved(const int &position, const long long int &time);
inline static const long long int MAX(const long long int &a, const long long int &b){return a>b?a:b;}

int main(void)
{
	scanf("%lld", &leftSize);
	for(int l = 0; l < leftSize; ++ l)
	{
		scanf("%lld", &left[l]);
		left[l] *= 10000000;
	}

	scanf("%lld", &rightSize);
	for(int r = 0; r < rightSize; ++ r)
	{
		scanf("%lld", &right[r]);
		right[r] *= 10000000;
	}

	for(int l = 0, r = 0; l < leftSize || r < rightSize;)
	{
		if(((l == leftSize) || moved(left[l], time) >= 80000000) && (r == rightSize || moved(right[r], time) >= 160000000))
			break;

		if(l != leftSize && moved(left[l], time) < 80000000)
		{
			time += moved(left[l] + 50000000, time) * 9 / 50;
			++ l;
		}

		if(r != rightSize && moved(right[r], time) < 160000000)
		{
			time += moved(right[r] + 50000000, time) * 9 / 50;
			++ r;
		}
	}

	printf("%lld.%07lld\n", time / 10000000, time % 10000000);
	return 0;
}

inline static const long long int moved(const int &position, const long long int &time)
{
	return MAX(position - time * 50 / 9, 0);
}
