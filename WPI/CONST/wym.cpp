#include<cstdio>

int tests,
	power,
	number,
	modulo;

char buffer[1000001];

int fastPower(int a, int power)
{
	if(power == 0)
		return 1;

	if(power%2)
		return ((long long unsigned)a * fastPower(a, power-1))%modulo;

	int half = fastPower(a, power/2);
	return ((long long unsigned)half*half)%modulo;
}


int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		power = 0;
		scanf("%d %s %d", &number, buffer, &modulo);
		if(modulo > 1)
			for(int b = 0; buffer[b]; ++b)
			{
				power = power * 10 + buffer[b] - '0';
				power %= modulo - 1;
			}

		else
			power = 0;
		
		printf("%d\n", fastPower(number, power));
	}
}

