/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int a,b,c,d,moves,t,x;

int main(void)
{
	scanf("%d", &moves);
	for(int m = 0; m < moves; ++ m)
	{
		scanf("%d %d", &t, &x);
		switch(t)
		{
			case 1:
				a += x;
				break;

			case 2:
				b += x;
				break;

			case 3:
				c += x;
				break;

			case 4:
				d += x;
				break;
		}
	}

	printf("%s\n", (a - c == 0 && b - d == 0)?"TAK":"NIE");
	return 0;
}

