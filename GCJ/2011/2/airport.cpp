/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	normal,
	fast,
	walkways,
	start,
	end,
	speed;
long double result,
	 mtime,
	 time;

std::pair<int, int> part[1024];

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		part[0].first = 0;
		scanf("%d %d %d %Lf %d", &part[0].second, &normal, &fast, &time, &walkways);
		result = 0;
		for(int w = 0; w < walkways; ++ w)
		{
			scanf("%d %d %d", &start, &end, &speed);
			part[0].second -= part[w + 1].second = end - start;
			part[w + 1].first = speed;
		}

		std::sort(part, part + walkways + 1);

		for(int p = 0; p < walkways + 1; ++ p)
		{
			mtime = ((long double)part[p].second) / (part[p].first + fast);
			if(mtime <= time)
			{
				result += mtime;
				time -= mtime;
			}

			else
			{
				result += time;
				result += ((long double)part[p].second - time * (part[p].first + fast)) / (part[p].first + normal);
				time = 0;
			}
		}

		printf("Case #%d: %.9Lf\n", t + 1, result);
	}

	return 0;
}

