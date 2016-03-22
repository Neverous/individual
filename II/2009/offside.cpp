#include <cstdio>
#include <cstdlib>

int result = 10,
	playersA [ 15 ],
	playersB [ 15 ],
	one;

int main ( void )
{
	for ( int p = 0; p < 11; ++ p )
		scanf ( "%d", & playersA [ p ] );

	for ( int p = 0; p < 11; ++ p )
		scanf ( "%d", & playersB [ p ] );

	for ( int p = 1; p < 11; ++ p )
	{
		one = 0;
		if ( playersA [ p ] > 52 )
			continue;

		if ( playersA [ p ] >= playersA [ 0 ] )
			continue;

		for ( int i = 0; i < 11; ++ i )
			if ( playersB [ i ] <= playersA [ p ] )
				one ++;

		if ( one > 1 )
			continue;

		-- result;
	}

	printf ( "%d", result );

    return 0;
}

