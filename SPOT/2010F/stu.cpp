/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int tests,
			 grounds,
			 waters,
			 w, g;
long double  Wa, Wb,
	 Ga, Gb,
	 result;
std::pair<int, int> ground[100002],
	water[100002];

inline static long double MIN(long double A, long double B);

int main(void)
{
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		scanf("%u", &grounds);
		for(g = 0; g < grounds; ++ g)
			scanf("%u %u", &ground[g].first, &ground[g].second);

		scanf("%u", &waters);
		for(w = 0; w < waters; ++ w)
			scanf("%u %u", &water[w].first, &water[w].second);

		result = ((long int)1 << 31);
		Wa = Wb = Ga = Gb = w = g = 0;
		while(w < waters && g < grounds)
		{
			if(ground[g].first < water[w].first)
			{
				result = MIN(result, (long double)ground[g].second - Wa * ground[g].first - Wb);
				++ g;
				if(g < grounds)
				{
					Ga = (long double)(ground[g - 1].second - ground[g].second) / (ground[g - 1].first - ground[g].first);
					Gb = (long double)ground[g].second - Ga * ground[g].first;
				}
			}

			else if(ground[g].first > water[w].first)
			{
				result = MIN(result, Ga * water[w].first + Gb - water[w].second);
				++ w;
				if(w < waters)
				{
					Wa = (long double)(water[w - 1].second - water[w].second) / (water[w - 1].first - water[w].first);
					Wb = (long double)water[w].second - Wa * water[w].first;
				}
			}

			else
			{
				result = MIN(result, ground[g ++].second - water[w ++].second);
				if(w < waters)
				{
					Wa = (long double)(water[w - 1].second - water[w].second) / (water[w - 1].first - water[w].first);
					Wb = (long double)water[w].second - Wa * water[w].first;
				}

				if(g < grounds)
				{
					Ga = (long double)(ground[g - 1].second - ground[g].second) / (ground[g - 1].first - ground[g].first);
					Gb = (long double)ground[g].second - Ga * ground[g].first;
				}
			}
		}

		while(w < waters)
		{
			result = MIN(result, Ga * water[w].first + Gb - water[w].second);
			++ w;
		}

		while(g < grounds)
		{
			result = MIN(result, (long double)ground[g].second - Wa * ground[g].first - Wb);
			++ g;
		}

		printf("%.2Lf\n", result);
	}

	return 0;
}

inline static long double MIN(long double A, long double B)
{
	return A < B?A:B;
}

