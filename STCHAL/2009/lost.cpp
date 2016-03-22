/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int a,b,c,d;

int main(void)
{
	scanf("%d %d %d %d", &a, &b, &c, &d);
	printf("%s\n", (a - c == 0 && b - d == 0)?"TAK":"NIE");
	return 0;
}

