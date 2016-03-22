/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>

using namespace std;

int tests,
	last,
	act;
long long unsigned int number,
					   powerOfThree;
vector<long long unsigned int> left,
							   right;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%lld", &number);
		right.clear();
		left.clear();
		last = 0;
		act = 0;
		for(powerOfThree = 1; number; number /= 3, powerOfThree *= 3)
		{
			switch(number % 3)
			{
				case 0:
					//printf("{0, %lld}", number);
					//printf("[%lld %d]", powerOfThree, act);
					if(act == -1)
					{
						right.push_back(powerOfThree);
						act = 0;
					}

					break;

				case 1:
					//printf("{1, %lld}", number);
					if(act == -1)
						left.push_back(powerOfThree);

					else
					{
						right.push_back(powerOfThree);
						act = 0;
					}

					break;

				case 2:
					//printf("{2, %lld}", number);
					act += 1;
					if(act == 1)
						left.push_back(powerOfThree);

					act = -1;
					break;
			}
		}

		if(act == -1)
			right.push_back(powerOfThree);

		for(unsigned int l = 0; l < left.size(); ++ l)
			printf("%lld ", left[l]);

		printf("| ");

		for(unsigned int r = 0; r < right.size(); ++ r)
			printf("%lld ", right[r]);

		puts("");
	}

	return 0;
}

