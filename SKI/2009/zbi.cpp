/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<cstring>

int tests,
	width,
	height,
	quests,
	start,
	end,
	count,
	game[1001],
	zeros;

char action[4];

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d %d", &width, &height, &quests);
		for(int w = 0; w < width; ++ w)
			game[w] = height;

		for(int q = 0; q < quests; ++ q)
		{
			scanf("%s", action);
			if(action[0] == 'Z')
			{
				scanf("%d %d %d", &start, &end, &count);
				for(int g = start - 1; g < end; ++ g)
					game[g] = (game[g] - count>0)?game[g] - count:0;

				printf("OK\n");
				continue;
			}

			zeros = 0;
			for(int w = 0; w < width; ++ w)
			{
				if(!zeros && !game[w])
				{
					start = w;
					zeros = 1;
				}

				else if(zeros == 1 && game[w])
				{
					end = w - 1;
					zeros = 2;
				}

				else if(zeros == 2 && !game[w])
				{
					zeros = 3;
					break;
				}
			}

			printf("%s ", zeros?"TAK":"NIE");
			if(zeros < 3 && zeros)
				printf("%d %d", start + 1, end + 1);

			puts("");
		}
	}
}
