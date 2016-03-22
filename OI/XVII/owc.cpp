/* 2010
   Maciej Szeptuch
   XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<list>

int fencePoints,
    sheeps,
    modulo,
    trianT[660][660],
    leftSide[660][660];
std::pair<int, int> fence[660],
					sheep[20020];

int onTheLeft(std::pair<int, int> &A, std::pair<int, int> &B, std::pair<int, int> &C);
void preprocess(void);
int trian(int from, int to, int mod);

int main(void)
{
	scanf("%d %d %d", &fencePoints, &sheeps, &modulo);
	for(int f = 0; f < fencePoints; ++ f)
		scanf("%d %d", &fence[f].first, &fence[f].second);

	for(int s = 0; s < sheeps; ++ s)
		scanf("%d %d", &sheep[s].first, &sheep[s].second);

	preprocess();

	printf("%d\n", trian(0, fencePoints - 1, modulo));
	return 0;
}

int onTheLeft(std::pair<int, int> &A, std::pair<int, int> &B, std::pair<int, int> &C)
{
	int value = (B.first - A.first) * (C.second - A.second) - (C.first - A.first) * (B.second - A.second);
	if(value > 0)
		return 1;

	if(value < 0)
		return -1;

	return 0;
}

void preprocess(void)
{
	int temp = -1;
	for(int t = 0; t < 660; ++ t)
		for(int t2 = 0; t2 < 660; ++ t2)
			trianT[t][t2] = -1;

	for(int s = 0; s < sheeps; ++ s)
		for(int f = 0, p = 1; f < fencePoints; ++ f)
		{
			temp = onTheLeft(fence[f], fence[p], sheep[s]);
			while(temp < 0 && (p = (p + 1) % fencePoints))
				temp = onTheLeft(fence[f], fence[p], sheep[s]);

			if(temp == 0)
				trianT[f][p] = trianT[p][f] = 0;

			++ leftSide[f][p];
		}

	for(int f = 0; f < fencePoints; ++ f)
		for(int p = f + 1; p < fencePoints; ++ p)
		{
			leftSide[f][p] += leftSide[f][p - 1];
			leftSide[p][f] = sheeps - leftSide[f][p];
		}
}

int trian(int from, int to, int mod)
{
	if(from + 1 == to)
		return 1;

	if(trianT[from][to] != -1)
		return trianT[from][to];

	trianT[from][to] = 0;
	for(int s = from + 1; s < to; ++ s)
	{
		if((leftSide[s][to] - leftSide[from][to]) % 2)
			continue;

		trianT[from][to] = (trianT[from][to] + trian(s, to, mod) * trian(from, s, mod)) % mod;
	}

	return trianT[from][to];
}

