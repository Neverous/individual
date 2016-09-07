/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>

int denoms[7] = {2, 5, 10, 20, 50, 100, 200},
	ways[1048576],
	money;

int main(void)
{
	scanf("%d", &money);
	for(int m = 0; m <= money; ++ m)
		ways[m] = 1;

	for(int d = 0; d < 7; ++ d)
		for(int m = denoms[d]; m <= money; ++ m)
			ways[m] = (ways[m] + ways[m - denoms[d]]) % 1000000007;


	printf("%d\n", ways[money]);
	return 0;
}
