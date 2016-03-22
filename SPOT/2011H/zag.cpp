/* 2011
 * Maciej Szeptuch
 * -*-*-*-*-*-*-*-*-
 */
#include<cstdio>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

const int BUFFER = 4096;
int p = BUFFER - 1;
char buffer[BUFFER];

int getInt(void)
{
	int number = 0;
	while((buffer[p] < '0' || buffer[p] > '9') && ++ p)
		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
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

	return number;
}

int tests,
	height,
	width,
	kangaroos,
	pos,
	left, right,
	top, bottom,
	best;
long long unsigned int result;
std::pair<int, int> point[1048576];

static inline const long long unsigned int $(const long long unsigned int &a){return a * (a + 1) / 2;}
static inline const int MAX(const int &a, const int &b){return a > b?a:b;}
static inline const int MIN(const int &a, const int &b){return a < b?a:b;}
static inline const int ABS(const int &a){return a<0?-a:a;}
static inline const long double dist(const std::pair<int, int> &P, const int &d, const int &C)
{
	return ABS(d * P.first + P.second - C);
}

int main(void)
{
	tests = getInt();
	for(int t = 0; t < tests; ++ t)
	{
		height = getInt(); width = getInt(); kangaroos = getInt();
		right = top = 0;
		left = bottom = 1048576;
		for(int k = 0; k < kangaroos; ++ k)
		{
			point[k].second = getInt(); point[k].first = getInt();
			left = MIN(left, point[k].first);
			right = MAX(right, point[k].first);
			bottom = MIN(bottom, point[k].second);
			top = MAX(top, point[k].second);
		}

		result = 1LLU * (right - left + 1) * (top - bottom + 1);
		/* BOTTOM-LEFT */
		best = 0;
		for(int k = 0; k < kangaroos; ++ k)
			if(dist(point[k], 1, left + bottom) < dist(point[best], 1, left + bottom))
				best = k;

		//printf("BL: (%d, %d)\n", point[best].first, point[best].second);
		result -= 1LLU * $(point[best].second - bottom) + $(point[best].first - left) + (point[best].second - bottom) * (point[best].first - left);

		/* BOTTOM-RIGHT */
		best = 0;
		for(int k = 0; k < kangaroos; ++ k)
			if(dist(point[k], -1, - right + bottom) < dist(point[best], -1, - right + bottom))
				best = k;

		//printf("BR: (%d, %d)\n", point[best].first, point[best].second);
		result -= 1LLU * $(point[best].second - bottom) + $(right - point[best].first) + (point[best].second - bottom) * (right - point[best].first);

		/* TOP-LEFT */
		best = 0;
		for(int k = 0; k < kangaroos; ++ k)
			if(dist(point[k], -1, left + top) < dist(point[best], -1, left + top))
				best = k;

		//printf("TL: (%d, %d)\n", point[best].first, point[best].second);
		result -= 1LLU * $(top - point[best].second) + $(point[best].first - left) + (top - point[best].second) * (point[best].first - left);

		/* TOP-RIGHT */
		best = 0;
		for(int k = 0; k < kangaroos; ++ k)
			if(dist(point[k], 1, right + top) < dist(point[best], 1, right + top))
				best = k;

		//printf("TR: (%d, %d)\n", point[best].first, point[best].second);
		result -= 1LLU * $(top - point[best].second) + $(right - point[best].first) + (top - point[best].second) * (right - point[best].first);

		//printf("%d %d %d %d\n", left, right, top, bottom);
		printf("%llu\n", result);
	}

	return 0;
}

