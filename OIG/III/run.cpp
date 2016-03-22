/* Maciej Szeptuch
 * XIV LO Wrocław
 * 2009
 */
#include <cstdio>

long long unsigned int competitors,
	 				   competitor [ 100001 ],
					   minTime = 1;

long long unsigned int nwd ( long long unsigned int a, long long unsigned int b );

int main ( void )
{
	scanf ( "%llu", & competitors );
	for ( long long unsigned int c = 0; c < competitors; ++ c )
	{
		scanf ( "%llu", & competitor [ c ] );
		minTime = ( minTime * competitor [ c ] ) / nwd ( minTime, competitor [ c ] );
	}

	for ( long long unsigned int c = 0; c < competitors; ++ c )
		printf ( "%llu\n", minTime / competitor [ c ] );

	return 0;
}

long long unsigned int nwd ( long long unsigned int a, long long unsigned b )
{
	long long unsigned int c;
	if ( a < b )
	{
		c = b;
		b = a;
		a = c;
	}

	while ( b )
	{
		c = b;
		b = a % b;
		a = c;
	}

	return a;
}
