/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
#include<algorithm>

int tests,
	cards,
	card[65536];
long long int result;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		result = 1;
		scanf("%d", &cards);
		for(int c = 0; c < cards; ++ c)
			scanf("%d", &card[c]);

		std::sort(card, card + cards);
		for(int c = 0, r = 0; c < cards && result; ++ c)
		{
			while(r < cards && card[r] <= c)
				++ r;

			result = (result * (r - c)) % 1000000007;
		}

		printf("%lld\n", result);
	}

	return 0;
}
