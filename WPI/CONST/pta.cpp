/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	weight;

bool readCase(bool first);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &weight);
		puts(readCase(true)?"TAK":"NIE");
	}

	return 0;
}

bool readCase(bool first = false)
{
	int size;
	scanf("%d", &size);
	bool ret = size < weight || (first && weight == size);
	for(int s = 0; s < size; ++ s)
		ret = readCase() && ret;

	return ret;
}
