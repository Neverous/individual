/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector < pair < int, pair <int, int > > > tab;
int many,
	requests,
	product,
	quant;

int compressAndRebuild ( void );

int main ( void )
{
	scanf ( "%d", & requests );

	for ( int r = 0; r < requests; ++ r )
	{
		scanf ( "%d %d", & product, & quant );

		tab . push_back ( make_pair ( product, make_pair ( quant, r ) ) );
	}

	sort ( tab . begin ( ), tab . end ( ) );

	many = compressAndRebuild ( );

	printf ( "%d\n", many );

	sort ( tab . begin ( ), tab . end ( ) );

	for ( int i = 0; tab [ i ] . first != 2000000; ++ i )
		printf ( "%d %d\n", tab [ i ] . second . second, tab [ i ] . second . first );

	return 0;
}

int compressAndRebuild ( void )
{
	int result = 1,
		tmp;

	unsigned int i = 1;

	for ( ; i < tab . size ( ); ++ i )
	{
		if ( tab [ i - 1 ] . first != tab [ i ] . first )
		{
			tmp = tab [ i - 1 ] . first;
			tab [ i - 1 ] . first = tab [ i - 1 ] . second . second;
			tab [ i - 1 ] . second . second = tmp;
			++ result;
			continue;
		}

		tab [ i ] . second . first += tab [ i - 1 ] . second . first;
		tab [ i ] . second . second = ( tab [ i - 1 ] . second . second < tab [ i ] . second . second ) ? tab [ i - 1 ] . second . second : tab [ i ] . second . second;
		tab [ i - 1 ] . first = 2000000;

	}
	tmp = tab [ i - 1 ] . first;
	tab [ i - 1 ] . first = tab [ i - 1 ] . second . second;
	tab [ i - 1 ] . second . second = tmp;

	return result;
}

