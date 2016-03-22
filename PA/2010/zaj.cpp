/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<string>
#include<map>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

using namespace std;

int length,
	result,
	best,
	pi[1024][1024];
char buffer[1024];

inline int LCS(char *wordA, int lengthA, char *wordB, int lengthB);

int main(void)
{
	scanf("%d", &length);
	scanf("%s", buffer);

	best = length;
	for(int l = 1; l < best && l < length; ++ l)
	{
		result = length - 2 * LCS(buffer, l, buffer + l, length - l);
		if(result < best)
			best = result;
	}

	printf("%d\n", best);
	return 0;
}

inline int LCS(char *wordA, int lengthA, char *wordB, int lengthB)
{
	for(int a = 0; a < lengthA; ++ a)
		for(int b = 0; b < lengthB; ++ b)
			if(wordA[a] == wordB[b])
				pi[a + 1][b + 1] = pi[a][b] + 1;

			else
				pi[a + 1][b + 1] = max(pi[a][b + 1], pi[a + 1][b]);

	return pi[lengthA][lengthB];
}
