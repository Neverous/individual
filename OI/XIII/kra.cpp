/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#define MIN(a, b) ((a) < (b)?(a):(b))

int pipeHeight,
	discs,
	last = 1000000010,
	disc,
	pipe[300030];

int main(void)
{
	scanf("%d %d", &pipeHeight, &discs);
	for(int p = 0; p < pipeHeight; ++ p)
	{
		scanf("%d", &pipe[p]);
		last = pipe[p] = MIN(last, pipe[p]);
	}

	last = pipeHeight;
	for(int d = 0; last >= 0 && d < discs; ++ d)
	{
		-- last;
		scanf("%d", &disc);
		while(last >= 0 && pipe[last] < disc)
			-- last;
	}

	printf("%d\n", last + 1);
	return 0;
}

