/*		2008
Maciej Szeptuch
XIV LO WROCŁAW
Zadanie: GAŚNICE
*/
#include <cstdio>
#include <vector>

#define SIZE 45
using namespace std;

int verts,	// ilość pokoi
	features,	// zastosowania gaśnicy
	dist,	// maksymalna odległość dla gaśnicy
	start,	// początek ścieżki
	end,	// koniec ścieżki
	result,	// wynik
	sum,
	tmp;

vector < int > tree [ 100010 ];	// graf
int resultTab [ 100010 ] [ SIZE ]; // poprzednie podejście dawało pesymistycznie to samo ^^, a tak jest czytelniej

void initTab ( int v1, int v2, int w ) // przesuwanie tablicy
{
	for ( int i = 0; i < SIZE; ++ i )	// ...
		resultTab [ v1 ] [ i ] += resultTab [ v2 ] [ i ]; // ...
}

void moveTab ( int v, int w )
{
	for ( int i = SIZE / 2 + dist + 1; i - w >= 0; -- i )	// ...
		resultTab [ v ] [ i ] = resultTab [ v ] [ i - w ]; // ...

	for ( int i = 0; i < w; ++ i ) // ...
		resultTab [ v ] [ i ] = resultTab [ v ] [ SIZE / 2 + i ] = 0;  // ...
}

void optimTab ( int v ) // optymalizuj tabelkę wyniku
{
	for ( int i = SIZE / 2 + dist + 1; resultTab [ v ] [ dist ] > 0 && i>= SIZE / 2; -- i )	// i jest gdzie to wykorzystać
	{
		resultTab [ v ] [ dist ] += resultTab [ v ] [ i ]; // to wykorzystaj
		resultTab [ v ] [ i ] = 0;	// nie ma więcej do wykorzystania
		if ( resultTab [ v ] [ dist ] < 0 )	// jeśli wykorzytamy więcej niż jest
		{
			resultTab [ v ] [ dist - 1 ] += resultTab [ v ] [ dist ];	// to znowu mamy nadmiar
			resultTab [ v ] [ dist ] = 0; // ...
			if ( resultTab [ v ] [ dist - 1 ] < 0 )
			{
				resultTab [ v ] [ i ] = resultTab [ v ] [ dist - 1 ];
				resultTab [ v ] [ dist - 1 ] = 0;
			}
		}
	}
}

void checkExtinguisher ( int v ) // sprawdź gaśnicę
{
	optimTab ( v );

	if ( resultTab [ v ] [ dist ] <= 0 )
		return;

	tmp = ( resultTab [ v ] [ dist ] + features - 1 ) / features;

	resultTab [ v ] [ dist ] -= tmp * features;
	result += tmp;
	if ( resultTab [ v ] [ dist ] < 0 );
	{
		resultTab [ v ] [ SIZE / 2 ] = resultTab [ v ] [ dist ];
		resultTab [ v ] [ dist ] = 0;
	}

	optimTab ( v );
}

void dfs ( int v, int f )	// DFS do przeglądania grafu
{
	for ( int i = 0; i < tree [ v ] . size ( ); ++ i ) // dla wszystkich dzieci
	{
		if ( tree [ v ] [ i ] == f )	// jeśli ojcem
			continue; 	// to pomiń
		dfs ( tree [ v ] [ i ], v ); // sprawdź co tam ;)
		initTab ( v, tree [ v ] [ i ], 1 );
	}
	resultTab [ v ] [ 0 ] = 1;
	checkExtinguisher ( v );
	moveTab ( v, 1 );
}

void solve ( void ) // Obliczanie optymalnego wyniku
{
	dfs ( 0, 0 );
	for ( int i = 0; i < SIZE; ++ i )
		sum += resultTab [ 0 ] [ i ];
	if ( sum > 0 )
		result += ( sum + features - 1 ) / features;

}

int main ( void )
{
	scanf ( "%d %d %d", & verts, & features, & dist ); // Wczytaj ile pokoi, ile gaśnica obsłuży pokoi, i na jaką maksymalną odległość
	for ( int i = 0; i < verts - 1; ++ i )	// Wczytywanie krawędzi
	{
		scanf ( "%d %d", & start, & end );	// Początek, koniec
		-- start;	// Numerowanie od 0
		-- end;	//	...
		tree [ start ] . push_back ( end );	// Dodanie do drzewa
		tree [ end ] . push_back ( start );	// ...
	}

	solve ( );
	if ( result * features < verts )
		result = ( verts + features - 1 ) / features;
	printf ( "%d\n", result );	// Wynik
	return 0;
}

