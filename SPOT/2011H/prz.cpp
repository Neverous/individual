/* 2011
 * Maciej Szeptuch
 * -*-*-*-*-*-*-*-*-
 */
#include<cstdio>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	people,
	pair,
	alone,
	weight,
	person[1048576],
	result,
	s, e;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d %d %d", &people, &pair, &alone, &weight);
		for(int p = 0; p < people; ++ p)
			scanf("%d", &person[p]);

		if(alone * 2 <= pair)
		{
			printf("%d\n", people * alone);
			continue;
		}

		result = 0;
		std::sort(person, person + people);
		while(people && person[people - 1] > weight)
		{
			result += alone;
			-- people;
		}

		if(alone > pair)
			alone = pair;

		for(s = 0, e = people - 1; s < e;)
		{
			while(s < e && person[e] + person[s] > weight)
			{
				result += alone;
				-- e;
			}

			if(s < e)
			{
				result += pair;
				++ s;
				-- e;
			}
		}

		if(s == e)
		{
			result += alone;
			++ s;
		}

		printf("%d\n", result);
	}

	return 0;
}

