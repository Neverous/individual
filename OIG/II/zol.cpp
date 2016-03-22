/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdlib>
#include <cstdio>
#include <algorithm>

using namespace std;

int soldier [ 200001 ],
	soldiers,
 	last,
  	result = 1,
   	value = 1;

bool big,
	 same = true;

int main ( void )
{
	scanf ( "%d", & soldiers );
	for ( int s = 0; s < soldiers; ++ s )
	{
		scanf ( "%d", & soldier [ s ] );
		if ( s &&
		     same &&
		     soldier [ s ] != soldier [ s - 1 ] )
			same = false;
	}

	if ( soldiers == 1 )
	{
		printf ( "1" );
		return 0;
	}

	sort ( soldier, soldier + soldiers );

	for ( int s = 0; s < soldiers; ++ s )
	{
		if ( last != soldier [ s ] )
		{
			value = 1;
			last = soldier [ s ];
		}
		else
			value ++;

		result *= value;

		if ( result > 1000 )
			big = true;

		result %= 10000;

		if ( ! result )
			break;
	}

	if ( ! same )
		result = ( result * 2 ) % 10000;
	else
		result %= 10000;

	if ( big )
	{
		if ( result < 1000 )
			printf ( "0" );

		if ( result < 100 )
			printf ( "0" );

		if ( result < 10 )
			printf ( "0" );
	}

	printf ( "%d\n", result );

	return 0;
}

