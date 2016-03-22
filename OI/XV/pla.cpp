#include<cstdio>
#include<stack>
using namespace std;
stack<int> tab;
int buildings,result,temp;
int main(void)
{
	scanf("%d", &buildings);
	for(int i=0;i<buildings;i++)
	{
		scanf("%*d %d", &temp);
		while(!tab.empty() && temp <= tab.top())
		{
			 if(tab.top()!=temp)
			 	result++;
			 tab.pop();
		}
		tab.push(temp);
	}
	printf("%d\n", result+tab.size());
	return 0;
}

