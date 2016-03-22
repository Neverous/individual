/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int a, b, c;

int main(void)
{
	scanf("%d %d %d", &a, &b, &c);
	printf("%s\n", (a * a + b * b == c * c || a * a + c * c == b * b || b * b + c * c == a * a)?"TAK":"NIE");
	return 0;
}

