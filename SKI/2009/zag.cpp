#include<cstdio>

int tests,
	numbers;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &numbers);
		while(numbers -- >= 0)
			printf("0/1 ");

		puts("");
	}

	return 0;
}
