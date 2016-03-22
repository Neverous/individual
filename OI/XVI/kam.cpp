/*		2008
Maciej Szeptuch
XIV LO WROCŁAW
Zadanie: KAMYKI
*/
#include <cstdio>

int tests,	// ilość testów
	heaps,	// ilość stosików kamieni
	now,	// aktualna
	result,	// wynik
	last, // ostatni
	tmp; // opcja A/B

int main ( void )
{
	scanf ( "%d", & tests );	// Wczytywanie ilości testów
	for ( int t = 0; t < tests; ++ t )
	{
		result = tmp = last = 0;
		scanf ( "%d", & heaps );	// Wczytywanie ilości stosów

		if ( heaps % 2 == 0 ) // sprawdzanie opcji
			tmp = 1;

		for ( int h = 0; h < heaps; ++ h )
		{
			scanf ( "%d", & now );

			if ( h % 2 == tmp )	// coś w stylu Staircase NIM
				result ^= now - last; // ...

			last = now;
		}
		printf ( "%s\n", ( result ) ? "TAK" : "NIE" );	// Wynik
	}
	return 0;
}

