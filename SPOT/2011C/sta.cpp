/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

char c;
unsigned int vowels;
bool word;

int main(void)
{
	scanf("%*u");
	while((c = getchar()) != -1)
	{
		if(c >= 'a' && c <= 'z')
		{
			if(c == 'a' || c == 'e' || c == 'i' ||
			   c == 'o' || c == 'u' || c == 'y')
				++ vowels;

			word = true;
		}

		else if(word)
		{
			printf("%u\n", vowels);
			vowels = word = false;
		}
	}

	if(word)
		printf("%u\n", vowels);

	return 0;
}

