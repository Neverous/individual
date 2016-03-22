/* 2011
 * Maciej Szeptuch
 * -*-*-*-*-*-*-*-*-
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	length,
	displacement;
char word[1048576],
	 answer[1048576];

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %s %c", &length, word, &answer[0]);
		answer[1] = 0;
		displacement = (word[0] - answer[0] + 26) % 26;
		for(int w = 1; word[w]; ++ w)
		{
			answer[w] = (26 + word[w] - displacement - 'a') % 26 + 'a';
			answer[w + 1] = 0;
		}

		puts(answer);
	}

	return 0;
}

