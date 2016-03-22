/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

const int BUFFER = 4096;
int p = BUFFER - 1;
char buffer[BUFFER];

int getInt(void)
{
	bool over = true;
	int number = 0;
	while((buffer[p] < '0' || buffer[p] > '9'))
	{
		if(buffer[p] == '-')
			over = false;

		++ p;
		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}
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

	return over?number:-number;
}

int tests,
	numbers,
	num,
	act,
	res;

int main(void)
{
	tests = getInt();
	//scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		res = act = 0;
		numbers = getInt();
		//scanf("%d", &numbers);
		for(int n = 0; n < numbers; ++ n)
		{
			//scanf("%d", &num);
			num = getInt();
			if(num == -1 && act == 0)
			{
				++ res;
				continue;
			}

			act += num;
		}

		printf("%d\n", res + act);
	}

	return 0;
}

