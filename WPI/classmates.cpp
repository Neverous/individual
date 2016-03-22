/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int firstLength,
	secondLength,
	first,
	second,
	length;

vector < int > hash [ 19 ];

char ord [ 256 ] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,0,0,0,0,0,0,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

char word [ 400004 ];

vector < pair < pair < int, int >, int > > hashing;

static inline void preprocess ( void );
static inline bool checkHash ( int first, int second, int length );
static inline pair < int, int > getHash ( int start, int level );

int main ( void )
{
	scanf ( " " );
	scanf ( "%s%n", word, & firstLength );
	scanf ( " " );
	scanf ( "%s%n", word + firstLength, & secondLength );
	preprocess ( );

	while ( scanf ( "%d %d %d", & first, & second, & length ) != -1 && length )
		printf ( "%s\n", checkHash ( first - 1, second + firstLength - 1, length ) ? "TAK" : "NIE" );
}

static inline void preprocess ( void )
{
	hash [ 0 ] . resize ( firstLength + secondLength );
	for ( int p = 0; p < firstLength + secondLength; ++ p )
		hash [ 0 ] [ p ] = ord [ ( int ) word [ p ] ];

	for ( int p = 1; ( 1 << p ) < firstLength + secondLength; ++ p )
	{
		hashing . resize ( firstLength + secondLength - ( 1 << ( p - 1 ) ) );
		hash [ p ] . resize ( firstLength + secondLength - ( 1 << ( p - 1 ) ) );
		for ( int w = 0; w < firstLength + secondLength - ( 1 << ( p - 1 ) ); ++ w )
			hashing [ w ] = make_pair ( make_pair ( hash [ p - 1 ] [ w ], hash [ p - 1 ] [ w + ( 1 << ( p - 1 ) ) ] ), w );

		sort ( hashing . begin ( ), hashing . end ( ) );
		for ( int w = 0, k = 0; w < firstLength + secondLength - ( 1 << ( p - 1 ) ); ++ w )
		{
			if ( w && hashing [ w ] . first != hashing [ w - 1 ] . first )
				++ k;

			hash [ p ] [ hashing [ w ] . second ] = k;
		}
	}
}

static inline bool checkHash ( int first, int second, int length )
{
	if ( first + length > firstLength ||
		 second + length > firstLength + secondLength )
		return false;

	int level = 0;

	while ( 1 << level <= length / 2 )
		++ level;

	return getHash ( first, level ) == getHash ( second, level );
}

static inline pair < int, int > getHash ( int start, int level )
{
	return make_pair ( hash [ level ] [ start ], hash [ level ] [ start + length - ( 1 << level ) ] );
}

