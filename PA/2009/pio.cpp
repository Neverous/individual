/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector < vector < pair < pair < int, int >, pair < pair < bool, int >, int > > > > tab;
vector < pair < int, pair < int, int > > > toSort;

int size,
	black,
	questions,
	row,
	startColumn,
	endColumn,
	x1,y1,
	x2,y2;

pair < int, int > findUnion ( pair < int, int > P )
{
	if ( tab [ P . first ] [ P . second ] . first != P )
		tab [ P . first ] [ P . second ] . first = findUnion ( tab [ P . first ] [ P . second ] . first );

	return tab [ P . first ] [ P . second ] . first;
}

void unionUnion ( pair < int, int > A, pair < int, int > B )
{
	pair < int ,int > Fa = findUnion ( A ),
					  Fb = findUnion ( B );

	if ( Fa == Fb )
		return;

	if ( Fa . first < Fb . first || Fa . second < Fb . second )
		tab [ B . first ] [ B . second ] . first = Fa;

	else
		tab [ A . first ] [ A . second ] . first = Fb;

}

int main ( void )
{
	scanf ( "%d %d %d", & size, & black, & questions );
	tab . resize ( size + 1 );
	for ( int b = 0; b < black; ++ b )
	{
		scanf ( "%d %d %d", & row, & startColumn, & endColumn );
		-- row;
		-- startColumn;
		-- endColumn;
		toSort . push_back ( pair < int, pair < int, int > > ( row, pair < int, int > ( startColumn, endColumn ) ) );
	}

	sort ( toSort . begin ( ), toSort . end ( ) );

	for ( int r = 0, p = 0, c = 0; r < size; ++ r )
	{
		c = 0;
		while ( p < (int) toSort . size ( ) && toSort [ p ] . first < r )
			++ p;

		for ( ; p < (int) toSort . size ( ) && toSort [ p ] . first == r; ++ p )
		{
			if ( toSort [ p ] . second . first > c )
			{
				tab [ r ] . push_back ( make_pair ( make_pair ( 0, toSort [ p ] . second . first - 1 ), make_pair ( make_pair ( 0, r ), 0 ) ) );
				c = toSort [ p ] . second . second + 1;
			}

			tab [ r ] . push_back ( make_pair ( make_pair ( toSort [ p ] . second . first, toSort [ p ] . second . second ), make_pair ( make_pair ( 1, r ), toSort [ p ] . second . first ) ) );

		}

		if ( c <= size - 1 )
			tab [ r ] . push_back ( make_pair ( make_pair ( c, size - 1 ), make_pair ( make_pair ( 0, r ), c ) ) );
	}
	/*
		for ( int c = 0; c < size; ++ c )
		{
			while ( p < (int) toSort . size ( ) && toSort [ p ] . first == r && toSort [ p ] . second . second < c )
				++ p;

			if ( p < (int) toSort . size ( ) &&  toSort [ p ] . first == r && toSort [ p ] . second . first <= c && toSort [ p ] . second . second >= c )
				tab [ r ] [ c ] . second = true;

			tab [ r ] [ c ] . first = pair < int, int > ( r, c );
		}
	}*/

	for ( int r = 0; r < size; ++ r )
		for ( int c = 0; c < size; ++ c )
		{

			if ( c - 1 >= 0 && tab [ r ] [ c ] . second == tab [ r ] [ c - 1 ] . second )
				unionUnion ( pair < int, int > ( r, c ), pair < int, int > ( r, c - 1 ) );

			if ( r - 1 >= 0 && tab [ r ] [ c ] . second == tab [ r - 1 ] [ c ] . second )
				unionUnion ( pair < int, int > ( r, c ), pair < int, int > ( r - 1, c ) );

			if ( r - 1 >= 0 && c - 1 >= 0 && tab [ r ] [ c ] . second == tab [ r - 1 ] [ c - 1 ] . second )
				unionUnion ( pair < int, int > ( r, c ), pair < int, int > ( r - 1, c - 1 ) );

			if ( r - 1 >= 0 && c + 1 < size && tab [ r ] [ c ] . second == tab [ r - 1 ] [ c + 1 ] . second )
				unionUnion ( pair < int, int > ( r, c ), pair < int, int > ( r - 1, c + 1 ) );
		}

	for ( int q = 0; q < questions; ++ q )
	{
		scanf ( "%d %d %d %d", & x1, & y1, & x2, & y2 );
		-- x1,
		-- y1;
		-- x2;
		-- y2;

		printf ( "%s\n", findUnion ( pair < int, int > ( x1, y1 ) ) == findUnion ( pair < int, int > ( x2, y2 ) ) ? "TAK" : "NIE" );
	}

	return 0;
}

