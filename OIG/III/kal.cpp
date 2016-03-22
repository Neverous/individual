/* Maciej Szeptuch
 * XIV LO Wrocław
 * 2009
 */
#include <cstdio>
#include <algorithm>

using namespace std;

int arbuzMonths,
	arbuzMonth [ 1000001 ],
	bananMonths,
	bananMonth [ 1000001 ],
	month,
	day,
	questions;

char convert [ 2 ];

void arbuzToBanan ( int & month, int & day );
void bananToArbuz ( int & month, int & day );

int main ( void )
{
	scanf ( "%d %d", & arbuzMonths, & bananMonths );
	for ( int a = 1; a <= arbuzMonths; ++ a )
	{
		scanf ( "%d", & arbuzMonth [ a ] );
		arbuzMonth [ a ] += arbuzMonth [ a - 1 ];
	}

	for ( int b = 1; b <= bananMonths; ++ b )
	{
		scanf ( "%d", & bananMonth [ b ] );
		bananMonth [ b ] += bananMonth [ b - 1 ];
	}

	scanf ( "%d", & questions );

	for ( int q = 0; q < questions; ++ q )
	{
		scanf ( "%d %d %s", & day, & month, convert );
		if ( convert [ 0 ] == 'A' )
			arbuzToBanan ( month, day );
		
		else
			bananToArbuz ( month, day );

		printf ( "%d %d\n", day, month );
	}

	return 0;
}

void arbuzToBanan ( int & month, int & day )
{
	day = arbuzMonth [ month - 1 ] + day;
	month = lower_bound ( bananMonth, bananMonth + bananMonths, day ) - bananMonth;
	day -= bananMonth [ month - 1 ]; 
	return;
}

void bananToArbuz ( int & month, int & day )
{
	day = bananMonth [ month - 1 ] + day;
	month = lower_bound ( arbuzMonth, arbuzMonth + arbuzMonths, day ) - arbuzMonth;
	day -= arbuzMonth [ month - 1 ]; 
	return;
}
