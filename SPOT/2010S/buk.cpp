/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	a,
	b;

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

	while(buffer[p] == '.' || (buffer[p] >= '0' && buffer[p] <= '9'))
	{
		if(buffer[p] == '.')
		{
			++ p;
			continue;
		}

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
	tests = getInt();
	for(int t = 0; t < tests; ++ t)
	{
		a = getInt();
		b = getInt();
		printf("%s\n", (long long int)(a - 100) * (b - 100) > (long long int)10000 ? "TAK" : "NIE");
	}
	return 0;
}

