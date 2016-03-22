/* 2011
 * Maciej Szeptuch
 * -*-*-*-*-*-*-*-*-
 */
#include<cstdio>
#include<vector>
#include<list>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	numbers,
	seq[1048576];
std::list<std::pair<int, int> > que;

int solve(void)
{
	int result = -2000000000,
		sum = 0;
	que.clear();
	que.push_back(std::make_pair(-1, 0));
	for(int n = 0; n < 2 * numbers; ++ n)
	{
		sum += seq[n % numbers];
		while(!que.empty() && que.front().first < n - numbers)
			que.pop_front();

		if(result < sum - que.front().second)
			result = sum - que.front().second;

		while(!que.empty() && que.back().second > sum)
			que.pop_back();

		que.push_back(std::make_pair(n, sum));
	}

	return result;
}

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &numbers);
		for(int n = 0; n < numbers; ++ n)
			scanf("%d", &seq[n]);

		printf("%d\n", solve());
	}

	return 0;
}

