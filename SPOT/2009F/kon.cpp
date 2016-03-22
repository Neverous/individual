/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int a,
	b,
	c;

int main(void)
{
	scanf("%*d");
	while(scanf("%d %d %d", &a, &b, &c) != -1)
		printf("%s\n", (a + b > c && a + c > b && b + c > a)?"TAK":"NIE");

	return 1;
}
