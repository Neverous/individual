/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

int statements,
	connections,
	start,
	end,
	question;

std :: vector < int > graph [ 100010 ],
					  reverseGraph [ 100010 ];

int sort [ 100010 ],
	visited [ 100010 ],
	component [ 100010 ],
	weight [ 100010 ],
	componentWeight [ 100010 ],
	components,
	sum,
	number;

void dfs ( int statement );
inline int findSCC ( void );
int dfsSCC ( int statement, int color );

int main ( void )
{
	scanf ( "%d %d", & statements, & connections );

	for ( int s = 0; s < statements; ++ s )
		scanf ( "%d", & weight [ s ] );

	for ( int c = 0; c < connections; ++ c )
	{
		scanf ( "%d %d", & start, & end );
		-- start;
		-- end;
		graph [ start ] . push_back ( end );
		reverseGraph [ end ] . push_back ( start );
	}

	for ( int s = 0; s < statements; ++ s )
		if ( ! visited [ s ] )
			dfs ( s );

	components = findSCC ( );
	int s = 0;
	for ( int c = 1; c < components; ++ c )
		if ( ! visited [ c ] )
		{
			sum += componentWeight [ c ];
			++ number;
		}
		else
			sort [ s ++ ] = componentWeight [ c ];

	std :: sort ( sort, sort + s, std :: greater < int >() );

	for ( int x = 0; x < s && ( ( double ) sum / ( double ) number < ( double ) ( sum + sort [ x ] ) / ( double ) ( number + 1 ) ); ++ x )
	{
		sum += sort [ x ];
		++ number;
	}

	printf ( "%0.5lf\n", ( double ) sum / ( double ) number );

	return 0;
}

void dfs ( int statement )
{
	static int colorize = 1;

	visited [ statement ] = -1;

	for ( unsigned int s = 0; s < graph [ statement ] . size ( ); ++ s )
		if ( ! visited [ graph [ statement  ] [ s ] ] )
			dfs ( graph [ statement ] [ s ] );

	visited [ statement ] = colorize ++;
}

inline int findSCC ( void )
{
	int components = 1;
	for ( int s = 0; s < statements; ++ s )
	{
		sort [ visited [ s ] ] = s;
		visited [ s ] = 0;
		componentWeight [ s ] = -5000;
	}

	for ( int s = statements; s > 0; -- s )
	{
		if ( component [ sort [ s ] ] )
			continue;

		dfsSCC ( sort [ s ], components );
		++ components;
	}

	return components;
}

int dfsSCC ( int statement, int color )
{
	int result = 1;
	component [ statement ] = color;

	if ( weight [ statement ] > componentWeight [ color ] )
		componentWeight [ color ] = weight [ statement ];

	for ( unsigned int s = 0; s < reverseGraph [ statement ] . size ( ); ++ s )
		if ( ! component [ reverseGraph [ statement ] [ s ] ] )
			result += dfsSCC ( reverseGraph [ statement ] [ s ], color );

		else if ( component [ reverseGraph [ statement ] [ s ] ] != color )
			++ visited [ color ];

	return result;
}

