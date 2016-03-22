/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)
#define isVowel(arg) (arg == 'a' || arg == 'e' || arg == 'i' || arg == 'o' || arg == 'u' || arg == 'y')

unsigned int tests,
			 need,
			 vowels,
			 result;
char c;

int main(void)
{
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		result = vowels = 0;
		scanf("%u ", &need);
		while((c = getchar()) != -1 && c >= 'a' && c <= 'z')
		{
			if(isVowel(c))
				++ vowels;

			else
			{
				if(vowels >= need)
					result += vowels + 1 - need;

				vowels = 0;
			}
		}

		if(vowels >= need)
			result += vowels + 1 - need;

		printf("%u\n", result);
	}

	return 0;
}

