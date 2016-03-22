/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int cities,
	roads,
	from,
	to,
	cost,
	findTab [ 7007 ];

bool result [ 300030 ];

vector < pair < pair < int, int >, pair < int, int > > > edges;

int find ( int & city );
bool Union ( pair < int, int > & edge );
void solve ( void );

int main ( void )
{
	scanf ( "%d %d", & cities, & roads );

	for ( int r = 0; r < roads; ++ r )
	{
		scanf ( "%d %d %d", & from, & to, & cost );
		-- from;
		-- to;

		edges . push_back ( make_pair ( make_pair ( cost, r ), make_pair ( from, to ) ) );
	}
	solve ( );
	return 0;
}

void solve ( void )
{
	for ( int c = 0; c < cities; ++ c )
		findTab [ c ] = c;

	sort ( edges . begin ( ), edges . end ( ) );

	for ( unsigned int e = 0; e < edges . size ( ); ++ e )
	{
		for ( unsigned int ee = e; edges [ e ] . first . first == edges [ ee ] . first . first; ++ ee )
			if ( find ( edges [ ee ] . second . first ) != find ( edges [ ee ] . second . second ) )
				result [ edges [ ee ] . first . second ] = true;

		Union ( edges [ e ] . second );
	}

	for ( int r = 0; r < roads; ++ r )
		printf ( "%s\n", result [ r ] ? "TAK" : "NIE" );

}

int find ( int & city )
{
	if ( findTab [ city ] == city )
		return city;

	findTab [ city ] = find ( findTab [ city ] );

	return findTab [ city ];
}

bool Union ( pair < int, int > & edge )
{
	int first = find ( edge . first ),
		second = find ( edge . second );

	if ( first == second )
		return false;

	if ( first < second )
		findTab [ second ] = first;

	else
		findTab [ first ] = second;

	return true;
}

