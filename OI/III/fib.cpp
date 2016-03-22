/* Maciej Szeptuch 2008
XIV LO Wrocław
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

struct BigInt
{
	char number [ 202 ];
	int len;

	BigInt ( int a )
	{
		for ( int i = 0; i < 201; ++ i )
			number [ i ] = '0';

		number [ 201 ] = 0;

		len = 200;
		for ( ; a > 0; -- len )
		{
			number [ len ] = (a % 10) + '0';
			a /= 10;
		}
		len = 200 - len;
	}

	BigInt ( const BigInt & A )
	{
		for ( int i = 0; i < 202; ++ i )
			number [ i ] = A . number [ i ];

		len = A . len;
	}

	BigInt ( void )
	{
		BigInt ( 0 );
	}

	BigInt operator+ ( const BigInt & B  )
	{
		BigInt wynik ( B );
		int moar = 0,
			i;
		for ( i = 200; i >= 0; -- i )
		{
			wynik . number [ i ] += number [ i ] - '0' - '0' + moar;
			moar = wynik . number [ i ] / 10;
			wynik . number [ i ] %= 10;
			wynik . number [ i ] += '0';
		}
		wynik . len = wynik . len > len ? wynik . len : len;
		if ( wynik . number [ 200 - wynik . len ] > '0' )
			wynik . len ++;
		return wynik;
	}

	BigInt operator+ ( int B )
	{
		BigInt wynik ( B );
		int moar = 0,
			i;
		for ( i = 200; i >= 0; -- i )
		{
			wynik . number [ i ] += number [ i ] - '0' - '0' + moar;
			moar = wynik . number [ i ] / 10;
			wynik . number [ i ] %= 10;
			wynik . number [ i ] += '0';
		}
		wynik . len = wynik . len > len ? wynik . len : len;
		if ( wynik . number [ 200 - wynik . len ] > '0' )
			wynik . len ++;
		return wynik;
	}

	BigInt operator= ( const BigInt & B )
	{
		for ( int i = 0; i < 202; ++ i )
			number [ i ] = B . number [ i ];

		len = B . len;
	}
};

char fibst [ 100 ] = "b",
	 fibnd [ 100 ] = "a",
	 swapperTab [ 100 ],
	 pattern [ 100 ];
//	 search [ 75 ];

int lenOfPattern = 0,
	minFibWord = 2,
	flag = 0,
	fib,
//	kmp [ 75 ],
	lenOfFibst = 1,
	lenOfFibnd = 1,
	swapper,
	toAddst,
	toAddnd;

BigInt BlenOfFibst,
	   BlenOfFibnd,
	   Bswapper;

BigInt solve ( void );
int strCount ( char * what, char * where );
char * strMake ( char * str );
char * addStrings ( char * A, char * B );

int main ( void )
{
	scanf ( "%s %d", pattern, & fib );
	if ( strcmp ( pattern, "b" ) == 0 && fib == 1 )
	{
		printf ( "1\n" );
		return 0;
	}
	lenOfPattern = strlen ( pattern );
	solve ( );
	for ( int i = 200 - BlenOfFibst . len + ( BlenOfFibst . len > 0 ? 1 : 0 ); i <= 200; ++ i )
		printf ( "%c", BlenOfFibst . number [ i ] );
	printf ( "\n" );
	return 0;
}

BigInt solve ( void )
{
	// znajdź minimalne słowo fibonacciego

	while ( lenOfFibst < lenOfPattern )
	{
		strcpy ( swapperTab, fibnd );
		strcat ( fibnd, fibst );
		strcpy ( fibst, swapperTab );
		swapper = lenOfFibnd;
		lenOfFibnd += lenOfFibst;
		lenOfFibst = swapper;
		++ minFibWord;
	}
	BlenOfFibst = BigInt ( strCount ( pattern, fibst ) );
	BlenOfFibnd = BigInt ( strCount ( pattern, fibnd ) );
	toAddst = strCount ( pattern, strMake ( fibst ) ) - strCount ( pattern, fibst );
	toAddnd = strCount ( pattern, strMake ( fibnd ) ) - strCount ( pattern, fibnd );
	if ( minFibWord > fib )
		return 0;

	for ( int act = minFibWord; act <= fib; ++ act )
	{
		Bswapper = BlenOfFibnd;
		BlenOfFibnd = BlenOfFibnd + BlenOfFibst;
		BlenOfFibst = Bswapper;

		if ( flag )
			BlenOfFibnd = BlenOfFibnd + toAddst;
		else
			BlenOfFibnd = BlenOfFibnd + toAddnd;
		flag = ! flag;
	}

	return BlenOfFibst;

}

char * strMake ( char * str )
{
	char * result = new char [ strlen ( str ) + lenOfPattern + 1 ];
	int i = 0;
	while ( str [ i ] != 0 )
		result [ i ] = str [ i ++ ];

	for ( int j = 0; j < lenOfPattern - 1; ++ j, ++ i )
		result [ i ] = result [ j ];

	result [ i ] = 0;

	return result;
}

int strCount ( char * what, char * where )
{
	/*int len = 0,
		act = 0,
		result = 0,
		lenW = 0;

	for ( len = 0; what [ len ] != 0; ++ len )
		search [ len ] = what [ len ];

	lenW = len;

	search [ len ++ ] = 'x';

	for ( int j = 0; where [ j ] != 0; ++ len, ++ j )
		search [ len ] = where [ j ];

	kmp [ 0 ] = 0;

	for ( int i = 1; i <= len; ++ i )
	{
		kmp [ i ] = 0;

		while ( act > 0 && search [ act ] != search [ i ] )
			act = kmp [ act - 1 ];

		if ( search [ act ] == search [ i ] )
			kmp [ i ] = ++ act;
	}

	for ( int i = lenW + 1; i < len; ++ i )
		if ( kmp [ i ] == lenW )
			++ result;

	return result;*/
	/* BRUTE O.o */
	int result = 0;
	for ( int i = 0,j; where [ i ] != 0; ++ i )
	{
		j = 0;
		while ( what [ j ] != 0 && where [ i + j ] == what [ j ] )
			++ j;
		if ( what [ j ] == 0 )
			++ result;
	}
	return result;
} // KMP

