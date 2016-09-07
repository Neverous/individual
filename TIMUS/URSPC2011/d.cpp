/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>

short int a, b;
short int speedup[42][42][102][102];
inline static const short int MAX(const short int &a, const short int &b){return a>b?a:b;}
inline static const short int worstCase(const short int &left, const short int &right, const short int &slippersLeft, const short int &slippersRight);

int main(void)
{
	for(int i = 0; i < 42; ++ i)
		for(int j = 0; j < 42; ++ j)
			for(int k = 0; k < 102; ++ k)
				for(int l = 0; l < 102; ++ l)
					speedup[i][j][k][l] = -1;

	scanf("%hd %hd", &a, &b);
	printf("%hd\n", worstCase(40, 40, a, b));
	return 0;
}

inline static const short int worstCase(const short int &left, const short int &right, const short int &slippersLeft, const short int &slippersRight)
{
	if(speedup[left][right][slippersLeft][slippersRight] != -1)
		return speedup[left][right][slippersLeft][slippersRight];

	if(left == 0)
		return speedup[left][right][slippersLeft][slippersRight] = slippersLeft * 2 + right;

	if(right == 0)
		return speedup[left][right][slippersLeft][slippersRight] = slippersRight * 2 + left;

	return speedup[left][right][slippersLeft][slippersRight] = MAX(1 + worstCase(left - 1, right, slippersLeft - 1, slippersRight),
			   2 + worstCase(left, right - 1, slippersLeft, slippersRight - 1));
}
