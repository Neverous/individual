/* Maciej Szeptuch
 * XIV LO Wrocław
 * 2009
 */
#include <cstdio>

int length,
	max,
	count [ 26 ];

char letter [ 2 ],
	 word [ 1000001 ],
	 maxLetter;

int main ( void )
{
	scanf ( "%d %s", & length, letter );
	scanf ( "%s", word );
	for ( int l = 0; l < length; ++ l )
		++ count [ word [ l ] - 'A' ];
	
	for ( int c = 0; c < 26; ++ c )
	{
		maxLetter = max > count [ c ] ? maxLetter : c;
		max = max > count [ c ] ? max : count [ c ];
	}

	for ( int l = 0; l < length; ++ l )
		printf ( "%c", 'A' + ( 26 + word [ l ] - 'A' + letter [ 0 ] - 'A' - maxLetter ) % 26 );
	
	puts ( "\n" );

	return 0;
}
