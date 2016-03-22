/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tourists,
	tourist[100010],
	best,
	temp;

int main(void)
{
	scanf("%d", &tourists);
	for(int t = 0; t < tourists; ++ t)
		scanf("%d", &tourist[t]);

	if(tourists == 1)
	{
		printf("%d\n", tourist[0]);
		return 0;
	}

	best = 0;
	for(int i = 1; 2 * i <= tourists; ++ i)
		if(2 * tourist[1] - tourist[0] < tourist[tourists - 2 * i])
			best = i;

	temp = (tourists - best - 2) * tourist[0] + (2 * best + 1) * tourist[1];
	for(int i = 2; i <= tourists - 1 - 2 * best; ++ i)
		temp += tourist[i];

	for(int i = 0; i <= best - 1; ++ i)
		temp += tourist[tourists - 1 - 2 * i];

	printf("%d\n", temp);
	return 0;
}

