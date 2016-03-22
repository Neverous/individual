/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<queue>
#include<vector>
#define ITP(a) pair<int, int>((a) / 1000, (a) % 1000) // int to point
#define PTI(a,b) ((a) * 1000 + (b)) // point to int
using namespace std;
typedef pair<double, pair<double, int> > QUE_ELEM;

int size,
	x,
	y;
double tab[1001][1001],
	   tmp;
QUE_ELEM queElem;
pair<int, int> point;
priority_queue<QUE_ELEM, vector<QUE_ELEM >, greater<QUE_ELEM > > que;

double solve(void);

int main(void)
{
	scanf("%d", &size);
	scanf("%d %d", &x, &y);
	for(int h = 1; h <= size; ++ h)
		for(int w = 1; w <= size; ++ w)
			scanf("%lf", &tab[h][w]);

	printf("%.3lf\n", solve());
}

double solve(void)
{
	que.push(QUE_ELEM(0.5 / tab[x][y], pair<double, int>(0.5, PTI(x, y - 1))));
	que.push(QUE_ELEM(0.5 / tab[x][y], pair<double, int>(0.5, PTI(x, y + 1))));
	que.push(QUE_ELEM(0.5 / tab[x][y], pair<double, int>(0.5, PTI(x + 1, y))));
	que.push(QUE_ELEM(0.5 / tab[x][y], pair<double, int>(0.5, PTI(x - 1, y))));

	while(!que.empty())
	{
		queElem = que.top();
		point = ITP(queElem.second.second);
		que.pop();
		if(!point.first || !point.second || point.first > size || point.second > size)
			return queElem.first;
		
		tmp = (queElem.second.first + 1) / tab[point.first][point.second];
		if(tmp < queElem.first)
			tmp = queElem.first;

		que.push(QUE_ELEM(tmp, pair<double, int>(queElem.second.first + 1, PTI(point.first, point.second - 1))));
		que.push(QUE_ELEM(tmp, pair<double, int>(queElem.second.first + 1, PTI(point.first, point.second + 1))));
		que.push(QUE_ELEM(tmp, pair<double, int>(queElem.second.first + 1, PTI(point.first + 1, point.second))));
		que.push(QUE_ELEM(tmp, pair<double, int>(queElem.second.first + 1, PTI(point.first - 1, point.second))));
	}
	return 0.0;
}
