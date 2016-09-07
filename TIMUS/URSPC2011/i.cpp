/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
#include<cstring>

int linesPerPage,
	width,
	words,
	wordLen,
	actual,
	lines = 1;
char word[128];
bool first = true;

int main(void)
{
	scanf("%d %d %d", &linesPerPage, &width, &words);
	for(int w = 0; w < words; ++ w)
	{
		scanf("%s", word);
		wordLen = strlen(word);
		if(actual + wordLen + !first > width)
		{
			++ lines;
			first = true;
			actual = 0;
		}

		actual += wordLen + !first;
		first = false;
	}

	printf("%d\n", (lines + linesPerPage - 1) / linesPerPage);
	return 0;
}

