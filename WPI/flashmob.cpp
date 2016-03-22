/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>
#include <vector>

using namespace std;

int graph [ 100010 ],
	people,
	bulb,
	questions,
	who,
	when;

vector < int > component [ 100010 ];
pair < int, int > where [ 100010 ];

int main ( void )
{
	scanf ( "%d", & people );
	for ( int  p = 0; p < people; ++ p )
	{
		scanf ( "%d", & bulb );
		graph [ p ] = -- bulb;
	}

	for ( int p = 0, c = 0, tmp, act; p < people; ++ p )
	{
		act = p;
		while ( graph [ act ] != -1 )
		{
			component [ c ] . push_back ( act );
			where [ act ] = pair < int, int > ( c, component [ c ] . size ( ) - 1 );
			tmp = graph [ act ];
			graph [ act ] = -1;
			act = tmp;
		}
		++ c;
	}

	scanf ( "%d", & questions );
	for ( int q = 0; q < questions; ++ q )
	{
		scanf ( "%d %d", & who, & when );
		-- who;
		when += where [ who ] . second;
		when %= component [ where [ who ] . first ] . size ( );
		printf ( "%d\n", component [ where [ who ] . first ] [ when ] + 1 );
	}
	return 0;
}

