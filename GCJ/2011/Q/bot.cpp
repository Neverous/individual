/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#define DEBUG(args...) fprintf(stderr, args)
//#define DEBUG(args...)

int tests,
	actions,
	button,
	oTime, bTime,
	oButton, bButton;
char robot[2];

inline static const unsigned int ABS(const int &a){return a<0?-a:a;}
inline static const int MAX(const int &a, const int &b){return a>b?a:b;}

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &actions);
		oTime = bTime = 0;
		oButton = bButton = 1;
		for(int a = 0; a < actions; ++ a)
		{
			scanf("%s %d", robot, &button);
			switch(robot[0])
			{
				case 'O':
					oTime = MAX(oTime + ABS(oButton - button) + 1, bTime + 1);
					oButton = button;
					break;

				case 'B':
					bTime = MAX(bTime + ABS(bButton - button) + 1, oTime + 1);
					bButton = button;
					break;

				default:
					throw "Error!";
			}

			DEBUG("O: %d %d | B: %d %d\n", oTime, oButton, bTime, bButton);
		}

		printf("Case #%d: %d\n", t + 1, MAX(oTime, bTime));
	}

	return 0;
}

