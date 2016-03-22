/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#define TAB(x, y) (((y) >= 0 && (y) < 128)?tab[(x)][(y)]:0)

int tab[64][128];

int main(void)
{
	tab[0][0] = 1;
	for(int i = 1; i < 64; ++ i)
		for(int p = 0; p < i * 2 + 1; ++ p)
			tab[i][p] = (TAB(i - 1, p - 2) + TAB(i - 1, p) + TAB(i - 1, p - 1)) % 3;


	for(int i = 0; i < 64; ++ i)
	{
		for(int s = 0; s < 63 - i; ++ s)
			putchar(' ');

		for(int p = 0; p < i * 2 + 1; ++ p)
			putchar(tab[i][p] + '0');

		puts("");
	}

	return 0;
}
