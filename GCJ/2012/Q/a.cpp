/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>

int tests;
char phrase[128];
char change[32] = {
	'y', //a
	'h', //b
	'e', //c
	's', //d
	'o', //e
	'c', //f
	'v', //g
	'x', //h
	'd', //i
	'u', //j
	'i', //k
	'g', //l
	'l', //m
	'b', //n
	'k', //o
	'r', //p
	'z', //q
	't', //r
	'n', //s
	'w', //t
	'j', //u
	'p', //v
	'f', //w
	'm', //x
	'a', //y
	'q', //z
};

char * translate(char *io);

int main(void)
{
	scanf("%d ", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%[^\n] ", phrase);
		printf("Case #%d: %s\n", t + 1, translate(phrase));
	}

	return 0;
}

char * translate(char *io)
{
	for(int i = 0; io[i]; ++ i)
		if(io[i] != ' ')
			io[i] = change[io[i]  - 'a'];

	return io;
}
