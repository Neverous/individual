/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int start = 1,
	end,
	apples,
	column,
	result;

int main(void)
{
	scanf("%*d %d %d", &end, &apples);
	for(int a = 0; a < apples; ++ a)
	{
		scanf("%d", &column);
		if(start <= column && column <= end)
			continue;

		if(column < start)
		{
			result += start - column;
			end -= start - column;
			start = column;
		}

		else if(column > end)
		{
			result += column - end;
			start += column - end;
			end = column;
		}
	}

	printf("%d\n", result);
	return 0;
}

