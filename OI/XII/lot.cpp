/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int stations,
	fuel[1000010],
	distance[1000010],
	tank;
bool ans[1000010];

int main(void)
{
	scanf("%d", &stations);
	for(int s = 0; s < stations; ++ s)
		scanf("%d %d", &fuel[s], &distance[s]);

	for(int s = 0, p = 0; s < stations; p = ++ s)
	{
		if(fuel[s] < distance[s])
			continue;

		tank = fuel[s];
		do
		{
			tank -= distance[p];
			p = (p + 1) % stations;
			tank += fuel[p];
		}
		while(p != s && tank >= distance[p]);

		if(p == s)
			ans[s] = true;
	}

	for(int s = stations - 1, p = stations - 1; s >= 0; p = -- s)
	{
		if(ans[s] || fuel[s] < distance[(stations + s - 1) % stations])
			continue;

		tank = fuel[s];
		do
		{
			tank -= distance[(stations + p - 1) % stations];
			p = (stations + p - 1) % stations;
			tank += fuel[p];
		}
		while(p != s && tank >= distance[(stations + p - 1) % stations]);

		if(p == s)
			ans[s] = true;
	}

	for(int s = 0; s < stations; ++ s)
		printf("%s\n", ans[s]?"TAK":"NIE");

	return 0;
}

