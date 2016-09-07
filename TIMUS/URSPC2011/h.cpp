/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>

int counter,
	first, second, third,
	player[3][4004];

int main(void)
{
	scanf("%d", &first);
	for(int f = 0; f < first; ++ f)
		scanf("%d", &player[0][f]);

	scanf("%d", &second);
	for(int s = 0; s < second; ++ s)
		scanf("%d", &player[1][s]);

	scanf("%d", &third);
	for(int t = 0; t < third; ++ t)
		scanf("%d", &player[2][t]);

	for(int f = 0, s = 0, t = 0; f < first && s < second && t < third; ++ f)
	{
		while(s < second && player[1][s] < player[0][f])
			++ s;

		while(t < third && player[2][t] < player[1][s])
			++ t;

		if(f < first && s < second && t < third && player[0][f] == player[1][s] && player[1][s] == player[2][t])
			++ counter;
	}

	printf("%d\n", counter);
	return 0;
}

