/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

long long int numbers,
			  number,
			  count[64],
			  result;

int main(void)
{
	scanf("%lld", &numbers);
	for(long long int n = 0; n < numbers; ++ n)
	{
		scanf("%lld", &number);
		for(long long int b = 0; number > 0; ++ b)
		{
			count[b] += number % 2;
			number /= 2;
		}
	}

	for(long long int b = 0, power = 1; b < 32; ++ b, power *= 2)
		result += power * count[b] * (numbers - count[b]);

	printf("%lld\n", result);
	return 0;
}

