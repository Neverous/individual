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
			 divs,
			 q = 1,
			 qStart[200020],
			 qEnd[200020],
			 act,
			 qMid;
long double qDist[200020];
std::vector<unsigned int> toSort;
std::pair<long double, long double> point[100010],
									sPoint[100010],
									qPoint[200020];
std::priority_queue<std::pair<long double, unsigned int> > que;

inline static std::pair<std::pair<long double, long double>, long double> findCircle(unsigned int s, unsigned int e);
inline static std::pair<std::pair<long double, long double>, long double> minCircle(unsigned int s, unsigned int e, int q1 = -1, int q2 = -1, int q3 = -1);
inline static bool inCircle(std::pair<std::pair<long double, long double>, long double> center, std::pair<long double, long double> Point);

inline static long double dist(std::pair<long double, long double> &A, std::pair<long double, long double> &B);
inline static long double MAX(long double a, long double b);
inline static bool compare(const unsigned int &A, const unsigned int &B);

int main(void)
{
	srand(42);
	scanf("%u %u", &points, &divs);
	for(unsigned int p = 0; p < points; ++ p)
		scanf("%Lf %Lf", &point[p].first, &point[p].second);

	qPoint[0] = findCircle(0, points).first;
	//printf("Byl sobie %.15Lf %.15Lf\n", qPoint[0].first, qPoint[0].second);
	qStart[0] = 0;
	qEnd[0] = points;
	for(unsigned int p = 0; p < points; ++ p)
		qDist[0] = MAX(qDist[0], dist(qPoint[0], point[p]));

	que.push(std::make_pair(qDist[0], 0));
	while(que.size() != divs && que.top().first)
	{
		act = que.top().second;
		que.pop();
		//printf("byl sobie %.15Lf %.15Lf\n", qPoint[act].first, qPoint[act].second);
		qMid = (qStart[act] + qEnd[act] + 1) / 2;

		qPoint[q] = findCircle(qStart[act], qMid).first;
		qStart[q] = qStart[act];
		qEnd[q] = qMid;
		for(unsigned int p = qStart[act]; p < qMid; ++ p)
			qDist[q] = MAX(qDist[q], dist(qPoint[q], point[p]));

		//printf("wrzucam %.15Lf %.15Lf => %.15Lf\n", qPoint[q].first, qPoint[q].second, qDist[q]);
		que.push(std::make_pair(qDist[q], q));
		++ q;

		qPoint[q] = findCircle(qMid, qEnd[act]).first;
		qStart[q] = qMid;
		qEnd[q] = qEnd[act];
		for(unsigned int p = qMid; p < qEnd[act]; ++ p)
			qDist[q] = MAX(qDist[q], dist(qPoint[q], point[p]));

		//printf("wrzucam %.15Lf %.15Lf => %.15Lf\n", qPoint[q].first, qPoint[q].second, qDist[q]);
		que.push(std::make_pair(qDist[q], q));
		++ q;
	}

	printf("%.15Lf\n%u\n", que.top().first, (unsigned int)que.size());
	while(!que.empty())
	{
		toSort.push_back(que.top().second);
		que.pop();
	}

	std::sort(toSort.begin(), toSort.end(), compare);
	for(unsigned int s = 0; s < toSort.size(); ++ s)
		printf("%.15Lf %.15Lf\n", qPoint[toSort[s]].first, qPoint[toSort[s]].second);

	return 0;
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

inline static bool compare(const unsigned int &A, const unsigned int &B)
{
	return qStart[A] < qStart[B];
}
