/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>

long long unsigned int result = 1,
					   number;

long long unsigned int gcd ( long long unsigned int a, long long unsigned int b )
{
	long long unsigned int c;
	if ( a < b )
	{
		c = a;
		a = b;
		b = c;
	}

	while ( b )
	{
		c = b;
		b = a % b;
		a = c;
	}
	return a;
}

int main ( void )
{
	for ( int q = 0; q < 8; ++ q )
	{
		scanf ( "%llu", & number );
		result = ( result * number ) / ( gcd ( result, number ) );
	}
	printf ( "%llu", result );
	return 0;
}

