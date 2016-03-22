/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>

unsigned int points,
			 divs;
long double best = -1.0;
std::pair<long double, long double> point[100010],
									sPoint[100010],
									qPoint[100010];

inline static std::pair<std::pair<long double, long double>, long double> findCircle(unsigned int s, unsigned int e);
inline static std::pair<std::pair<long double, long double>, long double> minCircle(unsigned int s, unsigned int e, int q1 = -1, int q2 = -1, int q3 = -1);
inline static bool inCircle(std::pair<std::pair<long double, long double>, long double> center, std::pair<long double, long double> Point);

inline static long double dist(std::pair<long double, long double> &A, std::pair<long double, long double> &B);
inline static long double MAX(long double a, long double b);
inline static long double MIN(long double a, long double b);
inline static long double brutal(unsigned int q, unsigned int s);

int main(void)
{
	srand(42);
	scanf("%u %u", &points, &divs);
	for(unsigned int p = 0; p < points; ++ p)
		scanf("%Lf %Lf", &point[p].first, &point[p].second);

	best = brutal(0, 0);
	brutal(0, 0);
	printf("%.15Lf\n", best);
	printf("%u\n", divs);
	for(unsigned int d = 0; d < divs; ++ d)
		printf("%.15Lf %.15Lf\n", qPoint[d].first, qPoint[d].second);

	return 0;
}

inline static long double MIN(long double a, long double b)
{
	return a<b?a:b;
}

inline static long double MAX(long double a, long double b)
{
	return a>b?a:b;
}

inline static long double dist(std::pair<long double, long double> &A, std::pair<long double, long double> &B)
{
	return sqrt((long double)(A.first - B.first) * (A.first - B.first) + (A.second - B.second) * (A.second - B.second));
}

inline static std::pair<std::pair<long double, long double>, long double> findCircle(unsigned int s, unsigned int e)
{
	for(unsigned int p = s; p < e; ++ p)
		sPoint[p] = point[p];

	return minCircle(s, e);
}

inline static std::pair<std::pair<long double, long double>, long double> minCircle(unsigned int s, unsigned int e, int q1, int q2, int q3)
{
	std::pair<std::pair<long double, long double>, long double> res;
	std::random_shuffle(sPoint + s, sPoint + e);
	if(q3 != -1) // GOT A TRIPLE
	{
		res.first.first = ((sPoint[q2].first * sPoint[q2].first * sPoint[q3].second + sPoint[q2].second * sPoint[q2].second * sPoint[q3].second - sPoint[q1].first * sPoint[q1].first * sPoint[q3].second + sPoint[q1].first * sPoint[q1].first * sPoint[q2].second - sPoint[q1].second * sPoint[q1].second * sPoint[q3].second + sPoint[q1].second * sPoint[q1].second * sPoint[q2].second + sPoint[q1].second * sPoint[q3].first * sPoint[q3].first + sPoint[q1].second * sPoint[q3].second * sPoint[q3].second - sPoint[q1].second * sPoint[q2].first * sPoint[q2].first - sPoint[q1].second * sPoint[q2].second * sPoint[q2].second - sPoint[q2].second * sPoint[q3].first * sPoint[q3].first - sPoint[q2].second * sPoint[q3].second * sPoint[q3].second) / (sPoint[q1].second * sPoint[q3].first - sPoint[q1].second * sPoint[q2].first - sPoint[q2].second * sPoint[q3].first - sPoint[q3].second * sPoint[q1].first + sPoint[q3].second * sPoint[q2].first + sPoint[q2].second * sPoint[q1].first)) / 2;
		res.first.second = ((-sPoint[q1].first * sPoint[q3].first * sPoint[q3].first - sPoint[q1].first * sPoint[q3].second * sPoint[q3].second + sPoint[q1].first * sPoint[q2].first * sPoint[q2].first + sPoint[q1].first * sPoint[q2].second * sPoint[q2].second + sPoint[q2].first * sPoint[q3].first * sPoint[q3].first + sPoint[q2].first * sPoint[q3].second * sPoint[q3].second - sPoint[q2].first * sPoint[q2].first * sPoint[q3].first - sPoint[q2].second * sPoint[q2].second * sPoint[q3].first + sPoint[q1].first * sPoint[q1].first * sPoint[q3].first - sPoint[q1].first * sPoint[q1].first * sPoint[q2].first + sPoint[q1].second * sPoint[q1].second * sPoint[q3].first - sPoint[q1].second * sPoint[q1].second * sPoint[q2].first) / (sPoint[q1].second * sPoint[q3].first - sPoint[q1].second * sPoint[q2].first - sPoint[q2].second * sPoint[q3].first - sPoint[q3].second * sPoint[q1].first + sPoint[q3].second * sPoint[q2].first + sPoint[q2].second * sPoint[q1].first)) / 2;
		res.second = dist(res.first, sPoint[q2]);

		return res;
	}

	else if(q2 != -1)
	{
		res.first = std::make_pair(
			(sPoint[q1].first + sPoint[q2].first) / 2,
			(sPoint[q1].second + sPoint[q2].second) / 2
		);

		res.second = dist(res.first, sPoint[q1]);
	}

	else if(q1 != -1)
	{
		res.first = std::make_pair(
			(sPoint[q1].first + sPoint[s].first) / 2,
			(sPoint[q1].second + sPoint[s].second) / 2
		);

		res.second = dist(res.first, sPoint[q1]);
		if(e == s + 1)
			return res;
	}

	else if(e == s + 1)
	{
		res.first = sPoint[s];
		res.second = 0;
		return res;
	}

	else
	{
		res.first = std::make_pair(
			(sPoint[s].first + sPoint[s + 1].first) / 2,
			(sPoint[s].second + sPoint[s + 1].second) / 2
			);

		res.second = dist(res.first, sPoint[s]);
	}

	for(unsigned int p = s; p < e; ++ p)
	{
		if(inCircle(res, sPoint[p]))
			continue;

		if(q2 != -1)
			res = minCircle(s, p, q1, q2, p);

		else if(q1 != -1)
			res = minCircle(s, p, q1, p);

		else
			res = minCircle(s, p, p);
	}

	return res;
}

inline static bool inCircle(std::pair<std::pair<long double, long double>, long double> center, std::pair<long double, long double> Point)
{
	return (center.first.first - Point.first) * (center.first.first - Point.first) + (center.first.second - Point.second) * (center.first.second - Point.second) <= center.second * center.second;
}

inline static long double brutal(unsigned int q, unsigned int s)
{
	long double res = (1 << 30),
				act = 0;
	std::pair<long double, long double> P;
	if(q + 1 == divs || s + 1 == points)
	{
		res = 0;
		P = findCircle(s, points).first;
		qPoint[q] = P;
		for(unsigned int p = s; p < points; ++ p)
			res = MAX(res, dist(P, point[p]));

		return res;
	}

	for(unsigned int e = s + 1; e < points; ++ e)
	{
		act = 0;
		P = findCircle(s, e).first;
		qPoint[q] = P;
		for(unsigned int p = s; p < e; ++ p)
			act = MAX(act, dist(P, point[p]));

		act = MAX(act, brutal(q + 1, e));
		if(act == best)
			return act;

		res = MIN(res, act);
	}

	return res;
}
