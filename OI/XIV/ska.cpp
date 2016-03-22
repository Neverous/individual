/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

struct Rock
{
	unsigned int x, y,
				 weight;
	bool moved;
};

inline static const unsigned int MIN(const unsigned int &a, const unsigned int &b){return a<b?a:b;}
inline static const unsigned int MAX(const unsigned int &a, const unsigned int &b){return a>b?a:b;}
inline static const bool BETWEEN(const unsigned int &val, const unsigned int &min, const unsigned int &max){return min <= val && val <= max;}
inline static const unsigned int count(const unsigned int &xmin, const unsigned int &xmax, const unsigned int &ymin, const unsigned int &ymax);

unsigned int rocks,
			 weight, ans,
			 x, y,
			 temp,
			 hmin = 1000000000, hmax,
			 vmin = 1000000000, vmax;

Rock rock[1048576];

int main(void)
{
	scanf("%u", &rocks);
	for(unsigned int r = 0; r < rocks; ++ r)
	{
		scanf("%u %u %u", &rock[r].x, &rock[r].y, &rock[r].weight);
		x = rock[r].x;
		y = rock[r].y;
		if(x > y)
		{
			std::swap(x, y);
			rock[r].moved = true;
		}

		vmin = MIN(vmin, x);
		vmax = MAX(vmax, x);

		hmin = MIN(hmin, y);
		hmax = MAX(hmax, y);
	}

	printf("%u", 2 * (vmax + hmax - vmin - hmin));
	weight = count(vmin, vmax, hmin, hmax); ans = 0;
	if((temp = count(hmin, hmax, vmin, vmax)) < weight)
	{
		weight = temp;
		ans = 1;
	}

	if((temp = count(hmin, vmax, vmin, hmax)) < weight)
	{
		weight = temp;
		ans = 2;
	}

	if((temp = count(vmin, hmax, hmin, vmax)) < weight)
	{
		weight = temp;
		ans = 3;
	}

	if(!ans)
		count(vmin, vmax, hmin, hmax);

	else if(ans == 1)
		count(hmin, hmax, vmin, vmax);

	else if(ans == 2)
		count(hmin, vmax, vmin, hmax);

	else
		count(vmin, hmax, hmin, vmax);

	printf(" %u\n", weight);
	for(unsigned int r = 0; r < rocks; ++ r)
		putchar('0' + rock[r].moved);

	puts("");
	return 0;
}

inline static const unsigned int count(const unsigned int &xmin, const unsigned int &xmax, const unsigned int &ymin, const unsigned int &ymax)
{
	unsigned int result = 0;
	for(unsigned int r = 0; r < rocks; ++ r)
	{
		if(BETWEEN(rock[r].x, xmin, xmax) && BETWEEN(rock[r].y, ymin, ymax))
			rock[r].moved = false;

		else if(BETWEEN(rock[r].y, xmin, xmax) && BETWEEN(rock[r].x, ymin, ymax))
		{
			rock[r].moved = true;
			result += rock[r].weight;
		}

		else
			return (1U << 31); // IMPOSSIBLE
	}

	return result;
}
