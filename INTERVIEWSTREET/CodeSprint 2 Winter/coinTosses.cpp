/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
#include<cmath>

inline static long double E(const int &n, const int &m);

int tests,
	n, m;
long double res;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d", &n, &m);
		res = E(n, m);
		if(res < 0.001L && res > -0.001L)
			res = 0.0L;

		printf("%.2Lf\n", res);
	}

	return 0;
}

inline static long double E(const int &n, const int &m)
{
	if(n == m)
		return 0.0L;

	if(m == 0)
		return 1.0L * powl(2, n + 1) - 2.0L;

	return 1.0L + E(n, m + 1) / 2.0L + E(n, 0) / 2.0L;
}

