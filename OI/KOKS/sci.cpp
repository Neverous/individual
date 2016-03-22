/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int res,
	value;

int main(void)
{
	scanf("%*d");
	while(scanf("%d", &value) != -1)
		if(res < value)
			res = value;

	printf("%d\n", res);
	return 0;
}

