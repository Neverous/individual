/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
#include<set>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

class yClassOperator
{
	public:
		bool operator()(const std::pair<int, int> &A, const std::pair<int, int> &B) const;
};

class xClassOperator
{
	public:
		bool operator()(const std::pair<int, int> &A, const std::pair<int, int> &B) const;
};

bool yOperator(const std::pair<int, int> &A, const std::pair<int, int> &B);

unsigned int tests,
			 points,
			 actions;
char action[8];
int tolerance;
std::pair<int, int> point[131072],
					left,
					highest,
					temp;
std::set<std::pair<int, int>, yClassOperator> upperLeft,
										 rest;
std::set<std::pair<int, int>, xClassOperator> leftUpper;

int main(void)
{
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		leftUpper.clear();
		upperLeft.clear();
		rest.clear();

		scanf("%u %d", &points, &tolerance);
		for(unsigned int p = 0; p < points; ++ p)
			scanf("%d %d", &point[p].first, &point[p].second);

		std::sort(point, point + points, yOperator);
		for(unsigned int p = 0; p < points; ++ p)
		{
			if(point[p].second >= point[0].second - tolerance)
			{
				leftUpper.insert(point[p]);
				upperLeft.insert(point[p]);
			}
			else
				rest.insert(point[p]);
		}

		left = *leftUpper.begin();
		highest = *upperLeft.begin();
		scanf("%u", &actions);
		for(unsigned int a = 0; a < actions; ++ a)
		{
			scanf("%s", action);
			if(action[0] == 'Z')
				printf("%d %d\n", left.first, left.second);

			else
			{
				scanf("%d %d", &point[points].first, &point[points].second);
				if(point[points].second >= highest.second - tolerance)
				{
					leftUpper.erase(point[points]);
					upperLeft.erase(point[points]);
					if(upperLeft.empty() && !rest.empty())
					{
						temp = *rest.begin();
						leftUpper.insert(temp);
						upperLeft.insert(temp);
						rest.erase(rest.begin());
					}

					highest = *upperLeft.begin();
					while(!rest.empty() && (temp = *rest.begin()).second >= highest.second - tolerance)
					{
						leftUpper.insert(temp);
						upperLeft.insert(temp);
						rest.erase(rest.begin());
					}

					left = *leftUpper.begin();
				}

				else
					rest.erase(point[points]);
			}
		}
	}

	return 0;
}

bool yOperator(const std::pair<int, int> &A, const std::pair<int, int> &B)
{
	if(A.second > B.second)
		return true;

	if(A.second < B.second)
		return false;

	return A.first < B.first;
}

bool yClassOperator::operator()(const std::pair<int, int> &A, const std::pair<int, int> &B) const
{
	return yOperator(A, B);
}

bool xClassOperator::operator()(const std::pair<int, int> &A, const std::pair<int, int> &B) const
{
	if(A.first < B.first)
		return true;

	if(A.first > B.first)
		return false;

	return A.second > B.second;
}
