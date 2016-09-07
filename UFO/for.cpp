/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int keys,
			 pow = 1,
			 days = 1;

inline static unsigned int MIN(const unsigned int &a, const unsigned int &b);

int main(void)
{
	scanf("%u", &keys);
	while(pow * 2 <= keys)
	{
		++ days;
		pow *= 2;
	}

	printf("%u\n", days);
	pow = 1;
	for(unsigned int d = 0; d < days; ++ d, pow *= 2)
	{
		printf("%u", MIN(keys - pow + 1, pow));
		for(unsigned int n = 0; n < pow && pow + n <= keys; ++ n)
			printf(" %u", pow + n);

		puts("");
	}

	return 0;
}

inline static unsigned int MIN(const unsigned int &a, const unsigned int &b)
{
	return a<b?a:b;
}
