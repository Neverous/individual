/* 2009
Maciej Szeptuch
XIV LO Wroc�aw
*/
#include <cstdio>
#include <queue>
#include <vector>
#define que_component pair < int, int >
#define que_elem pair < int, que_component >

using namespace std;

int width,
	height,
	sourceX,
	sourceY,
	destSize,
	field [ 1010 ][ 1010 ],
	lastHeight;

bool result [ 1010 ] [ 1010 ],
	 bylo [ 1010 ] [ 1010 ];

priority_queue < que_elem, vector < que_elem >, greater < que_elem > > que;
que_elem act;

void solve ( void )
{
	que . push ( que_elem ( field [ sourceY ] [ sourceX ], que_component ( sourceY, sourceX ) ) );
	bylo [ sourceY ] [ sourceX ] = true;
	while ( ! que . empty ( ) )
	{
		act = que . top ( );
		que . pop ( );

		if ( lastHeight < act . first )
		{
			if ( destSize <= 0 )
				break;

			lastHeight = act . first;
		}
		result [ act . second . first ] [ act . second . second ] = true;
		-- destSize;

		for ( int  i = -1; i < 2; ++ i )
			for ( int  j = -1; j < 2; ++ j )
				if ( act . second . first + i >= 0 &&
					 act . second . first + i < height &&
					 act . second . second + j >= 0 &&
					 act . second . second + j < width &&
					 ! bylo [ act . second . first + i ] [ act . second . second + j ] )
				{
					bylo [ act . second . first + i ] [ act . second . second + j ] = true;
					que . push ( que_elem ( field [ act . second . first + i ] [ act . second . second + j ],
							 				que_component ( act . second . first + i, act . second . second + j ) ) );
				}
	}
}

int main ( void )
{
	scanf ( "%d %d %d %d %d", & width, & height, & sourceX, & sourceY, & destSize );
	-- sourceX;
	-- sourceY;
	for ( int h = 0; h < height; ++ h )
		for ( int w = 0; w < width; ++ w )
			scanf ( "%d", & field [ h ] [ w ] );

	solve ( );

	for ( int h = 0; h < height; ++ h )
	{
		for ( int w = 0; w < width; ++ w )
			printf ( "%c", result [ h ] [ w ] ? 'x' : '.' );

		printf ( "\n" );
	}
	return 0;
}

