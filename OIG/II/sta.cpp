/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>
#include <algorithm>

using namespace std;

int bajteksFuel,
	bajteksModules,
	kajteksFuel,
	kajteksModules,
	zajteksFuel,
	zajteksModules,
	result;

long long int bajteksModule [ 1001 ],
			  kajteksModule [ 1001 ],
			  zajteksModule [ 1001 ],
			  maxEfficiency;

int main ( void )
{
	scanf ( "%d %d %d", & bajteksFuel, & kajteksFuel, & zajteksFuel );

	scanf ( "%d", & bajteksModules );
	for ( int m = 0; m < bajteksModules; ++ m )
	{
		scanf ( "%lld", & bajteksModule [ m ] );
		bajteksModule [ m ] *= bajteksFuel;
	}

	sort ( bajteksModule, bajteksModule + bajteksModules );

	scanf ( "%d", & kajteksModules );
	for ( int m = 0; m < kajteksModules; ++ m )
	{
		scanf ( "%lld", & kajteksModule [ m ] );
		kajteksModule [ m ] *= kajteksFuel;
	}

	sort ( kajteksModule, kajteksModule + kajteksModules );

	scanf ( "%d", & zajteksModules );
	for ( int m = 0; m < zajteksModules; ++ m )
	{
		scanf ( "%lld", & zajteksModule [ m ] );
		zajteksModule [ m ] *= zajteksFuel;
	}

	sort ( zajteksModule, zajteksModule + zajteksModules );

	maxEfficiency = bajteksModule [ bajteksModules - 1 ] + kajteksModule [ kajteksModules - 1 ] + zajteksModule [ zajteksModules - 1 ];
	maxEfficiency /= 2;

	for ( int b = bajteksModules - 1; b >= 0; -- b )
	{
		for ( int k = kajteksModules - 1; k >= 0; -- k )
			result += zajteksModule + zajteksModules - upper_bound ( zajteksModule, zajteksModule + zajteksModules, maxEfficiency - bajteksModule [ b ] - kajteksModule [ k ] );
	}

	printf ( "%d", result );
	return 0;
}

