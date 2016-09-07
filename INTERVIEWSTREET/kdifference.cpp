/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
#include<algorithm>

int numbers,
	difference,
	result,
	number[131072];

int main(void)
{
	scanf("%d %d", &numbers, &difference);
	for(int n = 0; n < numbers; ++ n)
		scanf("%d", &number[n]);

	std::sort(number, number + numbers);
	for(int n = 0, k = 0; n < numbers && k < numbers; ++ n)
	{
		while(k < numbers && number[k] - number[n] < difference)
			++ k;

		if(k < numbers && number[k] - number[n] == difference)
			++ result;
	}

	printf("%d\n", result);
	return 0;
}
