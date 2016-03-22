/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>
#include <vector>
#include <algorithm>

std :: vector < int > graph [ 100010 ];
int verts,
	edges,
	from,
	to,
	result,
	flag,
	visited [ 100010 ],
	fathers [ 100010 ],
	low [ 100010 ],
	resultTab [ 100010 ];

void dfs ( int vertex, int father, int time )
{
	int flag = 0;
	fathers [ vertex ] = father;
	low [ vertex ] = visited [ vertex ] = time;
	for ( unsigned int s = 0; s < graph [ vertex ] . size ( ); ++ s )
	{
		if ( ! visited [ graph [ vertex ] [ s ] ] )
		{
			dfs ( graph [ vertex ] [ s ], vertex, time + 1 );
			if ( low [ graph [ vertex ] [ s ] ] >= visited [ vertex ] )
				++ flag;
		}

		if ( graph [ vertex ] [ s ] != father )
			low [ vertex ] = ( low [ vertex ] < low [ graph [ vertex ] [ s ] ] ) ? low [ vertex ] : low [ graph [ vertex ] [ s ] ];
	}

	if ( ( father != -1 && flag > 0 ) || ( father == -1 && flag > 1 ) )
		resultTab [ result ++ ] = vertex + 1;

}

int main ( void )
{
	scanf ( "%d %d", & verts, & edges );
	for ( int e = 0; e < edges; ++ e )
	{
		scanf ( "%d %d", & from, & to );
		-- from;
		-- to;

		graph [ from ] . push_back ( to );
		graph [ to ] . push_back ( from );
	}

	for ( int v = 0; v < verts; ++ v )
		if ( ! visited [ v ] )
			dfs ( v, -1, 1 );

	printf ( "%d\n", result );

	std :: sort ( resultTab, resultTab + result );
	for ( int r = 0; r < result; ++ r )
		printf ( "%d ", resultTab [ r ] );

	printf ( "\n" );
}

