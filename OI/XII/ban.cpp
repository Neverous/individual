/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<algorithm>

int tests,
	length,
	result;
char buffer[16384];
bool possible[20000];

inline static void countCodes(char *word, const int &len);

int main(void)
{
	for(int p = 10000; p < 20000; ++ p)
		possible[p] = true;

	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %s", &length, buffer);
		countCodes(buffer, length);
	}

	for(int p = 10000; p < 20000; ++ p)
		result += possible[p];

	printf("%d\n", result);
	return 0;
}

inline static void countCodes(char *word, const int &len)
{
	std::vector<int> pos[10];
	std::vector<int>::iterator it;
	for(int d = 0; d < len; ++ d)
		pos[word[d] - '0'].push_back(d);

	for(int a = 0; a < 10; ++ a)
		for(int b = 0; b < 10; ++ b)
			for(int c = 0; c < 10; ++ c)
				for(int d = 0; d < 10; ++ d)
					if(possible[10000 + a * 1000 + b * 100 + c * 10 + d])
					{

						it = std::lower_bound(pos[a].begin(), pos[a].end(), 0);
						if(it == pos[a].end())
						{
							possible[10000 + a * 1000 + b * 100 + c * 10 + d] = false;
							continue;
						}

						it = std::lower_bound(pos[b].begin(), pos[b].end(), *it);
						if(it == pos[b].end())
						{
							possible[10000 + a * 1000 + b * 100 + c * 10 + d] = false;
							continue;
						}

						it = std::lower_bound(pos[c].begin(), pos[c].end(), *it);
						if(it == pos[c].end())
						{
							possible[10000 + a * 1000 + b * 100 + c * 10 + d] = false;
							continue;
						}

						it = std::lower_bound(pos[d].begin(), pos[d].end(), *it);
						if(it == pos[d].end())
						{
							possible[10000 + a * 1000 + b * 100 + c * 10 + d] = false;
							continue;
						}
					}

	return;
}
