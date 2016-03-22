#include <cstdio>
#include <cstdlib>

struct BigInt
{
	long long int data [ 200 ];
	const static int BASE = 100000000;

	BigInt ( void )
	{
		for ( int d = 0; d < 200; ++ d )
			data [ d ] = 0;
	}

	BigInt ( int number )
	{
		for ( int d = 0; d < 200; ++ d )
			data [ d ] = 0;
		data [ 199 ] = number;
	}

	BigInt operator * ( int number )
	{
		int position = 199,
			rest = 0;

		while ( position >= 0  )
		{
			data [ position ] *= number;
			data [ position ] += rest;
			rest = data [ position ] / BASE;
			data [ position ] %= BASE;
			-- position;
		}

		return *this;
	}

	BigInt operator *= ( int number )
	{
		int position = 199,
			rest = 0;

		while ( position >= 0  )
		{
			data [ position ] *= number;
			data [ position ] += rest;
			rest = data [ position ] / BASE;
			data [ position ] %= BASE;
			-- position;
		}

		return *this;
	}

	void print ( void )
	{
		int z = 0;
		for ( int  p = 0, write = 0, in = 0; p < 200; ++ p )
		{
			if ( ! write &&
				 data [ p ] > 0 )
				write = 1;

			if ( write )
			{
				if ( in )
				{
					z = BASE / 10;
					for ( int x = data [ p ]; x > 0; x /= 10 )
						z /= 10;

					while ( z > 0 )
					{
						printf ( "0" );
						z /= 10;
					}
				}
				printf ( "%lld", data [ p ] );
				in = 1;
			}
		}
		printf ( "\n" );
	}

	void operator = ( int A )
	{
		for ( int d = 0; d < 200; ++ d )
			data [ d ] = 0;
		data [ 199 ] = A;
	}
};

int number;
BigInt result = 1;

int main ( void )
{
	scanf ( "%d", & number );

	for ( int n = 4; n <= number; n += 2 )
		result *= n - 1;

	result . print ( );

    return 0;
}

