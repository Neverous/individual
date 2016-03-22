#include<cstdio>

int tests,
	number;
	int a = 1,
		 b = 1,
		 c = 0;

inline static int fibonacci(int which);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &number);
		printf("%d\n", fibonacci(number));
	}

	return 0;
}

inline static int fibonacci(int which)
{
	a = b = !(c = 0);
	for(int w = 2; w < which; ++ w)
	{
		c = a + b;
		a = b;
		b = c;
	}

	return b;
}

