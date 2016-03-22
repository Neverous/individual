/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int size,
	prev = 0,
	res = 1;

inline static const int $(const int &val);

int main(void)
{
	scanf("%d", &size);
	for(int s = 0; s < size; ++ s) // FIB
		prev = $((res = $(res + prev)) - prev);

	printf("%d\n", res);
	return 0;
}

inline static const int $(const int &val)
{
	return (10 + val) % 10;
}
