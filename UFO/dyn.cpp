/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int request,
			 rest[131072],
			 s,
			 n;

int main(void)
{
	scanf("%u", &request);
	n = 1 % request;
	s = 1;
	while(!rest[n])
	{
		rest[n] = s ++;
		n = (n * 10 + 1) % request;
	}

	s -= rest[n] + 1;
	while(s --)
		putchar('1');

	while(rest[n] --)
		putchar('0');

	puts("");
	return 0;
}

