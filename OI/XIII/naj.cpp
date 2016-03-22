/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

class Point
{
	public:
		int x,
			y;
};

class Factory: public Point
{
	public:
		int profit;
};

int verts,
	factories,
	act,
	profit,
	result = -2000000000,
	left[606][606];

Point poly[606];
Factory factory[10010];

inline static int $(const int &v){return (verts + v) % verts;}
inline static char onTheLeft(const Point &A, const Point &B, const Point &C);
inline static void preprocess(void);

int main(void)
{
	scanf("%d", &verts);
	for(int v = 0; v < verts; ++ v)
		scanf("%d %d", &poly[v].x, &poly[v].y);

	scanf("%d", &factories);
	for(int f = 0; f < factories; ++ f)
	{
		scanf("%d %d %d", &factory[f].x, &factory[f].y, &factory[f].profit);
		profit += factory[f].profit;
	}

	preprocess();
	for(int v = 0; v < verts; ++ v)
		for(int s = 0; s < v; ++ s)
			for(int t = 0; t < s; ++ t)
			{
				act = profit - left[s][v] - left[t][s] - left[v][t];
				if(act > result)
					result = act;
			}

	printf("%d\n", result);
	return 0;
}

inline static char onTheLeft(const Point &A, const Point &B, const Point &C)
{
	int side = (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
	if(side < 0)
		return -1;

	return side?1:0;
}

inline static void preprocess(void)
{
	for(int f = 0; f < factories; ++ f)
		for(int v = 0, s = 1, side; v < verts; ++ v)
		{
			do
				side = onTheLeft(poly[v], poly[s], factory[f]);

			while(side <= 0 && v != (s = $(s + 1)));
			left[v][s] += factory[f].profit;
		}

	for(int v = 0; v < verts; ++ v)
		for(int s = 1; s < verts - 1; ++ s)
			left[v][$(v + s + 1)] += left[v][$(v + s)];

	return;
}
