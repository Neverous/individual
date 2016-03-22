#include <cstdio>

int solve ( int number )
{
	int result = number;
	for ( int n = 1; n <= number; ++ n )
		for ( int d = 2; d * d <= n; ++ d )
			if ( n % d == 0 )
				++ result;

	return result;
}

int number;

int main ( void )
{
	scanf ( "%d", & number );
	printf ( "%d\n", solve ( number ) );
	return 0;
}

