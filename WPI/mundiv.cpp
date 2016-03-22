/* 2009
Maciej Szeptuch
XIV LO Wroc�aw
*/
#include <cstdio>

int number,
	dividers [ 8000008 ];

bool first;

inline void eratostenes ( void );

int main ( void )
{
	eratostenes ( );
	while ( scanf ( "%d", & number ) != -1 &&
			number )
	{
		first = true;
		while ( number > 1 )
		{
			if ( ! dividers [ number ] )
				dividers [ number ] = number;

			if ( ! first )
				printf ( "*" );
			printf ( "%d", dividers [ number ] );
			number /= dividers [ number ];
			first = false;
		}
		printf ( "\n" );
	}
	return 0;
}

inline void eratostenes ( void )
{
	dividers [ 1 ] = 1;
	for ( int i = 2; i * i <= 8000004; ++ i )
	{
		if ( dividers [ i ] )
			continue;

		dividers [ i ] = i;

		for ( int  j = i * i; j <= 8000004; j += i )
			if ( ! dividers [ j ] )
				dividers [ j ] = i;
	}
}

