/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/

#include <cstdio>
#include <algorithm>
#include <vector>

struct Tree
{
	static const int SIZE = 1024*512;
	int data [ SIZE ];

	Tree ( void )
	{
		for ( int s = 0; s < SIZE; ++ s )
			data [ s ] = 0;
	}

	void insert ( int start, int end, int value, int rootStart = 1, int rootEnd = SIZE / 2, int index = 1 )
	{
		if ( start == rootStart && end == rootEnd )
		{
			data [ index ] += value;
			return;
		}

		int half = ( rootStart + rootEnd ) / 2;

		if ( start <= half && end <= half )
			insert ( start, end, value, rootStart, half, index * 2 );
		else if ( start > half && end > half )
			insert ( start, end, value, half + 1, rootEnd, index * 2 + 1 );
		else if ( start <= half && end > half )
		{
			insert ( start, half, value, rootStart, half, index * 2 );
			insert ( half + 1, end, value, half + 1, rootEnd, index * 2 + 1 );
		}
	}

	int get ( int start, int end, int rootStart = 1, int rootEnd = SIZE / 2, int index = 1 )
	{
		if ( start == rootStart && end == rootEnd )
			return data [ index ];

		int half = ( rootStart + rootEnd ) / 2,
			result = data [ index ];

		if ( start <= half && end <= half )
			result += get ( start, end, rootStart, half, index * 2 );
		else if ( start > half && end > half )
			result += get ( start, end, half + 1, rootEnd, index * 2 + 1 );

		return result;
	}
};

std :: vector < int > graph [ 250025 ];

int size,
	from,
	to,
	trips,
	dfsTmp = 1,
	road [ 250025 ],
	start [ 250025 ],
	end [ 250025 ];

char action;

Tree tree;

void dfs ( int vert, int aRoad );

int main ( void )
{
	scanf ( "%d", & size );
	for ( int s = 0; s < size - 1; ++ s )
	{
		scanf ( "%d %d", & from, & to );
		-- from;
		-- to;

		graph [ from ] . push_back ( to );
	}

	dfs ( 0, 0 );

	scanf ( "%d", & trips );
	for ( int t = 0; t < trips + size - 1; ++ t )
	{
		scanf ( " %c %d", & action, & to );
		-- to;
		if ( action == 'A' )
		{
			scanf ( "%d", & to );
			-- to;
			tree . insert ( start [ to ], end [ to ], 1 );
		}
		else if ( action == 'W' )
			printf ( "%d\n", road [ to ] - tree . get ( start [ to ], start [ to ] ) );
	}
	return 0;
}

void dfs ( int vert, int aRoad )
{
	road [ vert ] = aRoad;
	start [vert ] = dfsTmp ++;

	for ( unsigned int s = 0; s < graph [ vert ] . size ( ); ++ s )
		dfs ( graph [ vert ] [ s ], aRoad + 1 );

	end [ vert ] = dfsTmp - 1;
}

