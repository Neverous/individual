/* 2009
Maciej Szeptuch
XIV LO Wrocław
*/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using namespace std;

struct BigDouble
{
	int comma,
		length;

	bool sign;

	char number [ 301 ];

	BigDouble ( void )
	{
		comma = 0;
		sign = true;
		length = 0;

		for ( int i = 0; i < 301; ++ i )
			number [ i ] = '0';

	}

	bool append ( char * num )
	{
		int start = 0,
			len = strlen ( num );

		bool isComma = false;

		for ( int i = 0; i < 301; ++ i )
			number [ i ] = '0';

		sign = true;
		length = 0;
		comma = 0;

		for ( int i = 0; i < len; ++ i )
			if ( num [ i ] == ',' )
			{
				isComma = true;
				len -= 1;
				break;
			}

		if ( isComma )
			while ( num [ len ] == '0' )
				-- len;

		if ( num [ start ] == '+' )
		{
			len -= 1;
			++ start;
		}
		else if ( num [ start ] == '-' )
		{
			++ start;
			sign = false;
			len -= 1;
		}

		for ( int i = len - 1; num [ start ] != 0 && i >= 0; ++ start, -- i )
		{
			if ( num [ start ] == ',' )
			{
				comma = ++i;
				continue;
			}
			number [ i ] = num [ start ];
		}
		tidy ( );
		return true;
	}

	bool add ( BigDouble A )
	{
		if ( A . sign != sign )
		{
			A . sign = true;
			return sub ( A );
		}

		int rest = 0,
			i;

		move ( A );

		for ( i = 0; i < A . length || i < length || rest; ++ i )
		{
			number [ i ] += rest + A . number [ i ] - 2 * '0';
			rest = number [ i ] / 10;
			number [ i ] %= 10;
			number [ i ] += '0';
		}

		tidy ( );
		return true;
	}

	bool move ( BigDouble & A )
	{
		if ( A . comma > comma )
		{
			for ( int i = length + A . comma - comma - 1; i >= A . comma - comma; -- i )
			{
				number [ i ] = number [ i - A . comma + comma ];
				number [ i - A . comma + comma ] = '0';
			}
			length += A . comma - comma;
			comma = A . comma;
		}
		else if ( comma > A . comma )
		{
			for ( int i = A . length + comma - A . comma - 1; i >= comma - A . comma; -- i )
			{
				A . number [ i ] = A . number [ i - comma + A . comma  ];
				A . number [ i - comma + A . comma  ] = '0';
			}
			A . length += comma - A.comma;
			A . comma = comma;

		}
		return true;
	}

	bool sub ( BigDouble A )
	{
		if ( ! A . sign )
			return add ( A );

		if ( greater ( A ) )
		{
			sign = ! sign;
			for ( int i = 0; i < 300; ++ i )
				swap ( A . number [ i ], number [ i ] );
			swap ( A . length, length );
			swap ( A . comma, comma );
		}

		move ( A );

		int rest = 0;
		for ( int i = 0; i < A . length || rest; ++ i )
		{
			number [ i ] -= A . number [ i ] + rest;
			if ( number [ i ] < 0 )
			{
				number [ i ] = 10 + number [ i ];
				rest = 1;
			}
			else
				rest = 0;

			number [ i ] += '0';
		}

		tidy ( );
		return true;
	}

	void tidy ( void )
	{
		int mov = 0;
		for ( int i = 0; i < comma && number [ i ] == '0'; ++ i )
			mov ++;

		for ( int i = 0; i <= length; ++ i )
			number [ i ] = number [ i + mov ];

		for ( int i = 300; number [ i ] == '0'; -- i )
			length = i;

		comma -= mov;
		if ( comma < 0 )
			comma = 0;
		if ( length < 0 )
			length = 0;

		if ( comma != 0 && comma >= length)
			length = comma+1;

		for ( int i = length; i < 300; ++ i )
			number [ i ] = '0';
	}

	bool greater ( BigDouble A )
	{
		if ( A . length - A . comma > length - comma )
			return true;

		if ( A . length - A . comma == length - comma )
		{
			move ( A );

			for ( int i = ( A . length > length ) ? A . length : length; i >= 0; -- i )
				if ( A . number [ i ] > number [ i ] )
					return true;
				else if ( A . number [ i ] < number [ i ] )
					return false;

		}

		return false;
	}

};

int nums;
char sth [ 300 ];
BigDouble A,B;

int main ( void )
{
	scanf ( "%d", & nums );
	for ( int n = 0; n < nums; ++ n )
	{
		scanf ( "%s", sth );
		B . append ( sth );
		A . add ( B );
	}

	if ( A . length == 0 )
	{
		printf ( "0\n" );
		return 0;
	}

	if ( ! A . sign )
		printf ( "-" );

	for ( int i = A . length - 1; i >= 0; -- i )
	{
		printf ( "%c", A . number [ i ] );

		if ( A . comma == i && i != 0 )
			printf ( "," );
	}
	printf ( "\n" );
	return 0;
}

