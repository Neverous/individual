/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>

int elements,
	stack[131072],
	ndStack[131072],
	act,
	ndStackSize,
	result[1048576],
	r;
bool ndStackHave[65536];


int main(void)
{
	scanf("%d", &elements);
	elements *= 2;
	for(int e = 1; e <= elements; ++ e)
		scanf("%d", &stack[elements - e]);

	while(elements --)
	{
		act = stack[elements];
		if(!ndStackHave[act])
		{
			ndStackHave[act] = true;
			ndStack[ndStackSize ++] = act;
		}

		else
		{
			-- ndStackSize;
			ndStackHave[ndStack[ndStackSize]] = false;
			if(act != ndStack[ndStackSize])
			{
				result[r ++] = ndStackSize + 1;
				stack[elements ++] = ndStack[ndStackSize];
				stack[elements ++] = act;
			}
		}
	}

	printf("%d\n", r);
	for(int rr = 0; rr < r; ++ rr)
		printf("%d\n", result[rr]);

	return 0;
}

