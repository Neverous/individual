/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>

int length,
	move,
	start,
	end;

inline long long unsigned int sum ( int start, int end )
{
	return ( long long unsigned int ) ( start + end ) * ( end - start + 1 ) / 2;
}

inline long long unsigned int solve ( void )
{
	if ( start <= move && end <= move )
		return sum ( length - move + start, length - move + end );

	if ( start > move && end > move )
		return sum ( start - move, end - move );

	return sum ( length - move + start, length ) + sum ( 1, end - move );
}

int main ( void )
{
	scanf ( "%d %d %d %d", & length, & move, & start, & end );
	printf ( "%llu\n", solve ( ) );
	return 0;
}

