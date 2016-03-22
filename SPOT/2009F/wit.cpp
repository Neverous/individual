/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<map>
#include<vector>
 
using namespace std;
 
int lines,
	Ax,
	Ay,
	Bx,
	By;
long long unsigned int result = 1;
map<double, int> data;
double a;
 
int main(void)
{
	scanf("%d", &lines);
	for(int l = 0; l < lines; ++ l)
	{
		scanf("%d %d %d %d", &Ax, &Ay, &Bx, &By);
		if(Bx - Ax)
			a = (double)(By - Ay) / (Bx - Ax);

		else
			a = 1.0/0.0; // PIONOWA PROSTA

		result += l + 1 - data[a];
		++ data[a];
	}
 
	printf("%llu\n", result);
	return 0;
}

