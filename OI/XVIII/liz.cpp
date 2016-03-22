/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int segments,
			 questions,
			 length,
			 deepest,
			 loly[1000010];
char lollipop[1000010];
std::pair<unsigned int, unsigned int> possible[2000020];

inline static void preprocess(void);

int main(void)
{
	scanf("%u %u %s", &segments, &questions, lollipop);
	preprocess();
	for(unsigned int q = 0; q < questions; ++ q)
	{
		scanf("%u", &length);
		if(possible[length].first)
			printf("%u %u\n", possible[length].first, possible[length].second);

		else
			puts("NIE");

	}

	return 0;
}

inline static void preprocess(void)
{
	loly[1] = 2 - (lollipop[0] == 'W');
	for(unsigned int l = 1; lollipop[l]; ++ l)
		loly[l + 1] = loly[l] + 2 - (lollipop[l] == 'W');

	for(unsigned int e = 1, s = 1, lE = loly[1], lS; e <= segments; lE = loly[++ e])
	{
		for(s = 1, lS = loly[0]; s <= e && !possible[lE - lS].first; lS = loly[s ++])
		{
			if(deepest < s)
				deepest = s;

			possible[lE - lS] = std::make_pair(s, e);
		}

		for(s = deepest + 1, lS = loly[deepest]; s <= e && !possible[lE - lS].first; lS = loly[s ++])
			possible[lE - lS] = std::make_pair(s, e);
	}

	return;
}
