/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>

int a, b;

int main(void)
{
	scanf("%d %d", &a, &b);
	puts((a % 2 == 0 || b % 2)?"yes":"no");
	return 0;
}

