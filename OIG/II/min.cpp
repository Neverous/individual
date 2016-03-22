/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>
#include <algorithm>

int size;

long long unsigned int divider,
					   divi,
					   tab [ 1000001 ],
					   * pos;

int main ( void )
{
	scanf ( "%d %lld", & size, & divi );

	for ( int s = 0; s < size; ++ s )
		scanf ( "%lld", & tab [ s ] );

	std :: sort ( tab, tab + size );
	pos = tab;

	do
	{
		divider += divi;
		pos = std :: lower_bound ( pos, tab + size, divider );
	}
	while ( *pos == divider );

	printf ( "%lld\n", divider );
	return 0;
}

