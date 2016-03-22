/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
// BRUTE
#include<cstdio>
#include<list>

int tests,
    accuracy,
    test[3000030],
    temp,
    best,
    bStart,
    bEnd;

std::list<int> min,
	       max;

inline void maxPush(std::list<int> &ptr, int &value);
inline void minPush(std::list<int> &ptr, int &value);
inline int MAX(int a, int b);

int main(void)
{
	scanf("%d %d", &accuracy, &tests);
	for(int t = 0; t < tests; ++ t)
		scanf("%d", &test[t]);

	for(int t = 0, pos = 0; t < tests; ++ t)
	{
		maxPush(max, t);
		minPush(min, t);
		while(test[max.front()] - test[t] > accuracy)
		{
			pos = MAX(max.front() + 1, pos);
			max.pop_front();
		}

		while(test[t] - test[min.front()] > accuracy)
		{
			pos = MAX(min.front() + 1, pos);
			min.pop_front();
		}

		best = MAX(best, t - pos + 1);
	}

	printf("%d\n", best);
	return 0;
}

inline int MAX(int a, int b)
{
	return (a > b)?a:b;
}

void maxPush(std::list<int> &ptr, int &value)
{
	while(!ptr.empty() && test[value] >= test[ptr.back()])
		ptr.pop_back();

	ptr.push_back(value);
	return;

}

void minPush(std::list<int> &ptr, int &value)
{
	while(!ptr.empty() && test[value] <= test[ptr.back()])
		ptr.pop_back();

	ptr.push_back(value);
	return;
}

