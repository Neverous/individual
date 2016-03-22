/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int tests;
int length;
//char next,
//last;
char word[1048576];

int main(void)
{
	scanf("%d ", &tests);
	//for(int t = 0; t < tests; ++ t)
	//{
	//while(scanf("%c", &next) != -1 && next >= 'a' && next <= 'z')
	//last = next;
	//
	//printf("%sskie\n", last == 'a'?"zen":"me");
	//}

	for(int t = 0; t < tests; ++ t)
	{
		scanf("%c%n", word, &length);
		printf("%sskie\n", word[length - 1] == 'a'?"zen":"me");
	}

	return 0;
}

