/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int size,
	atOnce,
	tests;

int count(int &number, int &base);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d", &size, &atOnce);
		printf("%d\n", count(size, atOnce));
	}

	return 0;
}

int count(int &number, int &base)
{
	if(base >= number)
		return 1;

	int result = 0;

	while(number > 1)
	{
		number = (number + base) / (base + 1);
		++ result;
	}

	return result;
}
