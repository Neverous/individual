/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int length,
			 result;
char first[1000010],
	 second[1000010];

int main(void)
{
	scanf("%u %s %s", &length, first, second);
	for(unsigned int l = 0; l < length; ++ l)
	{
		first[l] -= '0';
		second[l] -= '0';
		first[l] ^= second[l];

		if(l && first[l] != first[l - 1])
			++ result;
	}

	if(!result && first[0])
		++ result;

	printf("%u\n", result);
	return 0;
}

