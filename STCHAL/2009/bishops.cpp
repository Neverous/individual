/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int n;

int main(void)
{
	scanf("%d", &n);
	if(n == 1)
		printf("1\n");

	else
		printf("%d\n", n * 2 - 2);
	return 0;
}

