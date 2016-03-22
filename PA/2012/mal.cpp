/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>
#include <stack>
#include <vector>
#include <set>
 
using namespace std;

const int BUFFER = 4096;
int p = BUFFER - 1;
char buffer[BUFFER];

int getInt(void)
{
	int number = 0;
	while((buffer[p] < '0' || buffer[p] > '9') && ++ p)
		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}

	while(buffer[p] >= '0' && buffer[p] <= '9')
	{
		number = number * 10 + buffer[p] - '0';
		++ p;

		if(p == BUFFER)
		{
			fread(buffer, BUFFER, sizeof(char), stdin);
			p = 0;
		}
	}

	return number;
}
 
int children,
    x1, y1,
    x2, y2;
long long int result;
vector<pair<pair<int, bool>, pair<int, int> > > area;
multiset<pair<int, bool> > points;
 
inline void insertInterval(const pair<int, int> &interval);
inline void removeInterval(const pair<int, int> &interval);
inline int countLevel(void);
 
int main(void)
{
    children = getInt();
    for(int c = 0; c < children; ++ c)
    {
        x1 = getInt(); y1 = getInt();
        x2 = getInt(); y2 = getInt();
        area.push_back(make_pair(make_pair(x1, false), make_pair(y1, y2)));
        area.push_back(make_pair(make_pair(x2, true), make_pair(y1, y2)));
    }
 
    sort(area.begin(), area.end());
    insertInterval(area[0].second); // pierwszy zawsze zaczyna
    for(unsigned int a = 1; a < area.size(); ++ a)
    {
        if(points.size() / 2 >= children - 1 && area[a].first.first != area[a - 1].first.first)
            result += (long long int)(area[a].first.first - area[a - 1].first.first) * countLevel();
 
        //printf("%d\n", result);
        if(area[a].first.second)
            removeInterval(area[a].second);
 
        else
            insertInterval(area[a].second);
    }
 
    printf("%lld\n", result);
    return 0;
}
 
inline void insertInterval(const pair<int, int> &interval)
{
    points.insert(make_pair(interval.second, true));
    points.insert(make_pair(interval.first, false));
}
 
inline void removeInterval(const pair<int, int> &interval)
{
    points.erase(points.find(make_pair(interval.second, true)));
    points.erase(points.find(make_pair(interval.first, false)));
}
 
inline int countLevel(void)
{
    stack<int> inter;
    int res = 0;
    for(multiset<pair<int, bool> >::iterator it = points.begin(); it != points.end(); ++ it)
    {
        if(!it->second)
            inter.push(it->first);
 
        else
        {
            if(inter.size() == children - 1)
                res += it->first - inter.top();
 
            inter.pop();
        }
    }
 
    return res;
}
