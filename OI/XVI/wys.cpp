/*		2009
Maciej Szeptuch
XIV LO WROCŁAW
*/
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

int tests,
	num;

unsigned int globalLen;

char action;

string globalCheck;

bool myCmp ( const int & posA, const int & posB )
{
	for ( unsigned int i = posA, j = posB; i < globalLen + posA && j < globalLen + posB; ++ i, ++ j )
	{
		if ( globalCheck [ i ] > globalCheck [ j ] )
			return false;
		else if ( globalCheck [ i ] < globalCheck [ j ] )
			return true;
	}
	return false;
}

string makeTwiceGood ( string checkMe )
{
	unsigned int len = checkMe . size ( );
	vector < int > tab;
	string _result;
	checkMe += checkMe;
	globalCheck = checkMe;
	globalLen = len;

	for ( unsigned int i = 0; i < len; ++ i )
		tab . push_back ( i );

	sort ( tab . begin ( ), tab . end ( ), myCmp );
	for ( unsigned int i = tab [ 0 ]; i < len + tab [ 0 ]; ++ i )
		_result . push_back ( checkMe [ i ] );

	return _result;
}

string makeGood ( string checkMe )
{
	string _result,
		   _result2;

	_result = makeTwiceGood ( checkMe );
	reverse ( checkMe . begin ( ), checkMe . end ( ) );
	_result2 = makeTwiceGood ( checkMe );

	if ( strcmp ( _result . c_str ( ), _result2 . c_str ( ) ) < 0 )
		return _result;

	return _result2;
}

void addTriangle ( string figure, set < string > & where )
{
	unsigned int len = figure . size ( );
	unsigned int nF = 0;;
	figure += figure;
	string _result;

	for ( unsigned int f = 1; f < len; ++ f )
	{
		if ( figure [ f ] == 'a' )
			continue;

		_result . clear ( );

		for ( unsigned int i = 1; i < f; ++ i )
			_result . push_back ( figure [ i ] );

		_result . push_back ( figure [ f ] - 1 );

		if ( figure [ f + 1 ] != 'a' )
		{
			_result . push_back ( 'e' );
			_result . push_back ( figure [ f + 1 ] - 1 );
			nF = f + 2;
		}
		else if ( figure [ f + 2 ] != 'a' )
		{
			_result . push_back ( figure [ f + 2 ] - 1 );
			nF = f + 3;
			if ( nF > len + 1 )
				_result . erase( _result . begin ( ) );
		}
		else
			continue;

		for ( unsigned int i = nF; i < len + 1; ++ i )
			_result . push_back ( figure [ i ] );

		_result = makeGood ( _result );
		where . insert ( _result );
	}
}

void actionK ( void )
{
	char text [ 20 ];
	string stringText;
	scanf ( "%s", text );
	stringText . assign ( text );
	set < string > result;

	addTriangle ( stringText, result );

	printf ( "%d\n", ( int ) result . size ( ) );

	for ( set < string > :: iterator i = result . begin ( ); i != result . end ( ); ++ i )
		printf ( "%s ", i -> c_str ( ) );
	printf ( "\n" );
}

void actionN ( void )
{
	scanf ( "%d", & num );

	set < string > result;
	set < string > result2;
	result2 . insert ( "eee" );

	for ( int i = 1; i < num; ++ i )
	{
		result = result2;
		result2 . clear ( );
		for ( set < string > :: iterator i = result . begin ( ); i != result . end ( ); ++ i )
			addTriangle ( *i, result2 );
	}
	result = result2;
	result2 . clear ( );

	printf ( "%d\n", ( int ) result . size ( ) );

	for ( set < string > :: iterator i = result . begin ( ); i != result . end ( ); ++ i )
		printf ( "%s ", i -> c_str ( ) );
	printf ( "\n" );

}

int main ( void )
{
	scanf ( "%d", & tests );
	for ( int t = 0; t < tests; ++ t )
	{
		scanf ( " %c", & action );

		if ( action == 'K' )
			actionK ( );
		else if ( action == 'N' )
			actionN ( );
		else
		{
			printf ( "WTF? O.o" );
			exit ( 254 );
		}
	}

	return 0;
}

