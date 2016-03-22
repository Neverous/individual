/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
 
int numbers,
	number[200002],
	sum,
	result;
 
int main(void)
{
	scanf("%d %d", &numbers, &sum);
	for(int n = 0; n < numbers; ++ n)
		scanf("%d", &number[n]);
 
	std::sort(number, number + numbers);
 
	for(int i = 0, j = numbers - 1; i < j;)
	{
		if(number[i] == sum - number[j])
		{
			++ result;
			++ i;
			-- j;
			continue;
		}
 
		if(number[i] > sum - number[j])
		{
			-- j;
			continue;
		}
 
		++ i;
	}
 
	printf("%d\n", result);
}

