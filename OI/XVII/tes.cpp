/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<list>

using namespace std;

int numbers,
	number[1000002],
	questions,
	size,
	question[2000004],
	toAdd[1000002],
	t;
bool result[1000002];
list<int> bucket[1000002];

int main(void)
{
	scanf("%d", &numbers);
	for(int n = 0; n < numbers; ++ n)
		scanf("%d", &number[n]);

	scanf("%d", &questions);
	for(int q = 1, pos = 0; q <= questions; ++ q)
	{
		scanf("%d %d", &size, &question[pos]);
		bucket[question[pos]].push_back(pos);
		++ pos;
		for(int s = 1; s < size; ++ s)
			scanf("%d", &question[pos ++]);

		question[pos ++] = - q;
	}

	for(int n = 0; n < numbers; ++ n)
	{
		t = 0;
		for(list<int>::iterator b = bucket[number[n]].begin(); b != bucket[number[n]].end(); ++ b)
		{
			if(question[*b + 1] > 0)
				toAdd[t ++] = *b + 1;

			else
				result[- question[*b + 1]] = true;
		}

		bucket[number[n]].clear();
		for(int a = 0; a < t; ++ a)
			bucket[question[toAdd[a]]].push_back(toAdd[a]);
	}

	for(int q = 1; q <= questions; ++ q)
		printf("%s\n", result[q]?"TAK":"NIE");

	return 0;
}
