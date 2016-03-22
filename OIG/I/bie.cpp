/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>

int checker [ 505 ],
	checkers,
	maxQuantity,
	quantity,
	length,
	last;

int main ( void )
{
	scanf ( "%d", & checkers );
	for ( int c = 0; c < checkers; ++ c )
	{
		scanf ( "%d", & length );
		++ checker [ length ];
	}

	for ( int l = 500, f = 500; l > 0 && f > 0; -- l )
	{
		while ( l > 0 && ! checker [ l ] )
			-- l;

		if ( f > l )
		{
			quantity = 0;
			f = l;
			last = 0;
		}

		while ( f > 0 && 2 * f > l )
		{
			if  ( checker [ f ] )
				last = f;

			quantity += checker [ f -- ];
		}

		if ( quantity > maxQuantity )
			maxQuantity = quantity + ( checker [ f ] && last + f > l );

		quantity -= checker [ l ];
	}

	printf ( "%d\n", maxQuantity );
	return 0;
}

