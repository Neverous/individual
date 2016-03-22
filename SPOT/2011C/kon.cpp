/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<cstring>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int tests,
			 act,
			 fib[524288],
			 result;
char word[1048576];

static inline void preprocess(void);

int main(void)
{
	preprocess();
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		result = 1;
		act = 0;
		scanf("%s", word);
		for(unsigned int w = (word[0] == 'k'?3:2), len = strlen(word); w + 1 < len; ++ w)
		{
			if(word[w - 2] == 'k' && word[w - 1] == 'o' && word[w] == 't')
			{
				++ act;
				w += 2;
			}

			else if(act)
			{
				result = (unsigned int)(((long long unsigned int)result * fib[act]) % 1000000007);
				act = 0;
			}
		}

		if(act)
			result = (unsigned int)(((long long unsigned int)result * fib[act]) % 1000000007);

		printf("%u\n", result);
	}
	return 0;
}

static inline void preprocess(void)
{
	fib[0] = 1;
	fib[1] = 2;
	for(unsigned int f = 2; f < 524288; ++ f)
		fib[f] = (fib[f - 2] + fib[f - 1]) % 1000000007;

	return;
}
