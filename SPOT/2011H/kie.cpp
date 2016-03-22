/* 2011
 * Maciej Szeptuch
 * -*-*-*-*-*-*-*-*-
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

long long unsigned int product;
unsigned int sum;
int tests,
	elements,
	number;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d", &elements, &number);
		product = sum = number;
		for(int e = 1; e < elements; ++ e)
		{
			scanf("%d", &number);
			sum += number;
			product *= number;
			if(product > 1073741824)
				product = 1073741824;
		}

		puts(product == sum?"=":product > sum?"ILOCZYN":"SUMA");
	}

	return 0;
}

