/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#define abs(a) ((a) < 0?-(a):(a))

int numbers,
	questions,
	number[101],
	sum,
	question;
bool result[100001];

void preprocess(void);

int main(void)
{
	scanf("%d %d", &numbers, &questions);
	for(int n = 0; n < numbers; ++ n)
	{
		scanf("%d", &number[n]);
		sum += number[n];
	}

	preprocess();

	for(int q = 0; q < questions; ++ q)
	{

		scanf("%d", &question);
		question = abs(question);
		printf("%s\n", (question>sum || !result[question])?"NIE":"TAK");
	}
	
	return 0;
}

void preprocess(void)
{
	result[sum] = true;
	for(int n = 0; n < numbers; ++ n)
		for(int p = 0; p + number[n]*2 <= sum; ++ p)
			result[p] = result[p] | result[p + number[n] * 2];
}
