/* Maciej Szeptuch 2008
XIV LO Wrocław
*/

#include <cstdio>
#include <algorithm>
#include <cstdlib>

using namespace std;

int maxWeight,
	participants,
	tab [ 30030 ];

int solve ( void )
{
	int result = 0;
	sort ( tab, tab + participants );
	for ( int s = 0, e = participants - 1; s <= e; ++ s )
	{
		while ( s < e && tab [ s ] + tab [ e ] > maxWeight  )
		{
			-- e;
			++ result;
		}

		++ result;

		if ( s == e )
			break;

		-- e;
	}

	return result;
}

int main ( void )
{
	scanf ( "%d", & maxWeight );
	scanf ( "%d", & participants );

	for ( int p = 0; p < participants; ++ p )
		scanf ( "%d", & tab [ p ] );

	printf ( "%d\n", solve ( ) );
	return 0;
}

