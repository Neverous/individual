/*		2008
Maciej Szeptuch
XIV LO WROCŁAW
Zadanie: PRZYSPIESZENIE ALGORYTMU
*//*
GORSZE NIŻ
!!! BBBBB   RRRRRR  UU   UU TTTTTTT EEEEEEE  FFFFFFF  OOOOO  RRRRRR   CCCCC  EEEEEEE !!!
!!! BB   B  RR   RR UU   UU   TTT   EE       FF      OO   OO RR   RR CC    C EE      !!!
!!! BBBBBB  RRRRRR  UU   UU   TTT   EEEEE    FFFF    OO   OO RRRRRR  CC      EEEEE   !!!
    BB   BB RR  RR  UU   UU   TTT   EE       FF      OO   OO RR  RR  CC    C EE
!!! BBBBBB  RR   RR  UUUUU    TTT   EEEEEEE  FF       OOOO0  RR   RR  CCCCC  EEEEEEE !!!
Aż nie chce mi się go komentować ^^
Ciekawe ile pkt dostanie ?
*/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

int tests,
	lenA,
	lenB,
	tmp;

vector < bool > was ( 110, 0 ),
				wasB ( 110, 0 );

vector < int > strA,
			   strB;

vector < pair < int, pair < bool, int > > > checkA,
							  				checkB;

bool solve ( int sA, int eA, int sB, int eB )
{
	if ( sA > eA || sB > eB )
		return 1;
	if ( sA == eA && sB == eB )
		return 1;
	checkA . clear ( );
	checkB . clear ( );
	was . clear ( );
	was . resize ( 110, 0 );
	for ( int a = sA; a <= eA; ++ a )
	{
		if ( ! was [ strA [ a ] ] )
			checkA . push_back ( pair < int, pair < bool, int > > ( a, pair < bool, int > ( false, strA [ a ] ) ) );
		was [ strA [ a ] ] = true;
	}
	wasB . clear ( );
	wasB . resize ( 110, 0 );

	for ( int b = sB; b <= eB; ++ b )
	{
		if ( ! wasB [ strB [ b ] ] )
			checkB . push_back ( pair < int, pair < bool, int > > ( b, pair < bool, int > ( false, strB [ b ] ) ) );
		wasB [ strB [ b ] ] = true;
	}

	for ( int i = 0; i < 110; ++ i )
		if ( was [ i ] != wasB [ i ] )
			return 0;

	if ( checkA . size ( ) == checkB . size ( ) && checkA . size ( ) == 1 )
		return 1;

	was . clear ( );
	was . resize ( 110, 0 );

	for ( int a = eA; a >= sA; -- a )
	{
		if ( ! was [ strA [ a ] ] )
			checkA . push_back ( pair < int, pair < bool, int > > ( a+1, pair < bool, int > ( true, strA [ a ] ) ) );
		was [ strA [ a ] ] = true;
	}
	wasB . clear ( );
	wasB . resize ( 110, 0 );

	for ( int b = eB; b >= sB; -- b )
	{
		if ( ! wasB [ strB [ b ] ] )
			checkB . push_back ( pair < int, pair < bool, int > > ( b+1, pair < bool, int > ( true, strB [ b ] ) ) );
		wasB [ strB [ b ] ] = true;
	}

	if ( checkA . size ( ) != checkB . size ( ) )
		return 0;

	sort ( checkA . begin ( ), checkA . end ( ) );
	sort ( checkB . begin ( ), checkB . end ( ) );

	for ( int i = 0; i < checkA . size ( ); ++ i )
	{
		if ( checkA [ i ] . second . second  != checkB [ i ] . second . second || checkA [ i ] . second . first  != checkB [ i ] . second . first  )
		{
			return 0;
		}
	}
	int prefA = -1, prefB = -1,
		sufA = -1, sufB = -1;

	for ( int i = 0; i < checkA . size ( ); ++ i )
	{
		if ( sufA == -1 && checkA [ i ] . second . first == true && checkA [ i ] . first >= sA && checkA [ i ] . first <= eA )
			sufA = checkA [ i ] . first;

		if ( sufB == -1 && checkB [ i ] . second . first == true && checkB [ i ] . first >= sB && checkB [ i ] . first <= eB )
			sufB = checkB [ i ] . first;
	}
	for ( int i = checkA . size ( ) - 1; i >= 0; -- i )
	{
		if ( prefA == -1 && checkA [ i ] . second . first == false && checkA [ i ] . first > sA && checkA [ i ] . first <= eA )
			prefA = checkA [ i ] . first - 1;

		if ( prefB == -1 && checkB [ i ] . second . first == false && checkB [ i ] . first > sB && checkB [ i ] . first <= eB )
			prefB = checkB [ i ] . first - 1;
	}
	prefA = prefA > 0 ? prefA : 0;
	prefB = prefB > 0 ? prefB : 0;
	sufA = sufA > 0 ? sufA : 0;
	sufB = sufB > 0 ? sufB : 0;
	return solve ( sA, prefA, sB, prefB ) && solve ( sufA, eA, sufB, eB );
}

int main ( void )
{
	scanf ( "%d",  & tests );
	for ( int t = 0; t < tests; ++ t )
	{
		strA . clear ( );
		strB . clear ( );
		checkA . clear ( );
		checkB . clear ( );
		wasB . clear ( );
		wasB . resize ( 110, 0 );
		was . clear ( );
		was . resize ( 110, 0 );

		scanf ( "%d %d", & lenA, & lenB );
		/*------------------------------------A-----------------------------------*/
		for ( int a = 0; a < lenA; ++ a )
		{
			scanf ( "%d", & tmp );
			strA . push_back ( tmp );
		}
		/*------------------------------------B-----------------------------------*/

		for ( int b = 0; b < lenB; ++ b )
		{
			scanf ( "%d", & tmp );
			strB . push_back ( tmp );
		}
		printf ( "%d\n", solve ( 0, lenA - 1, 0, lenB - 1 ) );
	}
	return 0;
}

