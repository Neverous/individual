/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>
int tests,
	dices,
	need;

double tab [ 2000 ] [ 2000 ];

double dice ( int dices, int need )
{
	if ( dices < 2000 && need < 2000 && tab [ dices ] [ need ] )
		return tab [ dices ] [ need ];

	if ( dices == 1 )
	{
		if ( need >= 1 and need <= 6 )
			return 1.0 / 6.0;

		else
			return 0;
	}

	if ( need > 6 * dices || need < dices )
		return 0;

	double result = 0;

	for ( int i = 1; i <= need && i <= 6; ++ i )
		result += dice ( 1, i ) * dice ( dices - 1, need - i );

	if ( dices < 2000 && need < 2000 )
		tab [ dices ] [ need ] = result;

	return result;
}

int main ( void )
{
	scanf ( "%d", & tests );
	for ( int t = 0; t < tests; ++ t )
	{
		scanf ( "%d %d", & dices, & need );
		printf ( "%d\n", (int) ( dice ( dices, need ) * 100 ) );
	}

	return 0;
}

