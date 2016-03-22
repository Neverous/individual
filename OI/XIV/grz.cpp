#include <cstdlib>
#include <cstdio>
#include <queue>

using namespace std;

int size,
	tab [ 1010 ] [ 1010 ],
	res,
	grz,
	dol,
	tmp;

bool visited [ 1010 ] [ 1010 ];

pair < int, int > act;

inline void solve ( void );
char bfs ( int h, int w );

int main ( void )
{
	scanf ( "%d", & size );

	for ( int h = 0; h < size; ++ h )
		for ( int w = 0; w < size; ++ w )
			scanf ( "%d", & tab [ h ] [ w ] );

	solve ( );
    return 0;
}

inline void solve ( void )
{
	for ( int h = 0; h < size; ++ h )
		for ( int w = 0; w < size; ++ w )
		{
			if ( visited [ h ] [ w ] )
				continue;
			tmp ++;
			res = bfs ( h, w );

			if ( res == 1 )
				++ grz;

			else if ( res == 2 )
				++ dol;
		}
	if ( tmp == 1 )
	{
		printf ( "1 1\n" );
		return;
	}
	printf ( "%d %d\n", grz, dol );
}

char bfs ( int h, int w )
{
	priority_queue < pair < int, int > > stack;
	bool max = false,
		 min = false;

	int actV = tab [ h ] [ w ];

	stack . push ( pair < int, int > ( h, w ) );
	visited [ h ] [ w ] = true;

	while ( ! stack . empty ( ) )
	{
		act = stack . top ( );
		stack . pop ( );

		for ( int i = -1; i < 2; ++ i )
			for ( int j = -1; j < 2; ++ j )
			{
				if ( ( j == 0 && i == 0 ) || act . first + i < 0 || act . second + j < 0 || act . first + i >= size || act . second + j >= size )
					continue;

				if ( ! min && tab [ act . first + i ] [ act . second + j ] < actV )
					min = true;

				if ( ! max && tab [ act . first + i ] [ act . second + j ] > actV )
					max = true;

				if ( tab [ act . first + i ] [ act . second + j ] == actV && ! visited [ act . first + i ] [ act . second + j ] )
				{
					stack . push ( pair < int, int > ( act . first + i, act . second + j ) );
					visited [ act . first + i ] [ act . second + j ] = true;
				}
			}
	}

	if ( min && ! max )
		return 1;

	if ( ! min && max )
		return 2;

	return 0;
}

