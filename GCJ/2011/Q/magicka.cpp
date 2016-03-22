/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	combinations,
	opposites,
	invocation;
char combine[256][256],
	 combination[4],
	 opposite[4],
	 buffer[128];
bool clear[256][256];
std::vector<char> result;

inline static const bool findOpposites(const std::vector<char> &data, const char &element);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		for(int c = 0; c < 256; ++ c)
			for(int c2 = 0; c2 < 256; ++ c2)
				combine[c][c2] = clear[c][c2] = false;

		result.clear();
		scanf("%d", &combinations);
		for(int c = 0; c < combinations; ++ c)
		{
			scanf("%s", combination);
			combine[(int)combination[0]][(int)combination[1]] = combination[2];
			combine[(int)combination[1]][(int)combination[0]] = combination[2];
		}

		scanf("%d", &opposites);
		for(int o = 0; o < opposites; ++ o)
		{
			scanf("%s", opposite);
			clear[(int)opposite[0]][(int)opposite[1]] = true;
			clear[(int)opposite[1]][(int)opposite[0]] = true;
		}

		scanf("%d %s", &invocation, buffer);
		for(int i = 0; i < invocation; ++ i)
		{
			if(result.empty())
				result.push_back(buffer[i]);

			else if(combine[(int)result.back()][(int)buffer[i]])
				*result.rbegin() = combine[(int)result.back()][(int)buffer[i]];

			else if(findOpposites(result, buffer[i]))
					result.clear();

			else
				result.push_back(buffer[i]);
		}

		printf("Case #%d: [", t + 1);
		for(unsigned int r = 0; r < result.size(); ++ r)
		{
			putchar(result[r]);
			if(r + 1 != result.size())
			{
				putchar(',');
				putchar(' ');
			}
		}

		puts("]");
	}

	return 0;
}

inline static const bool findOpposites(const std::vector<char> &data, const char &element)
{
	for(unsigned int d = 0; d < data.size(); ++ d)
		if(clear[(int)data[d]][(int)element])
			return true;

	return false;
}
