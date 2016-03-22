/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<queue>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

const static int INFTY = 1 << 25;
int verts,
	edges,
	start,
	end,
	cost,
	questions,
	nth,
	V,
	shortest[2][102][102][102],
	temp[102],
	rres[102];
std::priority_queue<std::pair<int, int> > que;
std::pair<int, int> qact;

inline static void setCopy(int *result, const int *A);
inline static void setAdd(int *result, const int *A, const int *B);
inline static void setMerge(int *result, const int *A, const int *B);

int main(void)
{
	for(int s = 0; s < 102; ++ s)
		for(int e = 0; e < 102; ++ e)
			for(int k = 0; k < 102; ++ k)
				shortest[1][s][e][k] = INFTY;

	scanf("%d %d", &verts, &edges);
	V = (verts & 1) ^ 1; // V - result cell
	for(int e = 0; e < edges; ++ e)
	{
		scanf("%d %d %d", &start, &end, &cost);
		shortest[1][start - 1][end - 1][0] = cost;
	}

	for(int t = 0, N = 0, B = 1; t < verts; B = (N = (++ t) & 1) ^ 1) // N - now; B - before
	{
		setCopy(shortest[N][t][t], shortest[B][t][t]);
		setCopy(temp, shortest[N][t][t]);
		for(int k = 0; k < 100 && temp[0] + shortest[B][t][t][0] < shortest[N][t][t][100]; ++ k)
		{
			setAdd(temp, temp, shortest[B][t][t]);
			setMerge(shortest[N][t][t], shortest[N][t][t], temp);
		}

		for(int s = 0; s < verts; ++ s)
			for(int e = 0; e < verts; ++ e) if(s != t || e != t)
			{
				setCopy(shortest[N][s][e], shortest[B][s][e]);
				setAdd(temp, shortest[B][s][t], shortest[B][t][e]);
				setMerge(shortest[N][s][e], shortest[N][s][e], temp);
				setAdd(temp, temp, shortest[N][t][t]);
				setMerge(shortest[N][s][e], shortest[N][s][e], temp);
			}
	}

	scanf("%d", &questions);
	for(int q = 0; q < questions; ++ q)
	{
		scanf("%d %d %d", &start, &end, &nth);
		-- start;
		-- end;
		-- nth;

		if(shortest[V][start][end][nth] == INFTY)
			puts("-1");

		else
			printf("%d\n", shortest[V][start][end][nth]);
	}

	return 0;
}

inline static void setCopy(int *result, const int *A)
{
	for(int k = 0; k < 102; ++ k)
		result[k] = A[k];

	return;
}

inline static void setAdd(int *result, const int *A, const int *B)
{
	que = std::priority_queue<std::pair<int, int> >();
	for(int a = 0; A[a] + B[0] < INFTY; ++ a)
		que.push(std::make_pair(-A[a] - B[0], 0));

	int k = 0;
	for(; !que.empty() && k <= 100; ++ k)
	{
		qact = que.top();
		qact.first *= -1;
		que.pop();
		result[k] = qact.first;
		qact.first -= B[qact.second];
		++ qact.second;
		qact.first += B[qact.second];
		if(qact.first < INFTY)
		{
			qact.first *= -1;
			que.push(qact);
		}
	}

	while(k < 102)
		result[k ++] = INFTY;

	return;
}

inline static void setMerge(int *result, const int *A, const int *B)
{

	int k = 0;
	for(int a = 0, b = 0; k <= 100 && (A[a] != INFTY || B[b] != INFTY); ++ k)
		if(A[a] < B[b])
			rres[k] = A[a ++];

		else
			rres[k] = B[b ++];

	for(int K = 0; K < k; ++ K)
		result[K] = rres[K];

	while(k < 102)
		result[k ++] = INFTY;

	return;
}
