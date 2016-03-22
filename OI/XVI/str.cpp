/*		2008
Maciej Szeptuch
XIV LO WROCŁAW
Zadanie: STRAŻ POŻARNA
*/
/*
!!! BBBBB   RRRRRR  UU   UU TTTTTTT EEEEEEE  FFFFFFF  OOOOO  RRRRRR   CCCCC  EEEEEEE !!!
!!! BB   B  RR   RR UU   UU   TTT   EE       FF      OO   OO RR   RR CC    C EE      !!!
!!! BBBBBB  RRRRRR  UU   UU   TTT   EEEEE    FFFF    OO   OO RRRRRR  CC      EEEEE   !!!
    BB   BB RR  RR  UU   UU   TTT   EE       FF      OO   OO RR  RR  CC    C EE
!!! BBBBBB  RR   RR  UUUUU    TTT   EEEEEEE  FF       OOOO0  RR   RR  CCCCC  EEEEEEE !!!
Aż nie chce mi się go komentować ^^
*/
#include <cstdio>
#include <vector>

using namespace std;

int buildings,
	plans,
	w,
	x,
	y,
	z,
	tmpA,
	tmpB;

pair < int, int > building [ 100010 ];
pair < pair < int, int >, pair < int, int > > plan [ 100010 ];

int abs ( int a )
{
	return ( a > 0 ) ? a : 0 - a;
}

void solve ( void )
{
	int A = 0,
		B = 0;
	for ( int p = 0; p < plans; ++ p )
	{
		A = B = 0;
		for ( int b = 0; b < buildings; ++ b )
		{
			tmpA = abs ( building [ b ] . first - plan [ p ] . first . first ) + abs ( building [ b ] . second - plan [ p ] . first . second );
			tmpB = abs ( building [ b ] . first - plan [ p ] . second . first ) + abs ( building [ b ] . second - plan [ p ] . second . second );
			if ( tmpA < tmpB )
				A++;
			else if ( tmpA > tmpB )
				B++;
		}
		printf ( "%d %d %d\n", A, B, buildings - A - B );
	}
}

int main ( void )
{
	scanf ( "%*d %*d %d %d", & buildings, & plans );
	for ( int b = 0; b < buildings; ++ b )
	{
		scanf ( "%d %d", & x, & y );
		building [ b ] = pair < int, int > ( x, y );
	}
	for ( int p = 0; p < plans; ++ p )
	{
		scanf ( "%d %d %d %d", & w, & x, & y, & z );
		plan [ p ] = pair < pair < int, int >, pair < int, int > > ( pair < int, int > ( w, x ), pair < int, int > ( y, z ) );
	}
	solve ( );
	return 0;
}

