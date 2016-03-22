/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#define Point std :: pair < int, int >
#define Elem std :: pair < int, Point >

int verts,
	edges,
	from,
	to,
	cost,
	result,
	agent [ 7007 ],
	matched;

Elem edgesTab [ 1000010 ];

int unionFind ( int who );
inline bool unionUnion ( int A, int B );
inline void preprocess ( void );

int main ( void )
{
	preprocess ( );
	scanf ( "%d %d", & verts, & edges );
	for ( int e = 0; e < edges; ++ e )
	{
		scanf ( "%d %d %d", & from, & to, & cost );
		-- from;
		-- to;
		edgesTab [ e ] = Elem ( cost, Point ( from, to ) );
	}

	std :: sort ( edgesTab, edgesTab + edges );

	for ( int e = 0; e < edges && matched < verts - 1; ++ e )
		if ( unionUnion ( edgesTab [ e ] . second . first, edgesTab [ e ] . second . second ) )
		{
			++ matched;
			result += edgesTab [ e ] . first;
		}

	printf ( "%d\n", result );
	return 0;
}

inline void preprocess ( void )
{
	for ( int v = 0; v < 7007; ++ v )
		agent [ v ] = v;
}

int unionFind ( int who )
{
	if ( agent [ who ] == who )
		return who;

	return agent [ who ] = unionFind ( agent [ who ] );
}

bool unionUnion ( int A, int B )
{
	int agentA = unionFind ( A ),
		agentB = unionFind ( B );

	if ( agentA == agentB )
		return false;

	if ( agentA < agentB )
		agent [ agentB ] = agentA;

	else
		agent [ agentA ] = agentB;

	return true;
}

