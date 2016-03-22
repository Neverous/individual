/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...) 

int parts,
	tmp,
	tab[16384],
	result;

int main(void)
{
	scanf("%d", &parts);
	for(int p = 0; p < parts; ++ p)
	{
		scanf("%d", &tmp);
		++ tab[tmp];
		result += tmp;
	}

	for(int i = 0, j = 10000; i < j;)
	{
		while(tab[i] && tab[j])
		{
			result += j - i;
			-- tab[i];
			-- tab[j];
		}

		while(i < j && !tab[i])
			++ i;

		while(i < j && !tab[j])
			-- j;
	}

	printf("%d\n", result);
	return 0;
}

