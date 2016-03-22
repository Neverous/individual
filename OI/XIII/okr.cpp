/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int length,
	longest[1000010],
	shortest[1000010];
long long unsigned int result;
char word[1000010];

void preprocess(void);

int main(void)
{
	scanf("%d", &length);
	scanf("%s", word);
	preprocess();
	for(int w = 0; w < length; ++ w)
		result += shortest[w]?w + 1 - shortest[w]:0;

	printf("%llu\n", result);
	return 0;
}

void preprocess(void)
{
	for(int i = 1, j = 0; i < length; ++ i)
	{
		while(j && word[i] != word[j])
			j = longest[j - 1];

		if(word[i] == word[j])
		{
			longest[i] = ++ j; // KMP
			if(shortest[j - 1])
				shortest[i] = shortest[j - 1];

			else
				shortest[i] = longest[i];
		}
	}

	return;
}
