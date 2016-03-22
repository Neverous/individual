/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<queue>
#include<cstring>
#define SIZE 1048576

using namespace std;

struct iTree
{
	int elems[2 * SIZE];

	iTree(void)
	{
		memset(elems, 0, 2 * SIZE * sizeof(int));
	}

	bool remove(int elem)
	{
		elem += SIZE;
		if(elems[elem] == 0)
			return false;

		for(;elem; elem /= 2)
			-- elems[elem];
		
		return true;
	}

	bool insert(int elem)
	{
		elem += SIZE;
		
		for(;elem; elem /= 2)
			++ elems[elem];

		return true;
	}

	int find(int elem)
	{
		int act = 1;
		while(act < SIZE)
		{
			if(elem > elems[act * 2])
			{
				elem -= elems[act * 2];
				act = act * 2 + 1;
			}

			else
				act *= 2;
		}

		return act - SIZE;
	}
};

int actions,
	weight;
queue<int> que;
char action[16];
iTree tree;

int main(void)
{
	scanf("%d", &actions);
	for(int a = 0; a < actions; ++ a)
	{
		scanf("%s", action);
		if(action[0] == 'o')
		{
			tree.remove(que.front());
			que.pop();
			continue;
		}

		if(action[0] == 't')
		{
			if(que.size()%2)
				printf("%d\n", tree.find(que.size() / 2 + 1));

			else
				printf("%d %d\n", tree.find(que.size() / 2), tree.find(que.size() / 2 + 1));

			continue;
		}

		scanf("%d", &weight);
		que.push(weight);
		tree.insert(weight);
	}
	return 0;
}
