/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>

int size,
	cost [ 2020 ];

int bsearch ( int start, int end )
{
	if ( start == end )
		return cost [ start ];

	if ( start > end )
		return 0;

	int middle = ( start + end ) / 2,
		worst = cost [ middle ] + bsearch ( middle + 1, end ),
		worst2,
		second;

	second = cost [ middle ] + bsearch ( start, middle - 1 );
	worst = worst < second ? second : worst;

	worst2 = worst;

	if ( ( end - start ) % 2 )
	{
		++ middle;
		second = cost [ middle ] + bsearch ( start, middle - 1 );
		worst2 = worst2 < second ? second : worst2;

		second = cost [ middle ] + bsearch ( middle + 1, end );
		worst2 = worst2 < second ? second : worst2;
	}
	return worst < worst2 ? worst : worst2;
}

int main ( void )
{
	scanf ( "%d", & size );
	for ( int s = 0; s < size; ++ s )
		scanf ( "%d", & cost [ s ] );

	printf ( "%d", bsearch ( 0, size - 1 ) );
	return 0;
}

