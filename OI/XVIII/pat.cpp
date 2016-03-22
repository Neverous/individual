/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<algorithm>

int colors,
	quantity,
	stick,
	next[1048576],
	temp[1048576],
	tempSize;
std::vector<int> color[64];
std::vector<std::pair<int, int> > all;

inline static void solve(void);

int main(void)
{
	scanf("%d", &colors);
	for(int c = 0; c < colors; ++ c)
	{
		scanf("%d", &quantity);
		for(int q = 0; q < quantity; ++ q)
		{
			scanf("%d", &stick);
			color[c].push_back(stick);
			all.push_back(std::make_pair(stick, c));
		}

		std::sort(color[c].rbegin(), color[c].rend());
	}

	std::sort(all.rbegin(), all.rend());
	solve();
	return 0;
}

inline static void solve(void)
{
	for(int c = 0; c < colors; ++ c)
	{
		tempSize = all.size() - color[c].size();
		for(int a = all.size() - 1, t = tempSize - 1; a >= 0 && t >= 0; -- a)
			if(all[a].second != c)
			{
				temp[t] = a;
				next[t] = all.size();
				if(t < tempSize - 1)
				{
					if(all[temp[t]].second == all[temp[t + 1]].second)
						next[t] = next[t +  1];

					else
						next[t] = temp[t + 1];

				}

				-- t;
			}

		for(int e = 0, t = 0; e < color[c].size() && t < tempSize - 1 && next[t] < all.size(); ++ e)
		{
			while(t < tempSize - 1 && next[t] < all.size() && all[temp[t]].first > color[c][e])
				++ t;

			if(t < tempSize - 1 && next[t] < all.size() && color[c][e] < all[temp[t]].first + all[next[t]].first)
			{
				printf("%d %d %d %d %d %d\n", c + 1, color[c][e], all[temp[t]].second + 1, all[temp[t]].first, all[next[t]].second + 1, all[next[t]].first);
				return;
			}
		}

	}

	puts("NIE");
	return;
}

