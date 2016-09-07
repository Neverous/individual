/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>

/* [x][y][z] z|y/x_ */
int size, height,
	block[4][6][6][20][20][20],
	temp[20][20][20],
	temp2[20][20][20],
	result[20][20][20];

bool res;

inline static void rotate(int ret[20][20][20], const int tab[20][20][20], const int &degree);
inline static void makeWall(int ret[20][20][20], const int tab[20][20][20], const int &wall);
inline static const bool blockMatch(const int tab[20][20][20], const int match[20][20][20]);
inline static void blockPut(int tab[20][20][20], const int put[20][20][20]);
inline static void blockRemove(int tab[20][20][20], const int remove[20][20][20]);
inline static const bool solve(const int &wall, const int &mask);

int main(void)
{
	scanf("%d", &size);
	for(int s = 0; s < 6; ++ s)
		for(int x = 0; x < size; ++ x)
			for(int y = 0; y < size; ++ y)
			{
				scanf("%d", &height);
				for(int z = 0; z < height; ++ z)
					block[0][0][s][x][y][z] = s + 1;
			}

	for(int b = 0; b < 6; ++ b)
		for(int d = 0; d < 4; ++ d)
		{
			rotate(temp, block[0][0][b], d);
			for(int w = 0; w < 6; ++ w)
			{
				makeWall(temp2, temp, w);
				for(int x = 0; x < size; ++ x)
					for(int y = 0; y < size; ++ y)
						for(int z = 0; z < size; ++ z)
							block[d][w][b][x][y][z] = temp2[x][y][z];
			}
		}

	for(int x = 0; x < size; ++ x)
		for(int y = 0; y < size; ++ y)
			for(int z = 0; z < size; ++ z)
				result[x][y][z] = block[0][0][0][x][y][z];

	puts((res = solve(1, 1))?"Yes":"No");
	if(res)
		for(int z = 0; z < size; ++ z)
			for(int x = 0; x < size; ++ x)
				for(int y = 0; y < size; ++ y)
					printf("%d%c", result[x][y][z], y + 1 == size?'\n':' ');

	return 0;
}

inline static const bool solve(const int &wall, const int &mask)
{
	if(wall == 6)
		return mask + 1 == (1 << 6);

	for(int b = 1; b < 6; ++ b)
		if(~mask & (1 << b)) for(int d = 0; d < 4; ++ d)
		{
			if(blockMatch(result, block[d][wall][b]))
			{
				blockPut(result, block[d][wall][b]);
				if(solve(wall + 1, mask | (1 << b)))
					return true;

				blockRemove(result, block[d][wall][b]);
			}
		}

	return false;
}

inline static const bool blockMatch(const int tab[20][20][20], const int match[20][20][20])
{
	for(int x = 0; x < size; ++ x)
		for(int y = 0; y < size; ++ y)
			for(int z = 0; z < size; ++ z)
				if(tab[x][y][z] && match[x][y][z])
					return false;

	return true;
}

inline static void blockPut(int tab[20][20][20], const int put[20][20][20])
{
	for(int x = 0; x < size; ++ x)
		for(int y = 0; y < size; ++ y)
			for(int z = 0; z < size; ++ z)
				if(put[x][y][z])
					tab[x][y][z] = put[x][y][z];

	return;
}

inline static void blockRemove(int tab[20][20][20], const int remove[20][20][20])
{
	for(int x = 0; x < size; ++ x)
		for(int y = 0; y < size; ++ y)
			for(int z = 0; z < size; ++ z)
				if(tab[x][y][z] == remove[x][y][z])
					tab[x][y][z] = 0;

	return;
}

inline static void rotate(int ret[20][20][20], const int tab[20][20][20], const int &degree)
{
	for(int x = 0, X = 0, Y = 0; x < size; ++ x)
		for(int y = 0; y < size; ++ y)
			for(int z = 0; z < size; ++ z)
			{
				switch(degree)
				{
					case 1:
						X = size - 1 - y;
						Y = x;
						break;

					case 2:
						X = size - 1 - x;
						Y = size - 1 - y;
						break;

					case 3:
						X = y;
						Y = size - 1 - x;
						break;

					case 0:
					default:
						X = x;
						Y = y;
						break;
				}

				ret[x][y][z] = tab[X][Y][z];
			}

	return;
}

inline static void makeWall(int ret[20][20][20], const int tab[20][20][20], const int &wall)
{
	/* WALL:
	 *	1 - front
	 *	2 - right
	 *	3 - back
	 *	4 - left
	 *	5 - top
	 */
	for(int x = 0, X = 0, Y = 0, Z = 0; x < size; ++ x)
		for(int y = 0; y < size; ++ y)
			for(int z = 0; z < size; ++ z)
			{
				switch(wall)
				{
					case 1:
						X = x;
						Y = size - 1 - z;
						Z = y;
						break;

					case 2:
						X = z;
						Y = y;
						Z = size - 1 - x;
						break;

					case 3:
						X = x;
						Y = z;
						Z = size - 1 - y;
						break;

					case 4:
						X = size - 1 - z;
						Y = y;
						Z = x;
						break;

					case 5:
						X = x;
						Y = size - 1 - y;
						Z = size - 1 - z;
						break;

					case 0:
					default:
						X = x;
						Y = y;
						Z = z;
						break;
				}

				ret[x][y][z] = tab[X][Y][Z];
			}

	return;
}
