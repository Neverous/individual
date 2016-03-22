/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>

int screws [ 1010 ],
	boxesOfScrews,
	tables,
	screwsForTables,
	box,
	result;

int main ( void )
{
	scanf ( "%d %d %d", & boxesOfScrews, & screwsForTables, & tables );
	for ( int b = 0; b < boxesOfScrews; ++ b )
	{
		scanf ( "%d", & box );
		++ screws [ box ];
	}

	screwsForTables *= tables;
	for ( int b = 1000; b && screwsForTables; -- b )
	{
		if ( ( screwsForTables + b - 1 ) / b <= screws [ b ] )
		{
			result += ( screwsForTables + b - 1 ) / b;
			break;
		}
		result += screws [ b ];
		screwsForTables -= screws [ b ] * b;
	}
	printf ( "%d\n", result );
	return 0;
}

