/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<queue>
#include<stack>

int tests,
	have,
	opponents,
	opponent,
	need,
	result = 1;

const int BUFFER = 4096;
int p = BUFFER - 1;
char buffer[BUFFER];

std::stack<int> weaker;
std::queue<int> stronger;

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
	tests = getInt();
	for(int t = 0; t < tests; ++ t)
	{
		have = getInt();
		opponents = getInt();
		for(int o = 0; o < opponents; ++ o)
		{
			opponent = getInt();
			if(opponent < have)
				weaker.push(opponent);

			else
				stronger.push(opponent);

			need = opponent;
			opponent = 0;
		}

		while(have <= need && !weaker.empty())
		{
			have += weaker.top();
			weaker.pop();
			++ result;

			while(!stronger.empty() && stronger.front() < have)
			{
				weaker.push(stronger.front());
				stronger.pop();
			}
		}

		if(have > need)
			printf("%d\n", result);

		else
			printf("NIE\n");

		result = 1;
		weaker = std::stack<int>();
		stronger = std::queue<int>();
	}

	return 0;
}

