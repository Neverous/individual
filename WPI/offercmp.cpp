/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector < int > A,
			B,
			C;

int size,
	element;

int main ( void )
{
	scanf ( "%d", & size );
	for ( int s = 0; s < size; ++ s )
	{
		scanf ( "%d", & element );
		A . push_back ( element );
	}

	scanf ( "%d", & size );
	for ( int s = 0; s < size; ++ s )
	{
		scanf ( "%d", & element );
		B . push_back ( element );
	}

	set_union ( A . begin ( ),
				A . end ( ),
				B . begin ( ),
				B . end ( ),
				inserter ( C, C . begin ( ) ) );

	for ( vector < int > :: iterator i = C . begin ( ); i != C . end ( ); ++ i )
		printf ( "%d ", *i );

	C . clear ( );
	printf ( "\n" );

	set_intersection ( A . begin ( ),
				A . end ( ),
				B . begin ( ),
				B . end ( ),
				inserter ( C, C . begin ( ) ) );

	for ( vector < int > :: iterator i = C . begin ( ); i != C . end ( ); ++ i )
		printf ( "%d ", *i );

	C . clear ( );
	printf ( "\n" );

	set_symmetric_difference ( A . begin ( ),
				A . end ( ),
				B . begin ( ),
				B . end ( ),
				inserter ( C, C . begin ( ) ) );

	for ( vector < int > :: iterator i = C . begin ( ); i != C . end ( ); ++ i )
		printf ( "%d ", *i );

	C . clear ( );
	printf ( "\n" );

	return 0;
}

