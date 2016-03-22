/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int tests,
	result,
	input;
char buffer[16];

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d %s", &result, &input, buffer);
		for(int i = 0, r = 0; r < result; ++ r, ++ i)
		{
			if(i == input)
				i = 0;

			printf("%c", buffer[i]);
		}

		puts("");
	}


	return 0;
}

