/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int size;
char buffer[1024];
bool tower[1024][1024],
	 column[1024],
	 row[1024];

int main(void)
{
	scanf("%d", &size);
	for(int h = 0; h < size; ++ h)
	{
		scanf("%s", buffer);
		for(int w = 0; w < size; ++ w)
			if(buffer[w] == 'W')
			{
				tower[h][w] = true;
				column[w] = true;
				row[h] = true;
			}
	}

	for(int h = 0; h < size; ++ h)
	{
		for(int w = 0; w < size; ++ w)
		{
			if(tower[h][w])
				putchar('W');

			else if(column[w] || row[h])
				putchar('.');

			else
			{
				putchar('W');
				column[w] = row[h] = true;
			}
		}

		puts("");
	}

	return 0;
}

