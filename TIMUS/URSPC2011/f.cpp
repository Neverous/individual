/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>

int first, second, third, fourth,
	result = 1048576;

inline static const int MIN(const int &a, const int &b){return a<b?a:b;}
inline static const int X(const int &a) // -1 == +3
{
	if(a == 2)
		return 2;

	return a % 2;
}

int main(void)
{
	scanf("%d %d %*d %*d %d %d", &first, &second, &third, &fourth);
	-- first;
	-- second;
	-- third; 
	-- fourth;
	for(int f = 0; f < 4; ++ f)
		for(int s = 0; s < 4; ++ s)
			for(int t = 0; t < 4; ++ t)
				for(int fh = 0; fh < 4; ++ fh)
					if((first + f) % 4 == (second + s) % 4 && (second + s) % 4 == (third + t) % 4 && (third + t) % 4 == (fourth + fh) % 4)
						result = MIN(result, X(f) + X(s) + X(t) + X(fh));

	printf("%d\n", result);
	return 0;
}

