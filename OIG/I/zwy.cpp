/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>

int tab [ 30 ],
	people,
	max;

int main ( void )
{
	scanf ( "%d", & people );

	for ( int p = 0; p < people; ++ p )
	{
		scanf ( "%d", & tab [ p ] );
		max = tab [ p ] > max ? tab [ p ] : max;
	}

	for ( int p = 0; p < people; ++ p )
		if ( tab [ p ] == max )
			printf ( "%c", 'A' + p );

	printf ( "\n" );

	return 0;
}

