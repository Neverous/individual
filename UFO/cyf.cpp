/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#define DEBUG(args...) fprintf(stderr, args)
//#define DEBUG(args...)

unsigned int count[16],
			 speedup[4][16];
unsigned int solve(unsigned int rest, unsigned int digit);

int main(void)
{
	for(unsigned int r = 0; r < 4; ++ r)
		for(unsigned int d = 0; d < 16; ++ d)
			speedup[r][d] = (1 << 20);

	for(unsigned int d = 0; d < 10; ++ d)
		scanf("%u", &count[d]);

	printf("%u\n", ((solve(0, 1) - 1) * (count[0] + 1)) % 809);
	return 0;
}

unsigned int solve(unsigned int rest, unsigned int digit)
{
	if(speedup[rest][digit] != (1 << 20))
		return speedup[rest][digit];

	if(digit == 9)
	{
		if(rest)
			return speedup[rest][digit] = 0;

		return speedup[rest][digit] = count[digit] + 1;
	}

	if(digit % 3 == 0)
		return speedup[rest][digit] = ((count[digit] + 1) * solve(rest, digit + 1)) % 809;

	return speedup[rest][digit] = ((count[digit] + 3) / 3 * solve(rest, digit + 1) + (count[digit] + 2) / 3 * solve((rest + digit) % 3, digit + 1) + (count[digit] + 1) / 3 * solve((rest + 2 * digit) % 3, digit + 1)) % 809;
}
