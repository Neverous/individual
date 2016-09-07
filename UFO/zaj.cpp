/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)
#define MOD 1000000007

unsigned int pascal[16][16],
			 hunger,
			 fields;
std::pair<unsigned int, std::pair<unsigned int, unsigned int> > data[16];

void fillTriangle(void);

long long unsigned int solve(unsigned int act, unsigned int needs);
inline static unsigned int MIN(unsigned int a, unsigned int b);

int main(void)
{
	fillTriangle();
	scanf("%u %u", &hunger, &fields);
	hunger += 2;

	for(unsigned int f = 0; f < fields; ++ f)
	{
		scanf("%u %u", &data[f].second.first, &data[f].second.second);
		data[f].first = MIN(data[f].second.first, hunger / data[f].second.second);
	}

	std::sort(data, data + fields);
	printf("%llu\n", solve(0, hunger));
	return 0;
}

void fillTriangle(void)
{
	pascal[1][1] = 1;
	for(unsigned int h = 2; h < 12; ++ h)
		for(unsigned int w = 1; w <= h; ++ w)
			pascal[h][w] = pascal[h - 1][w] + pascal[h - 1][w - 1];
}

long long unsigned int solve(unsigned int act, unsigned int needs)
{
	long long unsigned int result = 0;
	if(act == fields - 1)
	{
		if(needs % data[act].second.second || needs / data[act].second.second > data[act].first)
			return 0;

		//printf("OSTATNI => %u\n", pascal[data[act].second.first + 1][needs / data[act].second.second + 1]);
		return pascal[data[act].second.first + 1][needs / data[act].second.second + 1];
	}

	for(unsigned int p = 0; p <= data[act].first; ++ p)
	{
		//printf("BADAM %u z %u i %u => %u\n", act, needs, p, pascal[data[act].second.first + 1][p + 1]);
		result = (result + pascal[data[act].second.first + 1][p + 1] * solve(act + 1, needs - p * data[act].second.second)) % MOD;
	}

	return result;
}

inline static unsigned int MIN(unsigned int a, unsigned int b)
{
	return a<b?a:b;
}
