#include <cstdio>
#include <cstdlib>

int banknoty [ 5 ] = { 20000, 10000, 5000, 2000, 1000 },
	monety [ 9 ] = { 500, 200, 100, 50, 20, 10, 5, 2, 1 },
	zlotych,
	groszy,
	wynik;

int main ( void )
{
	scanf ( "%d %d", & zlotych, & groszy );
	zlotych = zlotych * 100 + groszy;

	for ( int p = 0; p < 5 && zlotych >= 1000; ++ p )
	{
		while ( banknoty [ p ] > zlotych )
			++ p;

		wynik += zlotych / banknoty [ p ];
		zlotych %= banknoty [ p ];
	}

	printf ( "%d ", wynik );
	wynik = 0;

	for ( int p = 0; p < 9 && zlotych > 0; ++ p )
	{
		while ( monety [ p ] > zlotych )
			++ p;

		wynik += zlotych / monety [ p ];
		zlotych %= monety [ p ];
	}

	printf ( "%d\n", wynik );

    return 0;
}

