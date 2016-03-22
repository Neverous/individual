/* Maciej Szeptuch
 * XIV LO Wrocław
 * 2009
 */
#include <cstdio>
#define abs( a ) ( ( a ) > 0 ? ( a ) : - ( a ) )

int size,
	guards,
	x,
	y,
	range;

long long unsigned int pool [ 1002 ] [ 1002 ];

long long unsigned int solve ( int & x, int & y, int & range );

int main ( void )
{
	scanf ( "%d %d", & size, & guards );
	for ( int h = 1; h <= size; ++ h )
		for ( int w = 1; w <= size; ++ w )
		{
			scanf ( "%llu", & pool [ h ] [ w ] );
			pool [ h ] [ w ] += pool [ h ] [ w - 1 ];
		}

	for ( int g = 0; g < guards; ++ g )
	{
		scanf ( "%d %d %d", & y, & x, & range );
		printf ( "%llu\n", solve ( x, y, range ) );
	}
	return 0;
}

long long unsigned int solve ( int & x, int & y, int & range )
{
	long long unsigned int result = 0;
	for ( int h = y - range > 1 ? - range : 1 - y, H = y + range <= size ? range : size - y; h <= H; ++ h )
		result += pool [ y + h ] [ x + ( x + range - abs ( h ) <= size ? range - abs ( h ) : size - x ) ] - pool [ y + h ] [ x + ( x - range + abs ( h ) > 1 ? abs ( h ) - range : 1 - x ) - 1 ];

	return result;
}
