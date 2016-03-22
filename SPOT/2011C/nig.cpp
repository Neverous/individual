/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 * ----------
 *  Nie znosze geometrii...
 */
#include<cstdio>
#include<set>
#include<algorithm>
//#define DEBUG(args...) fprlong long intf(stderr, args)
#define DEBUG(args...)

const int BUFFER = 4096;
int p = BUFFER - 1;
char buffer[BUFFER];
 
long long int getInt(void)
{
	bool over = true;
	long long int number = 0;
	while((buffer[p] < '0' || buffer[p] > '9'))
	{
		if(buffer[p] == '-')
			over = false;
 
		++ p;
		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}
	}
 
	while(buffer[p] >= '0' && buffer[p] <= '9')
	{
		number = number * 10 + buffer[p] - '0';
		++ p;
 
		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}
	}
 
	return over?number:-number;
}

long long int tests,
	 segments,
	 start,
	 end,
	 a, b,
	 time;
std::pair<std::pair<long long int, long long int>, std::pair<long long int, long long int> > segment[131072];
std::pair<std::pair<long long int, long long int>, long long int> point[262144];
std::pair<long long int, long long int> dSegment[131072];

class segCompare
{
	public:
		bool operator()(const long long int &A, const long long int &B);
};

std::set<long long int, segCompare> que;
std::set<long long int, segCompare>::iterator temp,
	temp2;

bool segmentsIntersect(const long long int &A, const long long int &B);
bool intersect(const std::pair<long long int, long long int> &A, const std::pair<long long int, long long int> &B, const std::pair<long long int, long long int> &C);
long long int determinant(const std::pair<long long int, long long int> &A, const std::pair<long long int, long long int> &B, const std::pair<long long int, long long int> &C);
long long int MAX(const long long int &A, const long long int &B){return A>B?A:B;}
long long int MIN(const long long int &A, const long long int &B){return A<B?A:B;}
long long int SGN(const long long int &A){return A==0?0:A<0?-1:1;}

inline bool solve(void);

int main(void)
{
	tests = getInt();
	for(long long int t = 0; t < tests; ++ t)
	{
		segments = getInt();
		for(long long int s = 1; s <= segments; ++ s)
		{
			start = getInt();
			end = getInt();
			a = getInt();
			b = getInt();
			segment[s] = std::make_pair(std::make_pair(start, start * a + b), std::make_pair(end, end * a + b));
			dSegment[s] = std::make_pair(a, b);
			point[(s - 1) * 2] = std::make_pair(std::make_pair(start, start * a + b), -s);
			point[(s - 1) * 2 + 1] = std::make_pair(std::make_pair(end, end * a + b), s);
		}

		std::sort(point, point + segments * 2);
		puts(solve()?"TAK":"NIE");
	}

	return 0;
}

inline bool solve(void)
{
	que.clear();
	for(long long int p = 0; p < segments * 2; ++ p)
	{
		time = point[p].first.first;
		if(point[p].second < 0)
		{
			que.insert(-point[p].second);
			temp = que.find(-point[p].second);
			if(temp != que.end())
				++ temp;

			if(temp != que.end() && *temp != -point[p].second && segmentsIntersect(*temp, -point[p].second))
				return true;

			if(temp != que.begin())
				-- temp;

			if(temp != que.begin())
				-- temp;

			if(temp != que.end() && *temp != -point[p].second && segmentsIntersect(*temp, -point[p].second))
				return true;
		}

		else
		{
			temp = que.find(point[p].second);
			temp2 = temp;
			if(temp != que.end())
				++ temp;

			if(temp2 != que.begin())
				-- temp2;

			if(temp != que.end() && temp2 != que.end() && *temp != *temp2 && segmentsIntersect(*temp, *temp2))
				return true;

			que.erase(point[p].second);
		}
	}

	return false;
}

bool segCompare::operator()(const long long int &A, const long long int &B)
{
	return time * dSegment[A].first + dSegment[A].second < time * dSegment[B].first + dSegment[B].second;
}

bool segmentsIntersect(const long long int &A, const long long int &B)
{
	long long int d1 = determinant(segment[B].first, segment[B].second, segment[A].first),
		 d2 = determinant(segment[B].first, segment[B].second, segment[A].second),
		 d3 = determinant(segment[A].first, segment[A].second, segment[B].first),
		 d4 = determinant(segment[A].first, segment[A].second, segment[B].second);

	if(d1 * d2 < 0 && d3 * d4 < 0)
		return true;

	if(!d1 && intersect(segment[B].first, segment[B].second, segment[A].first))
		return true;

	if(!d2 && intersect(segment[B].first, segment[B].second, segment[A].second))
		return true;

	if(!d3 && intersect(segment[A].first, segment[A].second, segment[B].first))
		return true;

	if(!d4 && intersect(segment[A].first, segment[A].second, segment[B].second))
		return true;

	return false;
}

bool intersect(const std::pair<long long int, long long int> &A, const std::pair<long long int, long long int> &B, const std::pair<long long int, long long int> &C)
{
	return MIN(A.first, B.first) <= C.first &&
		MAX(A.first, B.first) >= C.first &&
		MIN(A.second, B.second) <= C.second &&
		MAX(A.second, B.second) >= C.second;
}

long long int determinant(const std::pair<long long int, long long int> &A, const std::pair<long long int, long long int> &B, const std::pair<long long int, long long int> &C)
{
	return SGN(A.first * B.second + A.second * C.first + B.first * C.second - B.second * C.first - A.first * C.second - A.second * B.first);
}


