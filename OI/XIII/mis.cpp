/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

const int MOD = 1000000;
int count[4],
	c[4],
	dp[2][40][40][40][4][4],
	pre[3][3][3][3][4][4],
	result;

inline static bool GOOD(const int &x, const int &y, const int &z);
inline static int DP(const int &f, const int &s, const int &t, const int &e, const int &b, const int &l);

int main(void)
{
	scanf("%d %d %d %d", &count[0], &count[1], &count[2], &count[3]);
	if(count[0] + count[1] + count[2] + count[3] == 1)
	{
		puts("1");
		return 0;
	}

	/* DP */
	for(int b = 0; b < 4; ++ b)
		for(int l = 0; l < 4; ++ l)
			if(count[l] && count[b] && (l != b || count[l] > 1))
				pre[(l == 0) + (b == 0)][(l == 1) + (b == 1)][(l == 2) + (b == 2)][(l == 3) + (b == 3)][b][l] = 1;

	for(c[0] = 0; c[0] <= count[0]; ++ c[0])
		for(c[1] = 0; c[1] <= count[1]; ++ c[1])
			for(c[2] = 0; c[2] <= count[2]; ++ c[2])
				for(c[3] = 0; c[3] <= count[3]; ++ c[3])
					for(int b = 0; b < 4; ++ b)
						for(int l = 0; l < 4; ++ l)
						{
							dp[c[0] & 1][c[1]][c[2]][c[3]][b][l] = 0;
							for(int p = 0; p < 4; ++ p)
								if(GOOD(p, b, l) && (l != b || p != l || b != p) && c[l] && c[b] && c[p] && c[0] + c[1] + c[2] + c[3] > 2 && (l != b || c[l] > 1) && (l != p || c[l] > 1) && (b != p || c[b] > 1))
								{
									dp[c[0] & 1][c[1]][c[2]][c[3]][b][l] += DP(c[0] - (l == 0), c[1] - (l == 1), c[2] - (l == 2), c[3] - (l == 3), p, b);
									if(dp[c[0] & 1][c[1]][c[2]][c[3]][b][l] >= MOD)
										dp[c[0] & 1][c[1]][c[2]][c[3]][b][l] %= MOD;
								}
						}

	for(int b = 0; b < 4; ++ b)
		for(int l = 0; l < 4; ++ l)
			result += DP(count[0], count[1], count[2], count[3], b, l);

	printf("%d\n", result % MOD);

	return 0;
}

inline static bool GOOD(const int &x, const int &y, const int &z)
{
	if(x < 2 && y < 2 && z < 2)
		return false;

	if(x > 1 && y > 1 && z > 1)
		return false;

	if((x & 1) == (y & 1) && (y & 1) == (z & 1))
		return false;

	return true;
}

inline static int DP(const int &f, const int &s, const int &t, const int &e, const int &b, const int &l)
{
	if(f + s + t + e < 3)
		return pre[f][s][t][e][b][l];

	return dp[f & 1][s][t][e][b][l];
}
