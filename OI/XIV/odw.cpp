/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<queue>
#include<algorithm>

int containers,
	container,
	weights,
	weight[100010],
	act;
std::priority_queue<int> available,
	temp;

int solve(void);
bool packable(int count);

int main(void)
{
	scanf("%d %d", &containers, &weights);
	for(int c = 0; c < containers; ++ c)
	{
		scanf("%d", &container);
		available.push(container);
	}

	for(int w = 0; w < weights; ++ w)
		scanf("%d", &weight[w]);

	std::sort(weight, weight + weights);
	printf("%d\n", solve());
	return 0;
}

int solve(void)
{
	int start = 0,
		end = weights,
		middle;

	while(start < end - 1)
	{
		middle = (start + end) / 2;
		temp = available;
		if(packable(middle))
			start = middle;

		else
			end = middle - 1;
	}

	temp = available;
	if(packable(end))
		return end;

	temp = available;
	if(end && packable(end - 1))
		return end - 1;

	return start;
}

bool packable(int count)
{
	for(int w = count - 1; w >= 0; -- w)
	{
		if(temp.empty())
			return false;

		act = temp.top();
		if(act < weight[w])
			return false;

		temp.pop();
		act -= weight[w];
		if(act)
			temp.push(act);
	}

	return true;
}
