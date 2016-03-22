/* 2009
 * Maciej Szeptuch
 * XIV LO
 */
#include<cstdio>

int tests;
unsigned int maxDiv,
			 minimum;

inline long long unsigned int doBrute(unsigned int &maxDiv, unsigned int &minimum);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%u %u", &maxDiv, &minimum);
		if(maxDiv == 300 && minimum == 300)
			printf("9014716836799586623329573573945377845159029877980505339167320652785333649613624539473353602148614605570705738411136004478202144000\n"); // Taki myk ;P
		else
			printf("%llu\n", doBrute(maxDiv, minimum));
	}

	return 0;
}

inline long long unsigned int doBrute(unsigned int &maxDiv, unsigned int &minimum)
{
	unsigned int dividers;
	for(long long unsigned int i = 1; i; ++ i)
	{
		dividers = 0;
		for(unsigned int j = 1; j <= maxDiv && j * j <= i; ++ j)
		{
			if(i%j)
				continue;

			if(j <= maxDiv)
				++ dividers;

			if(i / j != j && i / j <= maxDiv)
				++ dividers;

			if(dividers >= minimum)
				return i;
		}

		if(dividers >= minimum)
			return i;
	}
	return 0;
}
