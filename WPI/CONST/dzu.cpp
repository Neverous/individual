/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<cstring>

int lengthP,
	lengthW,
	result,
	clockwise[1000010],
	anticlockwise[1000010],
	pi[1000010],
	nd[2000020],
	a,
	c;
char pattern[1000010],
	 word[1000010],
	 actual[2000020];

char* strrev(char *s);
int doKmp(char *patttern, char *word, int *table);
void kmpPrefix(char *word, int *pi);

int main(void)
{
	scanf("%d %d", &lengthP, &lengthW);
	scanf("%s %s", pattern, word);
	strcpy(actual, word);
	strncat(actual, word, lengthP - 1);
	result = doKmp(pattern, actual, clockwise);
	strrev(pattern);
	result += doKmp(pattern, actual, anticlockwise);

	printf("%d\n", result);
	for(c = 0; clockwise[c] > 0; ++ c)
		printf("%d ", clockwise[c]);

	if(c)
		puts("");

	for(a = 0; anticlockwise[a] > 0; ++ a)
		printf("%d ", anticlockwise[a]);

	if(a)
		puts("");

}

char* strrev(char *s)
{
	char t[2000020];;
	strcpy(t,s);
	for(int i = 0, j = strlen(s) - 1; j >= 0 ; i++, j--)
		s[i] = t[j];

	return s;
}

int doKmp(char *Pattern, char *Word, int *table)
{
	int res = 0;

	kmpPrefix(Pattern, pi);
	nd[0] = nd[1] = 0;
	for(int w = 0, l = 0; Word[w]; ++ w)
	{
		while(l && Word[w] != Pattern[l])
			l = pi[l - 1];

		if(Word[w] == Pattern[l])
			++ l;

		nd[w] = l;
		if(nd[w] == lengthP)
		{
			table[res ++] = w + 2 - lengthP;
			table[res] = 0;
		}
	}

	return res;
}

void kmpPrefix(char *Word, int *kpi)
{
	kpi[0] = kpi[1] = 0;
	for(int p = 1, l = 0; Word[p]; ++ p)
	{
		while(l && Word[p] != Word[l])
			l = kpi[l-1];

		if(Word[p] == Word[l])
			++ l;

		kpi[p] = l;
	}

	return;
} //KNUTH PI
