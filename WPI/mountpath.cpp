/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>

int tripPoints,
	a,
	b,
	result,
	weight [ 1000010 ];

int main ( void )
{
	scanf ( "%d", & tripPoints );
	for ( int t = 1; t < tripPoints; ++ t )
	{
		scanf ( "%d %d", & a, & b );
		++ weight [ -- a ];
		++ weight [ -- b ];
	}

	for ( int t = 0; t < tripPoints; ++ t )
		result += ( weight [ t ] == 1 );

	result = ( result + 1 ) / 2;

	printf ( "%d\n", result );
	return 0;
}

