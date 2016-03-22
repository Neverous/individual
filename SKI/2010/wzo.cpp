/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int textLength,
			 patternLength,
			 result,
			 pi[1000020],
			 pi2[1000020],
			 first = 1;
bool possible[1000010],
	 next = true,
	 res = false;
char text[1000010],
	 pattern[1000010],
	 act[1000010];

inline bool KMP(char *p, char *t, unsigned int x);

int main(void)
{
	scanf("%u %u %s %s", &textLength, &patternLength, text, pattern);
	for(unsigned int p = 0; p + 1 < patternLength && pattern[p] == pattern[p + 1]; ++ p)
		++ first;

	for(unsigned int k = 1; next && k <= textLength / patternLength; ++ k)
	{
		for(unsigned int p = 0, a = 0; p < patternLength; ++ p)
			for(unsigned int l = 0; l < k; ++ l)
			{
				act[a ++] = pattern[p];
				act[a] = '$';
				act[a + 1] = 0;
			}

		next = KMP(act, text, k * first);
	}

	for(unsigned int t = 0; t < textLength; ++ t)
		result += possible[t];

	printf("%u\n", result);
	return 0;
}

inline bool KMP(char *p, char *t, unsigned int x)
{
	unsigned int pLen = 0;
	res = false;
	for(;p[pLen]; ++ pLen)
		pi[pLen] = 0;

	-- pLen;
	for(unsigned int i = 1, j = 0; p[i]; ++ i)
	{
		while(j > 0 && p[i] != p[j])
			j = pi[j - 1];

		if(p[i] == p[j])
			pi[i] = ++ j;
	}

	for(unsigned int i = 0, j = 0; t[i]; ++ i)
	{
		if(possible[i])
			continue;

		while(j > 0 && t[i] != p[j])
			j = pi[j - 1];

		if(t[i] == p[j])
			pi2[i] = ++ j;
	}

	for(unsigned int i = 0; t[i]; ++ i)
	{
		if(pi2[i] > x)
			res = true;

		if(pi2[i] == pLen)
			possible[i - pLen + 1] = true;
	}

	return res;
}

