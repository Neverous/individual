/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	n, s, k,
	pos, lim;

int sum(int start, int end);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d %d", &n, &s, &k);
		if(s >= sum(1, k) && s <= sum(n - k + 1, n))
		{
			puts("TAK");
			pos = (s - sum(1, k)) / k;
			lim = n;
			for(int p = 0; p < pos && p < lim; ++ p)
				putchar('0');

			//printf("\n>>%d, %d, %d\n", pos, k, sum(pos + 1, pos + k));
			lim -= pos;
			for(int p = 0; p < k - s + sum(pos + 1, pos + k) && p < lim; ++ p)
				putchar('1');

			lim -= k - s + sum(pos + 1, pos + k);
			for(int p = 0; p < 1 && p < lim; ++ p)
				putchar('0');

			lim -= 1;
			for(int p = 0; p < s - sum(pos + 1, pos + k) && p < lim; ++ p)
				putchar('1');

			lim -= s - sum(pos + 1, pos + k);
			for(int p = 0; p < lim; ++ p)
				putchar('0');

			puts("");
		}

		else
			puts("NIE");
	}
	return 0;
}

int sum(int start, int end)
{
	return end * (end + 1) / 2 - (start - 1) * start / 2;
}

