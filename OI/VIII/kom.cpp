/*		2009
Maciej Szeptuch
XIV LO WROCŁAW
*/
#include <cstdio>
#include <vector>

using namespace std;

bool value [ 16016 ],
	 color [ 16016 ],
	 reverseColor [ 16016 ];

int verts,
	edges,
	st,
	nd,
	list2;

vector < int > graph [ 16016 ],
			   reverse [ 16016 ],
			   list;

int opposite ( int vert )
{
	return vert ^ 1;
}

bool setTrue ( int vert )
{
	if ( color [ vert ] && value [ vert ] )
		return false;

	color [ vert ] = true;
	value [ vert ] = false;

	return true;
}

bool setFalse ( int vert )
{
	if ( color [ vert ] && ! value [ vert ] )
		return false;

	color [ vert ] = true;
	if ( value [ vert ] )
		return true;
	value [ vert ] = true;

	for ( int v = 0; v < graph [ vert ] . size ( ) ; ++ v )
	{
		if ( ! value [ graph [ vert ] [ v ] ] )
			if ( ! setTrue ( opposite ( graph [ vert ] [ v ] ) ) || ! setFalse ( graph [ vert ] [ v ] ) )
				return false;
	}

	return true;
}

void dfsTopOrder ( int vert )
{
	color [ vert ] = true;

	for ( int v = 0; v < graph [ vert ] . size ( ); ++ v )
	{
		if ( color [ graph [ vert ] [ v ] ] )
			continue;
		dfsTopOrder ( graph [ vert ] [ v ] );
	}
	list . push_back ( vert );
}

void dfsResult ( int vert )
{
	reverseColor [ vert ] = true;

	for ( int v = 0; v < reverse [ vert ] . size ( ); ++ v )
	{
		if ( reverseColor [ reverse [ vert ] [ v ] ] )
			continue;

		dfsResult ( reverse [ vert ] [ v ] ) ;
	}
}

bool solve ( void )
{
	for ( int v = 0; v < 2 * verts; ++ v )
	{
		if ( color [ v ] )
			continue;

		dfsTopOrder ( v );
	}
	for ( int v = 0; v < 2 * verts; ++ v )
		color [ v ] = false;

	for ( int v = list . size ( ) - 1; v >= 0; -- v )
	{
		if ( reverseColor [ list [ v ] ] )
			continue;

		dfsResult ( list [ v ] );

		if ( ! color [ list [ v ] ] )
			if ( ! setTrue ( list [ v ] ) || ! setFalse ( opposite ( list [ v ] ) ) )
				return false;
	}

	for ( int v = 0; v < 2 * verts; v += 2 )
		if ( value [ v ] == value [ opposite ( v ) ] )
			return false;

	for ( int v = 0; v < 2 * verts; ++ v )
		if ( value [ v ] )
			printf ( "%d\n", v + 1 );
	return true;
}

int main ( void )
{
	scanf ( "%d %d", & verts, & edges );

	for ( int e = 0; e < edges; ++ e )
	{
		scanf ( "%d %d", & st, & nd );
		-- st;
		-- nd;
		graph [ st ] . push_back ( opposite ( nd ) );
		reverse [ opposite ( nd ) ] . push_back ( st ); //REV
		graph [ nd ] . push_back ( opposite ( st ) );
		reverse [ opposite ( st ) ] . push_back ( nd ); //REV
	}

	if ( ! solve ( ) )
		printf ( "NIE\n" );

	return 0;
}

