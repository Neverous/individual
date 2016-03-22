/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int patch,
	type,
	result;
bool count[16384];

int main(void)
{
	scanf("%d", &patch);
	result = 15000;
	for(int p = 0; p < patch; ++ p)
	{
		scanf("%d", &type);
		result -= !count[type];
		count[type] = true;
	}

	printf("%d\n", result);
	return 0;
}

