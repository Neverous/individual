/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
#define DEBUG(args...) fprintf(stderr, args)
//#define DEBUG(args...)

using namespace std;

int cost[10][10] = {
	{9, 4, 3, 3, 4, 3, 2, 4, 1, 2},
	{9, 9, 5, 3, 2, 5, 6, 1, 5, 4},
	{9, 9, 9, 2, 5, 4, 3, 4, 2, 3},
	{9, 9, 9, 9, 3, 2, 3, 2, 2, 1},
	{9, 9, 9, 9, 9, 3, 4, 3, 3, 2},
	{9, 9, 9, 9, 9, 9, 1, 4, 2, 1},
	{9, 9, 9, 9, 9, 9, 9, 5, 1, 2},
	{9, 9, 9, 9, 9, 9, 9, 9, 4, 3},
	{9, 9, 9, 9, 9, 9, 9, 9, 9, 1},
	{9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
};

int best[10][10],
	global,
	tests,
	operations,
	digits,
	digit[10];
char buffer[100010];

bool globalCompare(const int &A, const int &B);
void makeBiggest(void);
inline int MIN(int A, int B);

int main(void)
{
	for(int n = 0; n < 10; ++ n)
	{
		for(int f = 0; f < 10; ++ f)
			best[n][f] = f;

		global = n;
		sort(best[n], best[n] + 10, globalCompare);
	}

	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		for(int d = 0; d < 10; ++ d)
			digit[d] = 0;

		scanf("%d %d %s", &operations, &digits, buffer);
		for(int d = 0; d < digits; ++ d)
			++ digit[buffer[d] - '0'];

		makeBiggest();
		for(int d = 9; d >= 0; -- d)
			while(digit[d] --)
				putchar(d + '0');

		puts("");
	}

	return 0;
}

bool globalCompare(const int &A, const int &B)
{
	return cost[A][global] < cost[B][global];
}

void makeBiggest(void)
{
	int temp;
	for(int d = 9; d > 0 && operations; -- d)
		for(int c = 0; best[d][c] < d && operations && cost[best[d][c]][d] <= operations; ++ c)
		{
			temp = digit[best[d][c]];
			digit[d] += MIN(operations / cost[best[d][c]][d], temp);
			digit[best[d][c]] -= MIN(operations / cost[best[d][c]][d], temp);
			operations -= MIN(operations / cost[best[d][c]][d], temp) * cost[best[d][c]][d];
		}

	return;
}

inline int MIN(int A, int B)
{
	return A < B?A:B;
}
