/* 2011
 * Maciej Szeptuch
 * -*-*-*-*-*-*-*-*-
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	numbers,
	que[1048576],
	seq[1048576],
	ans[1048576];

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &numbers);
		for(int n = 0; n < numbers; ++ n)
			scanf("%d", &seq[n]);

		for(int n = numbers - 1, q = 0; n >= 0; -- n)
		{
			while(q && seq[que[q - 1]] <= seq[n])
				-- q;

			que[q] = n;
			ans[n] = q?que[q - 1]:-1;
			++ q;
		}

		for(int n = 0; n < numbers; ++ n)
			printf("%d%c", ans[n], n + 1 == numbers?'\n':' ');
	}
	
	return 0;
}

