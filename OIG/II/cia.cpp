/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>

long long unsigned int number,
					   position = 1,
					   tmp = 1,
					   what = 1;

short tab [ 11000000 ];

int main ( void )
{
	scanf ( "%llu", & number );

	if ( number < 3 )
	{
		printf ( "%llu\n", number );
		return 0;
	}

	tab [ 1 ] = 1;
	tab [ 2 ] = 2;

	for ( int t = 2, t2 = 2; t < 1100000 && t2 < 11000000 ; ++ t )
		for ( int q = tab [ t ]; t2 < 11000000 && q; -- q )
			tab [ t2 ++ ] = t;

	if ( number < 11000000 )
	{
		printf ( "%d\n", tab [ number ] );
		return 0;
	}

	while ( position < number )
	{
		position += tab [ tmp ] * tmp;
		what += tab [ tmp ++ ];
	}

	-- tmp;

	what += ( number - position + tmp * tab [ tmp ] ) / tmp - tab [ tmp ];

	printf ( "%llu\n", what );
	return 0;
}

