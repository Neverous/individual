/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
#include<vector>

int tests,
    start,
    end,
    result;

int checkMoves(int base, int start, int end);

int main(void)
{
	scanf("%d ", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		result = 0;
		scanf("%d %d", &start, &end);
		for(int s = start; s <= end; ++ s)
			result += checkMoves(s, start, end);

		printf("Case #%d: %d\n", t + 1, result);
	}

	return 0;
}

int checkMoves(int base, int start, int end)
{
	int req = 1,
	    act = base,
	    res = 0;
	for(int b = base; b >= 10; b /= 10)
		req *= 10;

	while(true)
	{
		act = (act / 10)  + (act % 10) * req;
		if(act == base)
			break;

		if(act >= start && act > base && act <= end)
			++ res;
	}

	return res;
}
