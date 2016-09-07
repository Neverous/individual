/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int size,
			 width;
char line[256];

int main(void)
{
	scanf("%u", &size);
	width = 2 * size + 3;
	line[width] = 0;
	line[width / 2] = '*';
	for(unsigned int s = 0; s < size; ++ s) // Kondygnacja
		for(unsigned int c = 0; c < 3; ++ c) // Poziom
		{
			for(unsigned int u = 0, e = width / 2 - c - s; u < e; ++ u)
				line[u] = line[width - 1 - u] = '_';

			for(unsigned int x = 0, e = s + c; x < e; ++ x)
				line[width / 2 + 1 + x] = line[width / 2 - 1 - x] = '*';

			puts(line);
		}

	for(unsigned int u = 0, e = width / 2 - 1; u < e; ++ u)
		line[u] = line[width - 1 - u] = '_';

	puts(line);
	puts(line);
	return 0;
}

