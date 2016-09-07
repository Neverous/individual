/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int snowmen,
	snowman,
	count[1048576],
	f, m, l,
	result;

int main(void)
{
	scanf("%d", &snowmen);
	for(int s = 0; s < snowmen; ++ s)
	{
		scanf("%d", &snowman);
		++ count[snowman];
	}

	f = m = l = 1000000;
	while(f > 0 && m > 0 && l > 0)
	{
		while(f > 0 && !count[f])
			-- f;

		if(m >= f)
			m = f - 1;

		while(m > 0 && !count[m])
			-- m;

		if(l >= m)
			l = m - 1;

		while(l > 0 && !count[l])
			-- l;

		if(count[f] && count[m] && count[l])
		{
			++ result;
			-- count[f];
			-- count[m];
			-- count[l];
		}
	}

	printf("%d\n", result);
	return 0;
}

