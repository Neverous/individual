/* 2011
 * Maciej Szeptuch
 * -*-*-*-*-*-*-*-*-
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	set,
	hektors,
	card;
bool answer,
	 deck[1048576];

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d", &set, &hektors);
		answer = hektors == set;
		if(answer)
			for(int s = 0; s < set; ++ s)
				deck[s] = false;

		for(int h = 0; h < hektors; ++ h)
		{
			scanf("%d", &card);
			-- card;
			answer &= !deck[card];
			deck[card] = true;
		}

		puts(answer?"TAK":"NIE");
	}

	return 0;
}

