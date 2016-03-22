/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<cstring>
#define SIZE 1048576

int size,
	position,
	moves;
long long int result,
			  sumTree[1000001],
			  max,
			  temp;

struct iTree
{
	long long int data[SIZE * 2];

	iTree(void)
	{
		memset(data, 0, SIZE * 2 * sizeof(long long int));
	}

	void propagateTree(void)
	{
		for(int d = SIZE - 1; d > 0; -- d)
			data[d] = data[d * 2] + data[d * 2 + 1];
	}

	long long int findBestMove(int position)
	{
		position += SIZE;
		long long int bestMove = data[position],
					  actMove = 0;
		int actPosition = position;

		/* LEWO */

		for(;actPosition; actPosition /= 2) // Cały czas w lewo
		{
			if(data[actPosition] + actMove > bestMove) // taki przedział ma fajną sumę
				bestMove = data[actPosition] + actMove;

			if(!(actPosition % 2)) // Jestem lewym dzieckiem
			{
				actMove += data[actPosition]; // trzeba dodać co mam bo wyskakuje z poddrzewa
				if(actMove > bestMove) // aktualne coś ma fajną sumę
					bestMove = actMove;
				
				if(!(actPosition & (actPosition - 1))) // Jestem potęgą dwójki - doszedłem do lewej granicy drzewa... fajny sposób...
					break;

				while(actPosition < SIZE)
					actPosition *= 2;

				actPosition = actPosition * 2 - 1;
			}

		}

		if(!actPosition) // Jestem w korzeniu
			actMove = data[actPosition];
		
		if(actMove > bestMove)
			bestMove = actMove;

		/* PRAWO */
		actPosition = position;
		actMove = 0;
		for(;actPosition; actPosition /= 2) // Cały czas w prawo
		{
			if(data[actPosition] + actMove > bestMove) // taki przedział ma fajną sumę
				bestMove = data[actPosition] + actMove;

			if(actPosition % 2) // Jestem prawym dzieckiem
			{
				actMove += data[actPosition]; // trzeba dodać co mam bo wyskakuje z poddrzewa
				if(actMove > bestMove) // aktualne coś ma fajną sumę
					bestMove = actMove;
				
				if(!(actPosition & (actPosition + 1))) // Jestem potęgą dwójki - 1 - doszedłem do prawej granicy drzewa... fajny sposób...
					break;

				while(actPosition < SIZE)
					actPosition = actPosition * 2 + 1;

				actPosition = actPosition * 2 + 2;
			}

		}

		if(!actPosition) // Jestem w korzeniu
			actMove = data[actPosition];
		
		if(actMove > bestMove)
			bestMove = actMove;

		return bestMove;
	}
};

iTree tree;

int main(void)
{
	scanf("%d %d %d", &size, &position, &moves);
	for(int s = 0; s < size; ++ s)
	{
		scanf("%lld", &tree.data[SIZE + s + 1]);
		sumTree[s + 1] = tree.data[SIZE + s + 1];
		sumTree[s + 1] += sumTree[s];
	}
	
	if(moves)
	{ // troszeczke mniej zachłanne ^^
		tree.propagateTree();
		for(int s = 1; s <= size; ++ s)
		{
			result = (s < position)?sumTree[position] - sumTree[s - 1]:sumTree[s] - sumTree[position - 1];
			temp = tree.findBestMove(s) * (moves - 1);
			if(temp > 0)
				result += temp;

			if(result > max)
				max = result;
		}
	}

	printf("%lld\n", max > 0?max:0);
	return 0;
}
