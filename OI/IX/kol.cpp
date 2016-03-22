/*		2009
Maciej Szeptuch
XIV LO WROCŁAW
*/

#include <cstdio>
const int _Size = 131072; /* Wielkość drzewa przedziałowego */

int cities,
	places,
	requests,
	start,
	finish,
	people;

struct trainClass
{
	/* POCIĄG ^^ */
	int place [ _Size ], /* zajęte miejsca w danych miastach */
		maxes [ _Size ],
		places; /* ilość wolnych miejsc w pociągu */

	trainClass ( void ) /* Zerowanie */
	{
		for ( int s = 0; s < _Size; ++ s )
			place [ s ] = 0;
		places = 0;
	}

	void setPlaces ( int place ) // ustawianie ilości miejsc w pociągu
	{
		places = place;
	}

	bool addGroup ( int startCity, int endCity, int weight ) // obsługa rezerwacji
	{
		if ( ! _checkFreePlaces ( startCity, endCity, weight ) ) // jeśli nie ma miejsc
			return false;

		_updateTrain ( startCity, endCity, weight ); // kiedy są

		return true;
	}

	bool _checkFreePlaces ( int startCity, int endCity, int weight, int startRoot = 1, int endRoot = 65536, int placeIterator = 1, int moar = 0 )
	{
		if ( startCity == startRoot &&
			 endCity == endRoot )
			 return places - maxes [ placeIterator ] - place [ placeIterator ] - weight - moar >= 0; // jeśli przedziały pasują to sprawdź czy są miejsca

		moar += place [ placeIterator ];

		int _half = ( startRoot + endRoot ) / 2,
			_res; // połowa przedziału w drzewie

		if ( startCity <=  _half && endCity <= _half ) // jeśli przedział mieści się w lewyej odnodze
			_res = _checkFreePlaces ( startCity, endCity, weight, startRoot, _half, placeIterator * 2, moar );

		else if ( startCity <= _half ) // jeśli jest podzielony między dwie
		{
			_res = _checkFreePlaces ( startCity, _half, weight, startRoot, _half, placeIterator * 2, moar );
			if ( ! _res )
				return false;

			_res = _checkFreePlaces ( _half + 1, endCity, weight, _half + 1, endRoot, placeIterator * 2 + 1, moar );
		}

		else // mieści się w drugiej odnodze
			_res = _checkFreePlaces ( startCity, endCity, weight, _half + 1, endRoot, placeIterator * 2 + 1, moar );

		return  _res;
	}

	void _updateTrain ( int startCity, int endCity, int weight, int startRoot = 1, int endRoot = 65536, int placeIterator = 1  )
	{
		if ( startCity == startRoot &&
			 endCity == endRoot ) // jeśli przedziały pasują to zajmij miejsca
		{
			place [ placeIterator ] += weight;
			return;
		}

		int _half = ( startRoot + endRoot ) / 2; // połowa przedziału w drzewie

		if ( startCity <=  _half && endCity <= _half ) // jeśli przedział mieści się w lewyej odnodze
			_updateTrain ( startCity, endCity, weight, startRoot, _half, placeIterator * 2 );

		else if ( startCity <= _half ) // jeśli jest podzielony między dwie
		{
			_updateTrain ( startCity, _half, weight, startRoot, _half, placeIterator * 2 );
			_updateTrain ( _half + 1, endCity, weight, _half + 1, endRoot, placeIterator * 2 + 1 );
		}

		else // mieści się w drugiej odnodze
			_updateTrain ( startCity, endCity, weight, _half + 1, endRoot, placeIterator * 2 + 1 );

		maxes [ placeIterator ] = ( maxes [ placeIterator * 2 ] + place [ placeIterator * 2 ] > maxes [ placeIterator * 2 + 1 ] + place [ placeIterator * 2 + 1 ] ) ? // maksimum z moich dzieci
					maxes [ placeIterator * 2 ] + place [ placeIterator * 2 ] :  // pierwsza odnoga
					maxes [ placeIterator * 2 + 1 ] + place [ placeIterator * 2 + 1 ]; // druga odnoga
	}
};

trainClass train;

int main ( void )
{
	scanf ( "%d %d %d", & cities, & places, & requests );

	train . setPlaces ( places );

	for ( int r = 0; r < requests; ++ r )
	{
		scanf ( "%d %d %d", & start, & finish, & people );
		printf ( "%s\n", train . addGroup ( start, finish - 1, people ) ? "T" : "N" );
	}
	return 0;
}

