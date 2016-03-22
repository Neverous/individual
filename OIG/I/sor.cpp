/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int words;

char tmpWord [ 202 ];

vector < string > word;

bool stringSort ( const string & A, const string & B );

int main ( void )
{
	scanf ( "%d", & words );
	for ( int w = 0; w < words; ++ w )
	{
		scanf ( "%s", tmpWord );
		word . push_back ( string ( tmpWord ) );
	}

	sort ( word . begin ( ), word . end ( ), stringSort );

	for ( int w = 0; w < words; ++ w )
		printf ( "%s\n", word [ w ] . c_str ( ) );

	return 0;
}

bool stringSort ( const string & A, const string & B )
{
	if ( A . length ( ) > B . length ( ) )
		return false;

	else if ( A . length ( ) < B . length ( ) )
		return true;

	else
		return A < B;

}

