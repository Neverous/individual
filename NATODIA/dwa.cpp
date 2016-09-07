/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

inline long long unsigned int min(long long unsigned int A, long long unsigned int B);
long long unsigned int solve(long long unsigned int start, long long unsigned int count, long long unsigned int difference, long long unsigned int MOD);

int tests;
long long unsigned int start,
					   count,
					   difference,
					   MOD;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%llu %llu %llu %llu", &start, &count, &difference, &MOD);
		printf("%llu\n", solve(start, count, difference, MOD));
	}

	return 0;
}

long long unsigned int solve(long long unsigned int start, long long unsigned int count, long long unsigned int difference, long long unsigned int MOD)
{
	long long unsigned int result = 0,
						   power = 1,
						   next = 0,
						   previous = 0;

	while(power * 2 <= start)
		power *= 2;

	while(next < count)
	{
		previous = next;
		next = (power * 2 - start + difference - 1) / difference;
		while(next == previous)
		{
			power *= 2;
			next = (power * 2 - start + difference - 1) / difference;
		}

		if(next > count)
			next = count;

		// może jutro to poprawie... nie chce mi się już myśleć ani tym bardziej big numów pisać...
		/* BRAIN OFF START */
		long long unsigned int something = power,
			 sth2 = 100000000000000000LLU / (next - previous);
		while(something)
		{
			result = (result + min(sth2, something) * (next - previous)) % MOD;
			something -= min(sth2, something);
		}
		/* BRAIN OFF END */
		//result = (result + (power % MOD) * (next - previous)) % MOD;

		power *= 2;
	}

	return result;
}

inline long long unsigned int min(long long unsigned int A, long long unsigned int B)
{
	return A<B?A:B;
}
