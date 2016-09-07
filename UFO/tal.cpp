/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int lenA,
			 lenB;
char A[16384],
	 B[16384];

inline static unsigned int lcs(char *a, char *b);
inline static unsigned int MAX(unsigned int a, unsigned int b);

int main(void)
{
	scanf("%u %u %s %s", &lenA, &lenB, A, B);
	printf("%u\n", lenA + lenB - lcs(A, B));
	return 0;
}

inline static unsigned int lcs(char *a, char *b)
{
	unsigned int lcs[2][16384];
	for(unsigned int s = 0; s < 16384; ++ s)
		lcs[0][s] = lcs[1][s] = 0;

	for(unsigned int f = 0; a[f]; ++ f)
		for(unsigned int s = 0; b[s]; ++ s)
			if(a[f] == b[s])
				lcs[(f + 1) % 2][s + 1] = lcs[f % 2][s] + 1;

			else
				lcs[(f + 1) % 2][s + 1] = MAX(lcs[(f + 1) % 2][s], lcs[f % 2][s + 1]);

	return lcs[lenA % 2][lenB];
}

inline static unsigned int MAX(unsigned int a, unsigned int b)
{
	return a>b?a:b;
}
