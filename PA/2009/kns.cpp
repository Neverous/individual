/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>
#define abs(x) ((x)<0?(-(x)):(x))
int tests,
	k,
	n,
	x1,
	x2,
	y1,
	y2;

inline bool check ( void )
{

	return ( abs ( x1 - x2 ) == 0 && abs ( y1 - y2 ) == 0 ) ||
		   ( abs ( k - n ) && abs ( x1 - x2 ) % abs ( k - n ) == 0 && abs ( y1 - y2 ) % abs ( k - n ) == 0 ) ||
		   ( n > 1 && k > 1 && abs ( x1 - x2 ) % n == 0 && abs ( y1 - y2 ) % k == 0 ) ||
		   ( n > 1 && k > 1 && abs ( x1 - x2 ) % k == 0 && abs ( y1 - y2 ) % n == 0 ) ||
		   ( n + k && abs ( x1 - x2 ) % ( n + k ) == 0 && abs ( y1 - y2 ) % ( n + k ) == 0 ) ||
		   ( n && abs ( x1 - x2 ) % ( 2 * n ) == 0 && abs ( y1 - y2 ) == 0 ) ||
		   ( k && abs ( x1 - x2 ) % ( 2 * k ) == 0 && abs ( y1 - y2 ) == 0 ) ||
		   ( n && abs ( x1 - x2 ) == 0 && abs ( y1 - y2 ) % ( 2 * n ) == 0 ) ||
		   ( k && abs ( x1 - x2 ) == 0 && abs ( y1 - y2 ) % ( 2 * k ) == 0 );
}

int main ( void )
{
	scanf ( "%d", & tests );
	for ( int t = 0; t < tests; ++ t )
	{
		scanf ( "%d %d %d %d %d %d", & k, & n, & x1, & y1, & x2, & y2 );
		printf ( "%s\n", ( check ( ) ) ? "TAK" : "NIE" );
	}

	return 0;
}

