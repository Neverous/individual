/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>

int tests,
	upSize,
	downSize,
	result [ 2 ] [ 201 ],
	sum;

char number [ 201 ];

bool last;

void solve ( char * number );
inline int sumOfDigits ( char * number );
void BigIntDivByThree ( char * number );

int main ( void )
{
	scanf ( "%d", & tests );

	for ( int t = 0; t < tests; ++ t )
	{
		scanf ( "%s", number );
		solve ( number );
	}
	return 0;
}

void solve ( char * number )
{
	upSize = downSize = last = 0;

	for ( int i = 0; true; ++ i )
	{
		switch ( sumOfDigits ( number ) % 3 )
		{
			case 2 :
				if ( ! last )
					result [ 1 ] [ downSize ++ ] = i;
				last = true;
				break;

			case 1 :
				if ( last )
					result [ 1 ] [ downSize ++ ] = i;
				else
					result [ 0 ] [ upSize ++ ] = i;
				break;

			default :
				if ( last )
					result [ 0 ] [ upSize ++ ] = i;
				last = false;
				break;
		}

		if ( ! strcmp ( "0", number ) )
			break;

		if ( ! strcmp ( "1", number ) || ! strcmp ( "2", number ) )
			strcpy ( number, "0" );

		else
			BigIntDivByThree ( number );
	}
	printf ( "%d ", upSize );
	for ( int s = 0; s < upSize; ++ s )
		printf ( "%d ", result [ 0 ] [ s ] );

	printf ( "\n%d ", downSize );
	for ( int s = 0; s < downSize; ++ s )
		printf ( "%d ", result [ 1 ] [ s ] );
	printf ( "\n" );
}

inline int sumOfDigits ( char * number )
{
	sum = 0;
	for ( int s = 0; number [ s ] != 0; ++ s )
		sum += number [ s ] - '0';
	return sum;
}

void BigIntDivByThree ( char * number )
{
	int pos = 0;
	for ( int s = 0, act = 0; number [ s ] != 0; ++ s )
	{
		act = number [ s ] - '0' + act * 10;

		if ( pos == 0 && act < 3 )
			continue;

		number [ pos ++ ] = '0' + act / 3;
		act = act % 3;
	}

	if ( pos == 0 )
		number [ pos ++ ] = '0';

	number [ pos ] = 0;
}

