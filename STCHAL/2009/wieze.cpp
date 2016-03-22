/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int res(int n)
{
	if(n == 1)
		return 1;

	return res(n - 1) * 2 + 1;
}

int n;

int main(void)
{
	scanf("%d", &n);
	printf("%d\n", res(n));
	return 0;
}

