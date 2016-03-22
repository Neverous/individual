/*
Maciej Szeptuch
XIV LO Wroclaw
*/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string.h>

using namespace std;

struct Tree
{
	static const int SIZE = 16777216;
	int data [ SIZE ];

	Tree ( void )
	{
		bzero ( data, SIZE * sizeof ( int ) );
	}

	inline void insert ( int position )
	{
		position += SIZE / 2 - 1;

		while ( position > 0 )
		{
			data [ position ] ++;
			position /= 2;
		}
	}

	int sum ( int start, int end, int rootStart = 1, int rootEnd = SIZE / 2, int index = 1 )
	{
		if ( start == rootStart && end == rootEnd )
			return data [ index ];

		int half = ( rootStart + rootEnd ) / 2;
		int res = 0;

		if ( end <= half )
			res += sum ( start, end, rootStart, half, index * 2 );
		else if ( start > half )
			res += sum ( start, end, half + 1, rootEnd, index * 2 + 1 );
		else if ( start <= half && end > half )
		{
			res += sum ( start, half, rootStart, half, index * 2 );
			res += sum ( half + 1, end, half + 1, rootEnd, index * 2 + 1 );
		}

		return res;
	}
};

int luggage,
    concerns,
    a,
    b,
    result [ 1000001 ];

Tree tree;

pair < pair < int, int >, pair < int, int > > points [ 2000002 ];

bool compare ( const pair < pair < int, int >, pair < int, int > > & A, const pair < pair < int, int >, pair < int, int > > & B )
{
	return A > B;
}

int main ( void )
{
	scanf ( "%d %d", & luggage, & concerns );
	for ( int l = 0; l < luggage; ++ l )
	{
		scanf ( "%d %d", & a, & b );
		++ a;
		++ b;
		points [ l ] = pair < pair < int, int >, pair < int, int > > ( pair < int, int > ( a, b ), pair < int, int > ( 1, -1 ) );
	}

	for ( int c = 0; c < concerns; ++ c )
	{
		scanf ( "%d %d", & a, & b );
		++ a;
		++ b;
		points [ c + luggage ] =  pair < pair < int, int >, pair < int, int > > ( pair < int, int > ( a, b ), pair < int, int > ( 0, c ) );
	}

	std :: sort ( points, points + luggage + concerns, compare );

	for ( int p = 0; p < luggage + concerns; ++ p )
	{
		if ( points [ p ] . second . first )
			tree . insert ( points [ p ] . first . second );

		else
			result [ points [ p ] . second . second ] = tree . sum ( points [ p ] . first . second, 5000005 );
	}

	for ( int c = 0; c < concerns; ++ c )
		printf ( "%d\n", result [ c ] );
	return 0;
}

