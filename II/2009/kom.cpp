#include <cstdio>
#include <cstdlib>
#include <queue>

int size,
	towers,
	sight,
	x,
	y,
	result,
	act;

std :: queue < int > que;

bool field [ 1001 ] [ 1001 ];

void bfs ( int x, int y )
{
	que = std :: queue < int > ( );
	que . push ( 1001 * x + y );

	while ( ! que . empty ( ) )
	{
		act = que . front ( );
		que . pop ( );

		if ( field [ act / 1001 ] [ act % 1001 ] )
			continue;

		field [ act / 1001 ] [ act % 1001 ] = true;

		if ( act / 1001 - 1 >= 0 &&
			 ! field [ act / 1001 - 1 ] [ act % 1001 ] )
			que . push ( ( act / 1001 - 1 ) * 1001 + act % 1001 );

		if ( act / 1001 + 1 < size  &&
			 ! field [ act / 1001 + 1 ] [ act % 1001 ] )
			que . push ( ( act / 1001 + 1 ) * 1001 + act % 1001 );

		if ( act % 1001 - 1 >= 0 &&
			 ! field [ act / 1001 ] [ act % 1001 - 1 ] )
			que . push ( ( act / 1001 ) * 1001 + act % 1001 - 1 );

		if ( act % 1001 + 1 < size  &&
			 ! field [ act / 1001 ] [ act % 1001 + 1 ] )
			que . push ( ( act / 1001 ) * 1001 + act % 1001 + 1 );
	}
}

void setTower ( int x, int y, int sight )
{
	for ( int h = sight; h >= 0; -- h )
		for ( int w = y - sight + h; w <= y + sight - h; ++ w )
			if ( x + h >= 0 &&
				 x + h <= 1001 &&
				 w >= 0 &&
				 w <= 1001 )
			field [ x + h ] [ w ] = true;

	for ( int h = sight; h > 0; -- h )
		for ( int w = y - sight + h; w <= y + sight - h; ++ w )
			if ( x - h >= 0 &&
				 x - h <= 1001 &&
				 w >= 0 &&
				 w <= 1001 )
			field [ x - h ] [ w ] = true;

}

int main ( void )
{
	scanf ( "%d %d %d", & size, & towers, & sight );

	for ( int t = 0; t < towers; ++ t )
	{
		scanf ( "%d %d", & x, & y );
		-- x;
		-- y;
		setTower ( x, y, sight );
	}

	for ( int x = 0; x < size; ++ x )
		for ( int y = 0; y < size; ++ y )
			if ( ! field [ x ] [ y ] )
			{
				++ result;
				bfs ( x, y );
			}
	printf ( "%d\n", result );

    return 0;
}

