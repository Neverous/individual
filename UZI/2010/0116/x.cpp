/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

char buffer[1048576];
int b;

int main(void)
{
	scanf("%[^\n]s", buffer);
	for(b = 0; buffer[b]; ++ b);
	for(-- b; b >= 0; -- b)
		printf("%c", buffer[b]);

	return 0;
}

