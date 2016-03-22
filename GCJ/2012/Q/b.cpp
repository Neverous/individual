/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>

int tests,
    players,
    surprise,
    question,
    score,
    result;

int main(void)
{
	scanf("%d ", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		result = 0;
		scanf("%d %d %d", &players, &surprise, &question);
		for(int p = 0; p < players; ++ p)
		{
			scanf("%d", &score);
			if(score < question)
				continue;

			if(score >= 3 * question - 2)
				++ result;

			else if(surprise && score >= 3 * question - 4)
			{
				++ result;
				-- surprise;
			}
		}

		printf("Case #%d: %d\n", t + 1, result);
	}

	return 0;
}
