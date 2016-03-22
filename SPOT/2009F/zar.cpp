/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#define DUZO 500000009

int count;
long long unsigned int result = 1,
					   power = 1;

int main(void)
{
	scanf("%d", &count);
	while(-- count)
	{
		power *= 4;
		if(power > DUZO)
			power %= DUZO;

		result += power;
		if(result > DUZO)
			result %= DUZO;
	}

	printf("%llu", result);
	return 0;
}
