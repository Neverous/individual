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

std::stack<int> weaker;
std::queue<int> stronger;
int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d", &have, &opponents);
		for(int o = 0; o < opponents; ++ o)
		{
			scanf("%d", &opponent);
			if(opponent < have)
				weaker.push(opponent);

			else
				stronger.push(opponent);
			need = opponent;

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

