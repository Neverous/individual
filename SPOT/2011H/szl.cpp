/* 2011
 * Maciej Szeptuch
 * -*-*-*-*-*-*-*-*-
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	length,
	position,
	number;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d", &length, &position);
		position %= 2 * length;
		if(position >= length)
			position = 2 * length - position - 1;

		for(int l = 0; l < length; ++ l)
		{
			scanf("%d", &number);
			if(l == position)
				printf("%d\n", number);
		}
	}

	return 0;
}

