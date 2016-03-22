/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	players,
	win[128][128],
	games[128],
	wins[128];

char buffer[128];

long double wp[128],
			owp[128],
			oowp[128];

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &players);
		for(int p = 0; p < players; ++ p)
		{
			for(int o = 0; o < players; ++ o)
				win[p][o] = -1;

			wins[p] = 0;
			games[p] = 0;
			wp[p] = 0;
			owp[p] = 0;
			oowp[p] = 0;
		}

		for(int p = 0; p < players; ++ p)
		{
			scanf("%s", buffer);
			for(int o = 0; o < players; ++ o)
			{
				if(buffer[o] == '.')
					continue;

				++ games[p];
				wins[p] += buffer[o] == '1';
				win[p][o] = buffer[o] == '1';
			}
		}

		for(int p = 0; p < players; ++ p)
		{
			wp[p] = (long double)wins[p] / games[p];
			for(int o = 0; o < players; ++ o)
				if(win[p][o] != -1)
					owp[p] += (long double)(wins[o] - win[o][p]) / (games[o] - 1);

			owp[p] /= games[p];
		}

		for(int p = 0; p < players; ++ p)
		{
			for(int o = 0; o < players; ++ o)
				if(win[p][o] != -1)
					oowp[p] += owp[o];

			oowp[p] /= games[p];
		}

		printf("Case #%d:\n", t + 1);
		for(int p = 0; p < players; ++ p)
			printf("%.8Lf\n", (wp[p] + oowp[p]) / 4 + owp[p] / 2);

	}

	return 0;
}

