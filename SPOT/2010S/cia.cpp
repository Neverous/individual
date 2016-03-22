/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>

int tests,
	size,
	sequence[1000010],
	sum[1000010],
	best,
	A,
	B;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &size);
		for(int s = 0; s < size; ++ s)
			scanf("%d", &sequence[s]);

		std::sort(sequence, sequence + size);
		std::reverse(sequence, sequence + size);
		for(int s = size - 1; s >= 0; -- s)
			sum[s] = sequence[s] + ((s + 2 < size)?sum[s + 2]:0);

		best = sum[0] - sum[1];
		A = 0;
		B = 0;

		for(int s = 0; s < size; ++ s)
		{
			if(!s || sequence[s] + 1 < sequence[s - 1]) // DODAJ A
			{
				if(best > A - B + ((s % 2)?-1:1) * (sequence[s] + 1 + ((s + 1 < size)?sum[s + 1]:0) - sum[s]))
					best = A - B + ((s % 2)?-1:1) * (sequence[s] + 1 + ((s + 1 < size)?sum[s + 1]:0) - sum[s]);
			}

			if(s == size - 1 || sequence[s] - 1 > sequence[s + 1]) // DODAJ B
			{
				if(best > A - B + ((s % 2)?1:-1) * (((s + 2 < size)?sum[s + 2]:0) - ((s + 1 < size)?sum[s + 1]:0) - 1))
					best = A - B + ((s % 2)?1:-1) * (((s + 2 < size)?sum[s + 2]:0) - ((s + 1 < size)?sum[s + 1]:0) - 1);
			}

			// DODAJ C
			if(best > A - B + ((s % 2)?-1:1) * (sequence[s] + ((s + 1 < size)?sum[s + 1]:0) - sum[s]))
				best = A - B + ((s % 2)?-1:1) * (sequence[s] + ((s + 1 < size)?sum[s + 1]:0) - sum[s]);

			if(s % 2)
				B += sequence[s];

			else
				A += sequence[s];
		}

		printf("%d\n", best);
	}
	return 0;
}

