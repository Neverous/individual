/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<string>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

using namespace std;

int intervals,
	patterns;
long long unsigned int interval[5005];
char buffer[20];

long long unsigned int check(string pattern);
string lluToString(long long unsigned int number);
int count(string where, string what);

int main(void)
{
	scanf("%d %d", &intervals, &patterns);
	for(int i = 0; i < 2 * intervals; i += 2)
		scanf("%llu %llu", &interval[i], &interval[i + 1]);

	for(int p = 0; p < patterns; ++ p)
	{
		scanf("%s", buffer);
		printf("%llu\n", check(string(buffer)));
	}

	return 0;
}

long long unsigned int check(string pattern)
{
	long long unsigned int result = 0;
	for(int i = 0; i < 2 * intervals; i += 2)
	{
		for(long long unsigned int s = interval[i]; s <= interval[i + 1]; ++ s)
			result += count(lluToString(s), pattern);
	}

	return result;
}

string lluToString(long long unsigned int number)
{
	string result;
	while(number)
	{
		result += number % 10 + '0';
		number /= 10;
	}

	return result;
}

int count(string where, string what)
{
	int result = 0;
	bool pasuje = false;
	for(unsigned int w = 0; w < where.size(); ++ w)
	{
		pasuje = true;
		for(unsigned int p = 0; pasuje && p < what.size(); ++ p)
			if(where[w + p] != what[p])
				pasuje = false;

		result += pasuje;
	}

	return result;
}
