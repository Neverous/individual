#include <cstdio>
#include <cstdlib>
#include <queue>
#include <vector>

using namespace std;

priority_queue < pair < int, int > > que;
pair < int, int > act;
vector < int > graph [ 1000010 ];

int timeFirst [ 1000010 ],
	timeSecond [ 1000010 ],
	verts,
	edges,
	start,
	end;

void bfs ( void )
{
	que . push ( make_pair ( 0, 0 ) );
	while ( ! que . empty ( ) )
	{
		act = que . top ( );
		que . pop ( );
		act . first = - act . first;

		if ( timeFirst [ act . second ] <= act . first )
			continue;

		timeFirst [ act . second ] = act . first;

		for ( unsigned int s = 0; s < graph [ act . second ] . size ( ); ++ s )
		{
			if ( timeFirst [ graph [ act . second ] [ s ] ] > act . first + 1 )
				que . push ( make_pair ( - ( act . first + 1 ), graph [ act . second ] [ s ] ) );
		}
	}

	que . push ( make_pair ( 0, 0 ) );
	while ( ! que . empty ( ) )
	{
		act = que . top ( );
		que . pop ( );

		if ( timeSecond [ act . second ] >= act . first )
			continue;

		timeSecond [ act . second ] = act . first;

		for ( unsigned int s = 0; s < graph [ act . second ] . size ( ); ++ s )
		{
			if ( timeSecond [ graph [ act . second ] [ s ] ] < act . first + 1 )
				que . push ( make_pair ( act . first + 1, graph [ act . second ] [ s ] ) );
		}
	}

};

int main ( void )
{
	scanf ( "%d %d", & verts, & edges );
	for ( int e = 0; e < edges; ++ e )
	{
		scanf ( "%d %d", & start, & end );
		-- start;
		-- end;
		graph [ start ] . push_back ( end );
		timeFirst [ start ] = 1000010;
		timeSecond [ start ] = -1;
		timeFirst [ end ] = 1000010;
		timeSecond [ end ] = -1;
	}

	bfs ( );

	printf ( "%s\n", timeFirst [ verts - 1 ] == timeSecond [ verts - 1 ] ? "TAK" : "NIE" );
	printf ( "%d %d\n", timeFirst [ verts - 1 ], timeSecond [ verts - 1 ] );

#ifdef WIN$HIT
	system ( "pause" );
#endif
    return 0;
}

