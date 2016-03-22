/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>

int tables [ 30030 ],
	checked [ 30030 ],
	people,
	person;

int PFS ( void ) // PSEUDO GRAPH SEARCH ^^
{
	int result = 0;

	for ( int p = 0; p < people; ++ p )
	{
		if ( checked [ p ] )
			continue;

		for ( int n = p; ! checked [ n ]; n = tables [ n ] )
			 checked [ n ] = true;

		++ result;
	}

	return result;
}

int main ( void )
{
	scanf ( "%d", & people );

	for ( int p = 0; p < people; ++ p )
	{
		scanf ( "%d", & person );
		-- person;

		tables [ p ] = person;
	}

	printf ( "%d\n", PFS ( ) );
	return 0;
}

