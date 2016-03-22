/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include <cstdio>
#define INF 100000000
#define minimum(a,b) ( ( (a)>(b) ) ? (b) : (a) )
//przepraszam za makro ale bez niego to przerost kodu nad problemem ^^

int cities,
	roads,
	projects,
	from,
	to,
	cost,
	costs [ 101 ] [ 101 ];

int main ( void )
{
	scanf ( "%d %d %d", & cities, & roads, & projects );
	for ( int c = 0; c < cities; ++ c )
		for ( int i = 0; i < cities; ++ i )
			costs [ c ] [ i ] = c == i ? 0 : INF;

	for ( int r = 0; r < roads; ++ r )
	{
		scanf ( "%d %d %d", & from, & to, & cost );
		-- from;
		-- to;
		costs [ from ] [ to ] = minimum ( cost, costs [ from ] [ to ] );
		costs [ to ] [ from ] = minimum ( cost, costs [ to ] [ from ] );
	}

	for ( int c = 0; c < cities; ++ c )
		for ( int f = 0; f < cities; ++ f )
			if ( costs [ f ] [ c ] < INF )
				for ( int t = 0; t < cities; ++ t )
					if ( costs [ c ] [ t ] < INF )
						costs [ f ] [ t ] = minimum ( costs [ f ] [ c ] + costs [ c ] [ t ], costs [ f ] [ t ] );	//FW

	for ( int p = 0; p < projects; ++ p )
	{
		scanf ( "%d %d %d", & from, & to, & cost );
		-- from;
		-- to;
		if ( costs [ 0 ] [ cities - 1 ] > minimum ( costs [ 0 ] [ from ] + cost + costs [ to ] [ cities - 1 ], costs [ 0 ] [ to ] + cost + costs [ from ] [ cities - 1 ] ) )
		{
			for ( int i = 0; i < cities; ++ i )
				for ( int j = i; j < cities; ++ j )
				{
					costs [ i ] [ j ] = minimum ( costs [ i ] [ j ], costs [ i ] [ to ] + cost + costs [ from ] [ j ] );
					costs [ i ] [ j ] = minimum ( costs [ i ] [ j ], costs [ i ] [ from ] + cost + costs [ to ] [ j ] );

					costs [ j ] [ i ] = costs [ i ] [ j ];
				}

			costs [ from ] [ to ] = cost;
			costs [ to ] [ from ] = cost;
			printf ( "1\n" );
		}
		else
			printf ( "0\n" );

	}
	return 0;
}

