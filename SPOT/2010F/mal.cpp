/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int tests,
			 a, b;

bool isRed(unsigned int f, unsigned int t);

int main(void)
{
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		 scanf("%u / %u", &a, &b);
		 printf("%s\n", isRed(a, b)?"czerwony":"niebieski");
	}

	return 0;
}

bool isRed(unsigned int f, unsigned int t)
{
	if(f == 0)
		return false;

	if(f == 1 && t == 1)
		return true;

	if(f < t)
		return isRed(t, f);

	return ((f / t) % 2) ^ isRed(f % t, t);
}
