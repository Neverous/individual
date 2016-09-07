/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>

long long int ways(int cash);
int money;

int main(void)
{
	scanf("%d", &money);
	printf("%lld\n", ways(money));
	return 0;
}

long long int ways(int cash)
{
	long long int result = 0;
	for(int dwusetki = 0; dwusetki * 200 <= cash; ++ dwusetki)
	{
		cash -= dwusetki * 200;
		for(int setki = 0; setki * 100 <= cash; ++ setki)
		{
			cash -= setki * 100;
			for(int piecdziesiatki = 0; piecdziesiatki * 50 <= cash; ++ piecdziesiatki)
			{
				cash -= piecdziesiatki * 50;
				for(int dwudziestki = 0; dwudziestki * 20 <= cash; ++ dwudziestki)
				{
					cash -= dwudziestki * 20;
					for(int dziesiatki = 0; dziesiatki * 10 <= cash; ++ dziesiatki)
					{
						cash -= dziesiatki * 10;
						for(int piatki = 0; piatki * 5 <= cash; ++ piatki)
						{
							cash -= piatki * 5;
							result = (result + cash / 2 + 1) % 1000000007;
							cash += piatki * 5;
						}
						cash += dziesiatki * 10;
					}
					cash += dwudziestki * 20;
				}
				cash += piecdziesiatki * 50;
			}
			cash += setki * 100;
		}
		cash += dwusetki * 200;
	}

	return result;
}
