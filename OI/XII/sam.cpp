/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<list>
#include<queue>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int cars,
	actions,
	action[500001],
	moves;
const int INFINITY = 1 << 20;
unsigned int size,
			 groundSize;
bool onGround[100001];
std::list<int> wanted[100001];
std::priority_queue<std::pair<int, int> > ground;
std::pair<int, int> act;

int main(void)
{
	scanf("%d %d %d", &cars, &size, &actions);
	for(int a = 0; a < actions; ++ a)
	{
		scanf("%d", &action[a]);
		wanted[action[a]].push_back(a);
	}

	for(int c = 0; c < cars; ++ c)
		wanted[c].push_back(INFINITY);

	for(int a = 0; a < actions; ++ a)
	{
		if(onGround[action[a]])
		{
			wanted[action[a]].pop_front();
			ground.push(std::make_pair(wanted[action[a]].front(), action[a]));
			continue;
		}

		wanted[action[a]].pop_front();
		while(groundSize >= size)
		{
			act = ground.top();
			ground.pop();
			onGround[act.second] = false;
			-- groundSize;
		}

		ground.push(std::make_pair(wanted[action[a]].front(), action[a]));
		onGround[action[a]] = true;
		++ moves;
		++ groundSize;
	}

	printf("%d\n", moves);
	return 0;
}
