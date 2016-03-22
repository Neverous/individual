/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>

int computers,
	pendrives,
	tests,
	result;

int solve ( int c, int p )
{
	int result = 0,
		sum = 1,
		power = 1;

	while ( power < p && sum < c )
	{
		sum += power;
		power *= 2;
		++ result;
	}

	if ( sum < c )
		result += ( c - sum + pendrives - 1 ) / pendrives;

	return result;
}

int main ( void )
{
	scanf ( "%d", & tests );
	for ( int t = 0; t < tests; ++ t )
	{
		scanf ( "%d %d", & computers, & pendrives );
		printf ( "%d\n", solve ( computers, pendrives ) );
	}
	return 0;
}

