/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<string>
#define MAXCHECKS 1000000
#define MAXDEPTH 100000
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int tests,
			 buildingsA,
			 housesA,
			 buildingsB,
			 housesB,
			 pathA[1024][16],
			 pathB[1024][16],
			 paths,
			 checks;
std::string result;

inline static std::string solve(int a, int b, int depth);

int main(void)
{
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		checks = MAXCHECKS;
		scanf("%u %u %u %u %u", &buildingsA, &housesA, &buildingsB, &housesB, &paths);
		for(unsigned int b = 0; b < buildingsA; ++ b)
			for(unsigned int p = 0; p < paths; ++ p)
				scanf("%u", &pathA[b][p]);

		for(unsigned int b = 0; b < buildingsB; ++ b)
			for(unsigned int p = 0; p < paths; ++ p)
				scanf("%u", &pathB[b][p]);

		result = solve(0, 0, MAXDEPTH);
		if(!result.empty())
			printf("%d %s\n", (int)result.length(), result.c_str());

		else
			printf("0\n");
	}

	return 0;
}

inline static std::string solve(int a, int b, int depth)
{
	std::string res = "",
				tmp;
	if(!checks || !depth)
		return res;

	-- checks;
	for(unsigned int p = 0; p < paths; ++ p)
		if(pathA[a][p] >= 1 && pathA[a][p] <= housesA && (pathB[b][p] == 0 || pathB[b][p] > housesB))
		{
			res += "0";
			res[0] += p;
			return res;
		}

	for(int d = 1; d < depth; ++ d)
		for(unsigned int p = 0; p < paths; ++ p)
		{
			tmp = solve(pathA[a][p], pathB[b][p], d);
			if(!tmp.empty())
			{
				res = "0";
				res[0] += p;
				res += tmp;
				return res;
			}
		}

	return res;
}
