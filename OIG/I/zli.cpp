/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>

int tab [ 300 ];

char sign;

int main ( void )
{
	scanf ( "%*d " );

	while ( scanf ( "%c", & sign ) != -1 )
		++ tab [ ( int ) sign ];

	for ( int i = 'a'; i <= 'z'; ++ i )
		if ( tab [ i ] > 0 )
			printf ( "%c %d\n", i, tab [ i ] );

	for ( int i = 'A'; i <= 'Z'; ++ i )
		if ( tab [ i ] > 0 )
			printf ( "%c %d\n", i, tab [ i ] );

	return 0;
}

