/*
Maciej Szeptuch
XIV LO Wroclaw
*/
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

pair < int, int > point [ 2002 ];

int edges [ 2002 ];

int points,
	result,
	edgesSize;

static inline int getAngle ( int A, int B )
{
	int C;
	if ( point [ A ] . second > point [ B ] . second )
	{
		C = A;
		A = B;
		B = C;
	}

	int Bx = point [ B ] . first - point [ A ] . first,
	    By = point [ B ] . second - point [ A ] . second,
	    Ax = 1,
	    Ay = 0;

	double angle = acos((Ax*Bx + Ay*By)/(sqrt(Ax*Ax+Ay*Ay)*sqrt(Bx*Bx+By*By)))/acos(-1)*180; // Iloczyn skalarny ^^

	if ( angle >= 180 )
		angle -= 180;

	return ( int ) angle;
}

static inline int findTriangles ( int angle )
{
	while ( angle >= 180 )
		angle -= 180;

	return lower_bound ( edges, edges + edgesSize, angle ) - lower_bound ( edges, edges + edgesSize, angle );
}

int main ( void )
{
	scanf ( "%d", & points );
	for ( int p = 0; p < points; ++ p )
		scanf ( "%d %d", & point [ p ] . first, & point [ p ] . second );

	for ( int i = 0; i < points; ++ i )
	{
		edgesSize = 0;
		for ( int j = 0; j < points; ++ j )
		{
			if ( i == j )
				continue;

			edges [ edgesSize ++ ] = getAngle ( i, j );
		}

		sort ( edges, edges + edgesSize );

		for ( int e = 0; e < edgesSize; ++ e )
			result += findTriangles ( edges [ e ] );
	}
	printf ( "%d\n", result / 2 );

}

