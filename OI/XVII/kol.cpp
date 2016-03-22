/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<cstdlib>
#include<vector>

using namespace std;

int train,
	trains,
	stackA[100001],
	a,
	stackB[100001],
	b,
	position = 1;
bool answer[100001];
vector<bool> possible;


int main(void)
{
	srand(260127666);
	scanf("%d", &trains);
	for(int t = 0; t < trains; ++ t)
	{
		scanf("%d", &train);
		if(a && train == stackA[a - 1] - 1) // jest o jeden mniejsze od pierwszego
		{
			stackA[a ++] = train;
			answer[t] = false;
		}

		else if(b && train == stackB[b - 1] - 1) // jest o jeden mninejsze od drugiego
		{
			stackB[b ++] = train;
			answer[t] = true;
		}

		else
		{
			possible.clear();
			if(!b) // b jest puste
				possible.push_back(true);

			if(!a) // a jest puste
				possible.push_back(false);

			if(b && train < stackB[b - 1]) // jestem mniejszy od B
				possible.push_back(true);

			if(a && train < stackA[a - 1]) // jestem mniejszy od A
				possible.push_back(false);

			if(!possible.size())
			{
				printf("NIE\n");
				return 0;
			}

			if(possible[rand() % possible.size()])
			{
				stackB[b ++] = train;
				answer[t] = true;
			}

			else
			{
				stackA[a ++] = train;
				answer[t] = false;
			}
		}

		while((a && position == stackA[a - 1]) || (b && position == stackB[b - 1]))
		{
			if(a && position == stackA[a - 1])
				-- a;

			if(b && position == stackB[b - 1])
				-- b;

			position ++;
		}
	}

	while((a && position == stackA[a - 1]) || (b && position == stackB[b - 1]))
	{
		if(a && position == stackA[a - 1])
			-- a;

		if(b && position == stackB[b - 1])
			-- b;

		position ++;
	}

	if(a || b)
	{
		printf("NIE\n");
		return 0;
	}

	printf("TAK\n");
	for(int t = 0; t < trains; ++ t)
		printf("%d ", answer[t] + 1);

	puts("");
	return 0;
}
