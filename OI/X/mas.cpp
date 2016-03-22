/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int sequences,
	equal[9],
	different[9],
	sequence[9][10],
	result[9],
	temp;

bool compatibile(void);

int main(void)
{
	scanf("%d", &sequences);
	for(int s = 0; s < 9; ++ s)
		result[s] = s + 1;

	for(int s = 0; s < sequences; ++ s)
	{
		scanf("%d %d", &equal[s], &different[s]);
		for(int p = 1; p <= sequences; ++ p)
		{
			scanf("%d", &temp);
			sequence[s][temp] = p;
		}
	}

	while(!compatibile())
		std::next_permutation(result, result + 9);

	for(int s = 0; s < sequences; ++ s)
		printf("%d ", result[s]);

	puts("");
	return 0;
}

bool compatibile(void)
{
	int diff = 0,
		eq = 0;
	for(int s = 0; s < sequences; ++ s)
	{
		diff = eq = 0;
		for(int p = 1; p <= sequences; ++ p)
			if(p == sequence[s][result[p - 1]])
				eq += result[p - 1];

			else if(sequence[s][result[p - 1]])
				diff += result[p - 1];

		if(eq != equal[s] || diff != different[s])
			return false;
	}

	return true;
}
