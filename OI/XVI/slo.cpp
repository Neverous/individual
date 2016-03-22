/*		2008
Maciej Szeptuch
XIV LO WROCŁAW
Zadanie: SŁONIE
*/
#include <cstdio>

#define SIZE 1000010
typedef long long int lld;

lld elephants,		//Liczba słoni w Bajtocji
	weight [ SIZE ],			// wagi słoni
	startPosition [ SIZE ],		// początkowe ustawienie słoni
	endPosition [ SIZE ],		// końcowe ustawienie
	visited [ SIZE ],			// czy odwiedzony
	min,						// minimalny element cyklu
	minWeight = 10010,			// minimum z całego zbioru
	length,						// długość cyklu
	sum,						// suma elementów w cyklu
	tmp;						// zmienna tymczasowa

lld dfs ( lld v ) // szukanie cykli
{
	while ( ! visited [ v ] )
	{
		visited [ v ] = true;	// Odwiedzony
		sum += weight [ startPosition [ v ] ];	// suma się zwiększa
		min = ( min < weight [ startPosition [ v ] ] ) ? min : weight [ startPosition [ v ] ]; // minimum się zmniejsza
		++ length;	// długość cyklu się zwiększa
		v = endPosition [ startPosition [ v ] ]; // dalej
	}

	return length;
} // end dfs ( );

lld solve ( void ) // wyznaczenie optymalnego rozwiązania
{
	lld result = 0;

	for ( lld i = 0; i < elephants; ++ i )
	{
		min = 10010; // zerowanie
		sum = length = 0; // c.d.
		if ( ! visited [ i ] ) // jeśli jeszcze nie odwiedzony
			if ( dfs ( i ) > 1 ) // to odwiedź
			result += ( minWeight * ( length + 1 ) + sum + min < min * ( length - 2 ) + sum ) ? minWeight * ( length + 1 ) + sum + min : min * ( length - 2 ) + sum; // z tym że można go nieco ulepszyć jeśli koszt zamiany minimum z cyklu i minimum ogólnego i z powrotem będzie dawał jakiś zysk
	}

	return result;
} // end solve ( );

int main ( void )
{
	scanf ( "%lld", & elephants );

	for ( lld i = 0; i < elephants; ++ i )
	{
		scanf ( "%lld", & weight [ i ] );
		minWeight = ( minWeight < weight [ i ] ) ? minWeight : weight [ i ]; // minimum z całego zbioru
	}	// Wczytywanie wag

	for ( lld i = 0; i < elephants; ++ i )
	{
		scanf ( "%lld", & startPosition [ i ] );
		-- startPosition [ i ];
	}	// Wczytywanie początkowego ustawienia

	for ( lld i = 0; i < elephants; ++ i )
	{
		scanf ( "%lld", & tmp );
		endPosition [ tmp - 1 ] = i; // element tmp ląduje na i-tym miejscu
	}	// Wczytywanie końcowego ustawienia

	printf ( "%lld", solve ( ) );
	return 0;
} // end main ( );

