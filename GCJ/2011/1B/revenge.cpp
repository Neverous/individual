/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	places,
	distance,
	point,
	vendors;

long double result,
			last,
			act;

inline static long double MIN(const long double &A, const long double &B){return A - B < 0.0000000001?A:B;}

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d", &places, &distance);
		result = 0;
		last = 1 << 30;
		for(int p = 0; p < places; ++ p)
		{
			scanf("%d %d", &point, &vendors);
			for(int v = 0; v < vendors; ++ v)
			{
				act = point;
				//printf("%d", v + 1);
				if(last != 1 << 30)
				{
					if(act - last < distance)
					{
						//printf(" R: %.8Lf", result);
						result += (long double) ((long double)distance - act + last) / 2;
						//printf(" R: %.8Lf", result);
					}

					else
					{
						//printf(" A: %.8Lf", act);
						act -= MIN(result * 2, (long double) act - last - distance);
						//printf(" A: %.8Lf", act);
					}
				}

				//puts("");
				last = act;
			}

			//puts("");
		}

		printf("Case #%d: %.8Lf\n", t + 1, result);
	}

	return 0;
}

