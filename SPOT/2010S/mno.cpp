/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	count;
long long int prime,
			  a,
			  b,
			  number;
bool bylo[1048576];

int main(void)
{
	scanf("%d %lld", &tests, &prime);
	for(int t = 0; t < tests; ++ t)
	{
		for(int i = 0; i < 1048576; ++ i)
			bylo[i] = false;

		scanf("%lld %lld", &a, &b);
		count = 0;
		number = 1;
		while(count < 50000000 && number != b)
		{
			if(number < 1048576)
			{
				if(bylo[number])
				{
					count = -1;
					break;
				}

				bylo[number] = true;
			}

			number = (number * a) % prime;
			++ count;
		}

		if(count == 50000000)
			count = -1;

		printf("%d\n", count);
	}
	return 0;
}

