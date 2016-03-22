/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int number;

int main(void)
{
	scanf("%d", &number);
	for(int n = 0; n < number; ++ n)
		if(n + n + 1 + n + 2 == number)
		{
			printf("TAK\n");
			return 0;
		}

	printf("NIE\n");
	return 0;
}

