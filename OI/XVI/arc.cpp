/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<list>
#include "carclib.h"

int projects,
	next;
std::list<int> best;
std::list<int>::iterator a, n;

int main(void)
{
	projects = inicjuj();
	for(int p = 0; p < projects; ++ p)
		best.push_back(wczytaj());


	a = best.begin();
	while((next = wczytaj()))
	{
		best.push_back(next);
		n = a;
		++ n;
		while(n != best.end() && *a >= *n)
		{
			++ a;
			++ n;
		}

		if(a != best.begin())
		{
			n = a;
			-- n;
		}

		best.erase(a);
		a = n;
	}

	for(a = best.begin(); a != best.end(); ++ a)
		wypisz(*a);

	return 0;
}
