/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

int houses,
	points;

long long int result,
			  act,
			  range,
			  x,
			  y;

pair < long long int, long long int > house [ 100001 ];

inline long long int length ( long long int x, long long int y )
{
	double tmp = sqrt ( x*x + y*y );
	long long int result = (long long int) tmp;
	if ( result < tmp )
		++ result;

	return result;
}

inline long long int calc ( long long int num )
{
	return ( ( num - 1 ) * num ) / 2;
}

int main ( void )
{
	scanf ( "%d %lld", & houses, & range );
	for ( int h = 0; h < houses; ++ h )
	{
		scanf ( "%d %lld", & points, & house [ h ] . second );

		for ( int p = 0; p < points; ++ p )
		{
			scanf ( "%lld %lld", & x, & y );
			if ( length ( x, y ) > house [ h ] . first )
				house [ h ] . first = length ( x, y );
		}
	}

	sort ( house, house + houses );

	for ( int h = 1; h < houses; ++ h )
		house [ h ] . second += house [ h - 1 ] . second;

	for ( int h = houses - 1; h >= 0; -- h )
	{
		act = house [ h ] . second - calc ( ( house [ h ] . first + range - 1 ) / range );

		if ( act > result )
			result = act;
	}

	printf ( "%lld\n", result );
	return 0;
}

