/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
#define ABS(a) ((a) > 0?(a):-(a))
#define LENGTH(a, b) (ABS((a).first - (b).first) * ABS((a).first - (b).first) + ABS((a).second - (b).second) * ABS((a).second - (b).second))

using namespace std;

int tests,
	transmitters,
	unionTab[1024];
double x,
	   y;

vector<pair<double, pair<int, int> > > segment;
pair<double, double> point[1024];

double solve(void);
bool unionUnion(int &a, int &b);
int unionFind(int &a);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &transmitters);
		for(int r = 0; r < transmitters; ++ r)
		{
			scanf("%lf %lf", &x, &y);
			point[r] = make_pair(x, y);
			for(int p = r - 1; p >= 0; -- p)
				segment.push_back(make_pair(LENGTH(point[r], point[p]), make_pair(r, p)));
		}

		printf("%.6lf\n", solve());
	}

	return 0;
}

double solve(void)
{
	double result = 0;

	sort(segment.begin(), segment.end());
	for(int i = 0; i < 1024; ++ i)
		unionTab[i] = i;

	for(unsigned int s = 0; s < segment.size(); ++ s)
		if(unionUnion(segment[s].second.first, segment[s].second.second) && result < segment[s].first)
			result = segment[s].first;

	segment.clear();
	return sqrt(result);
}

bool unionUnion(int &a, int &b)
{
	int fA = unionFind(a),
		fB = unionFind(b);

	if(fA == fB)
		return false;

	if(fA < fB)
		unionTab[fB] = fA;

	else
		unionTab[fA] = fB;

	return true;
}

int unionFind(int &a)
{
	if(unionTab[a] != a)
		return unionTab[a] = unionFind(unionTab[a]);

	return unionTab[a];
}
