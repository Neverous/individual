/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int tests;
char word[100001];

inline unsigned int isPalindrome(char *Word);

int main(void)
{
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		scanf("%s", word);
		printf("%u\n", isPalindrome(word)?1:2);
	}

	return 0;
}

inline unsigned int isPalindrome(char *Word)
{
	unsigned int a = 0,
				 b = 0;
	for(;Word[b]; ++ b);
	-- b;

	while(a < b)
		if(Word[a ++] != Word[b --])
			return false;

	return true;
}
