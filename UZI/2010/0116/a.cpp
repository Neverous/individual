/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int tests,
	count[32];

char buffer,
	 last,
	 last2,
	 first,
	 first2;

bool solve(void);

int main(void)
{
	scanf("%d ", &tests);
	for(int t = 0; t < tests; ++ t)
		printf("%c\n", solve()?'P':'N');

	return 0;
}

bool solve(void)
{

	first = last = first2 = last2 = 0;
	for(int c = 0; c < 32; ++ c)
		count[c] = 0;

	while(scanf("%c", &buffer) != -1 && buffer != ' ')
	{
		if(!first)
			first = buffer;

		++ count[buffer - 'a'];
		last = buffer;
	}

	while(scanf("%c", &buffer) != -1 && buffer != '\n')
	{
		if(!first2)
			first2 = buffer;

		-- count[buffer - 'a'];
		last2 = buffer;
	}

	for(int c = 0; c < 32; ++ c)
		if(count[c])
			return false;

	return first == first2 && last == last2;
}
