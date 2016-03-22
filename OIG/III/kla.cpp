/* Maciej Szeptuch
 * XIV LO Wrocław
 * 2009
 */
#include <cstdio>
#include <vector>
#include <cstring>

int size,
	firstX,
	firstY,
	secondX,
	secondY,
	limesUp,
	limesDown,
	limesLeft,
	limesRight,
	moveX,
	moveY,
	positionX,
	positionY;

bool iTurn;

char turn [ 10 ],
	 direction [ 10 ];

std :: vector < std :: vector < int > > result;

inline void prepare ( void );
inline void turnRight ( void );
inline void turnLeft ( void );
inline void printResult ( void );
inline void solve ( void );

int main ( void )
{
	scanf ( "%d %s %s", & size, direction, turn );
	scanf ( "%d %d %d %d", & firstX, & secondX, & firstY, & secondY );
	prepare ( );
	solve ( );
	printResult ( );
	return 0;
}

inline void prepare ( void )
{
	int width = secondX - firstX + 1,
		height = secondY - firstY + 1;
	limesUp = limesRight = size + 1;
	result . resize ( height );
	for ( int h = 0; h < height; ++ h )
		result [ h ] . resize ( width );

	if ( ! strcmp ( turn, "PRAWO" ) )
		iTurn = true;

	else
		iTurn = false;

	if ( ! strcmp ( direction, "POLNOC" ) )
	{
		if ( iTurn )
			positionX = positionY = 1;

		else
		{
			positionX = size;
			positionY = 1;
		}

		moveX = 0;
		moveY = 1;
	}
	else if ( ! strcmp ( direction, "POLUDNIE" ) )
	{
		if ( iTurn )
			positionX = positionY = size;

		else
		{
			positionX = 1;
			positionY = size;
		}

		moveX = 0;
		moveY = -1;
	}
	else if ( ! strcmp ( direction, "WSCHOD" ) )
	{
		if ( iTurn )
		{
			positionX = 1;
			positionY = size;
		}
		else
			positionX = positionY = 1;

		moveX = 1;
		moveY = 0;
	}
	else
	{
		if ( iTurn )
		{
			positionX = size;
			positionY = 1;
		}
		else
			positionX = positionY = size;

		moveX = -1;
		moveY = 0;
	}
}

inline void printResult ( void )
{
	int width = secondX - firstX + 1,
		height = secondY - firstY + 1;

	for ( int h = height - 1; h >= 0; -- h )
		for ( int w = 0; w < width; ++ w )
			printf ( "%d%c", result [ h ] [ w ], w + 1 == width ? '\n' : ' ' );
}

inline void turnRight ( void )
{
	if ( moveX == 0 )
	{
		if ( moveY == 1 )
			limesLeft = positionX;

		else
			limesRight = positionX;
	}

	if ( moveY == 0 )
	{
		if ( moveX == 1 )
			limesUp = positionY;

		else
			limesDown = positionY;
	}

	int tmp = moveX;
	moveX = moveY;
	moveY = - tmp;
}

inline void turnLeft ( void )
{
	if ( moveX == 0 )
	{
		if ( moveY == -1 )
			limesLeft = positionX;

		else
			limesRight = positionX;
	}

	if ( moveY == 0 )
	{
		if ( moveX == -1 )
			limesUp = positionY;

		else
			limesDown = positionY;
	}

	int tmp = moveX;
	moveX = - moveY;
	moveY = tmp;
}

inline void solve ( void )
{
	for ( int m = 0, k = 1; m < 2 * size - 1; positionX += moveX, positionY += moveY, ++ k )
	{
		if ( positionX >= firstX && positionX <= secondX &&
			 positionY >= firstY && positionY <= secondY )
			result [ positionY - firstY ] [ positionX - firstX ] = k;

		if ( ( ! moveX && ( positionY + moveY == limesUp || positionY + moveY == limesDown ) ) ||
			 ( ! moveY && ( positionX + moveX == limesLeft || positionX + moveX == limesRight ) ) )
		{
			++ m;
			if ( iTurn )
				turnRight ( );

			else
				turnLeft ( );
		}
	}
}

