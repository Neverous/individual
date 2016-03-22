#include <cstdio>
#include <vector>

int tab [ 1000010 ],
	max = 1,
	size,
	first,
	second,
	special;

int main ( void )
{
	scanf ( "%d", & size );
	scanf ( "%d %d %d", & first, & second, & special );
	for ( int s = 0; s < size; ++ s )
	{
		scanf ( "%d", & tab [ s ] );
		tab [ s ] = ! tab [ s ];
	}

	tab [ 0 ] = 2;
	for ( int s  = 0; s < size; ++ s )
	{
		if ( tab [ s ] < 2 )
			continue;

		if ( s + first < size &&
			 tab [ s + first ] )
		{
			tab [ s + first ] = tab [ s ];
			max = ( max > s + first + 1 ) ? max : s + first + 1;
		}

		if ( s + second < size &&
			 tab [ s + second ] )
		{
			tab [ s + second ] = tab [ s ];
			max = ( max > s + second + 1 ) ? max : s + second + 1;
		}

		if ( s + special < size &&
			 tab  [ s ] != 3 &&
			 tab [ s + special ] == 1 )
		{
			tab [ s + special ] = 3;
			max = ( max > s + special + 1 ) ? max : s + special + 1;
		}
	}

	printf ( "%d", max );

#ifdef WIN$HIT
	system ( "pause" );
#endif
    return 0;
}

