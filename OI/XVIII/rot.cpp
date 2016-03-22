/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>

int leafs;

inline static std::pair<std::vector<int>, long long int> readTree(void); 
inline static long long int MIN(const long long int &a, const long long int &b){return a<b?a:b;}

int main(void)
{
	scanf("%d", &leafs);
	printf("%lld\n", readTree().second);
	return 0;
}

inline static std::pair<std::vector<int>, long long int> readTree(void)
{
	std::vector<int> sum;
	std::pair<std::vector<int>, long long int> left,
											   right;
	long long int invA = 0,
		 		  invB = 0;

	int value;
	scanf("%d", &value);
	if(value)
	{
		sum.push_back(value);
		return std::make_pair(sum, 0);
	}

	left = readTree();
	right = readTree();
	int a = 0,
		b = 0;
	
	while(a < left.first.size() && b < right.first.size())
	{
		if(left.first[a] < right.first[b])
		{
			sum.push_back(left.first[a]);
			++ a;
			invB += right.first.size() - b;
		}

		else
		{
			sum.push_back(right.first[b]);
			++ b;
			invA += left.first.size() - a;
		}
	}

	while(a < left.first.size())
	{
		sum.push_back(left.first[a]);
		++ a;
	}

	while(b < right.first.size())
	{
		sum.push_back(right.first[b]);
		++ b;
	}

	return std::make_pair(sum, MIN(invA, invB) + left.second + right.second);
}

