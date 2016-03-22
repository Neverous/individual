/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int pairs,
	first,
	second,
	start = 0,
	end = 1 << 31,
	result = -1,
	bak;

inline static const int MAX(const int &a, const int &b){return a>b?a:b;}

int main(void)
{
	scanf("%d", &pairs);
	for(int p = 0; p < pairs; ++ p)
	{
		scanf("%d %d", &first, &second);
		first += second;
		if(first - start >= 0)
		{
			++ result;
			bak = start;
			start = MAX(first - end, 0);
			end = first - bak;
		}

		else
		{
			start = 0;
			end = first;
		}
	}

	printf("%d\n", result);
	return 0;
}

