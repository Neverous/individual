/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	dominoes,
	distance[131072],
	height[131072],
	left[131072],
	right[131072],
	best;
std::vector<int> que;

bool lowerOperator(const int &dominoe, const int &dist);
bool higherOperator(const int &dominoe, const int &dist);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		best = 0;
		scanf("%d", &dominoes);
		for(int d = 0; d < dominoes; ++ d)
		{
			scanf("%d %d", &distance[d], &height[d]);
			left[d] = d;
			right[d] = d;
		}

		que.clear();
		for(int d = 0; d < dominoes; ++ d)
		{
			que.push_back(d);
			if(!que.empty())
			{
				left[d] = left[*std::lower_bound(que.begin(), que.end(), distance[d] - height[d], higherOperator)];
				//printf("L: %d %d\n", d, left[d]);
			}

			while(!que.empty() && left[d] <= left[que.back()])
				que.pop_back();

			que.push_back(d);
		}

		que.clear();
		for(int d = dominoes - 1; d >= 0; -- d)
		{
			que.push_back(d);
			if(!que.empty())
			{
				right[d] = right[*std::lower_bound(que.begin(), que.end(), distance[d] + height[d], lowerOperator)];
				//printf("R: %d %d\n", d, right[d]);
			}

			while(!que.empty() && right[d] >= right[que.back()])
				que.pop_back();

			que.push_back(d);
		}

		for(int d = 0; d < dominoes; ++ d)
		{
			best = d - left[d] + 1 > best?d - left[d] + 1:best;
			best = right[d] - d + 1 > best?right[d] - d + 1:best;
		}

		printf("%d\n", best);
	}

	return 0;
}

bool higherOperator(const int &dominoe, const int &dist)
{
	return dist > distance[dominoe];
}

bool lowerOperator(const int &dominoe, const int &dist)
{
	return dist < distance[dominoe];
}
