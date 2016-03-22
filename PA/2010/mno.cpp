/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int tab[1000010],
	size,
	low = 1,
	high = 1;

const int BUFFER = 4096;
int p = BUFFER - 1;
char buffer[BUFFER];

int getInt(void)
{
	int number = 0;
	while((buffer[p] < '0' || buffer[p] > '9') && ++ p)
		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}

	while(buffer[p] >= '0' && buffer[p] <= '9')
	{
		number = number * 10 + buffer[p] - '0';
		++ p;

		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}
	}

	return number;
}

int main(void)
{
	size = getInt();
	for(int s = 0; s < size && low < size && high < size; ++ s)
	{
		tab[s] = getInt();
		if(!s)
			continue;

		if(tab[s] > tab[s - 1])
		{
			++ low;
			high = 1;
		}

		else if(tab[s] < tab[s - 1])
		{
			low = 1;
			++ high;
		}

		else
		{
			++ high;
			++ low;
		}
	}

	for(int s = 0; s < size && low < size && high < size; ++ s)
	{
		if(tab[s] > tab[(size + s - 1) % size])
		{
			++ low;
			high = 1;
		}

		else if(tab[s] < tab[(size + s - 1) % size])
		{
			low = 1;
			++ high;
		}

		else
		{
			++ high;
			++ low;
		}
	}

	printf("%s\n", low == size || high == size?"TAK":"NIE");
	return 0;
}

