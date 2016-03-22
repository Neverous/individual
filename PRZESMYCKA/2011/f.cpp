/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
#include<cstring>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	zeroA,
	zeroB,
	oneA[1048576],
	oneB[1048576],
	result,
	len;
char wordA[1048576],
	 wordB[1048576];

inline static const int MAX(const int &a, const int &b){return a>b?a:b;}
inline static const int MIN(const int &a, const int &b){return a<b?a:b;}

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%s %s", wordA, wordB);
		len = strlen(wordA);
		zeroA = zeroB = result = 0;
		bzero(oneA, sizeof(oneA));
		bzero(oneB, sizeof(oneB));
		for(int i = len - 1; i >= 0; -- i)
		{
			oneA[i] = oneA[i + 1] + (wordA[i] == '1');
			oneB[i] = oneB[i + 1] + (wordB[i] == '1');
		}

		result = MIN(oneA[0], oneB[0]);
		for(int z = 1, a = 0, b = 0; b < len && a < len; ++ a, ++ b, ++ z)
		{
			while(a < len && wordA[a] != '0')
				++ a;

			while(b < len && wordB[b] != '0')
				++ b;

			if(a >= len || b >= len)
				break;

			result = MAX(result, z + MIN(oneA[a], oneB[b]));
		}

		printf("%d\n", result);
	}

	return 0;
}

