/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tab[1000010],
	size,
	steps;
long long int pref,
	 result,
	 best;

const int BUFFER = 4096;
int p = BUFFER - 1;
char buffer[BUFFER];

int getInt(void);
inline int min(int a, int b)
{
	return a<b?a:b;
}

int main(void)
{
	size = getInt();
	steps = getInt();
	for(int s = 0; s < min(steps + 1, size); ++ s)
	{
		pref += tab[s] = getInt();
		if(!s)
			continue;

		result = pref + (long long int)(tab[s] + tab[s - 1]) * ((steps - s) / 2);
		if((steps - s) % 2)
			result += tab[s - 1];

		if(result > best)
			best = result;
	}

	if(size == 1)
	{
		printf("%lld\n", (long long int)tab[0] * (steps / 2 + 1));
		return 0;
	}

	printf("%lld\n", best);
	return 0;
}

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
