/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

long long int rocks,
	maxJump,
	x,
	y,
	unionTab [ 1001 ],
	frogRock;

double result;

pair < long long int, long long int > rock [ 1001 ];

inline double length ( long long int a, long long int b )
{
	return (double) sqrt ( ( rock [ a ] . first - rock [ b ] . first ) * ( rock [ a ] . first - rock [ b ] . first ) + ( rock [ a ] . second - rock [ b ] . second ) * ( rock [ a ] . second - rock [ b ] . second ) );
}

long long int unionFind ( long long int a )
{
	if ( unionTab [ a ] != a )
		unionTab [ a ] = unionFind ( unionTab [ a ] );

	return unionTab [ a ];
}

bool unionUnion ( long long int a, long long int b )
{
	int sA = unionFind ( a ),
		sB = unionFind ( b );

	if ( sA == sB )
		return false;

	if ( a < b )
		unionTab [ sB ] = sA;

	else
		unionTab [ sA ] = sB;

	return true;
}

int main ( void )
{
	scanf ( "%lld %lld %lld", & rocks, & frogRock, & maxJump );
	-- frogRock;

	for ( long long int r = 0; r < rocks; ++ r )
	{
		scanf ( "%lld %lld", & x, & y );
		rock [ r ] = make_pair ( x, y );
		unionTab [ r ] = r;
	}

	for ( long long int r = 0; r < rocks; ++ r )
		for ( long long int r2 = r + 1; r2 < rocks; ++ r2 )
			if ( length ( r, r2 ) <= maxJump )
				unionUnion ( r, r2 );

	for ( long long int r = 0; r < rocks; ++ r )
		if ( unionFind ( r ) == unionFind ( frogRock ) &&
			 length ( r, frogRock ) > result )
			result = length ( r, frogRock );

	printf ( "%0.3f\n", result + maxJump );
	return 0;
}

