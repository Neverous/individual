/* 2010
 * Maciej Szeptuch
 * XIV LO WrocĹ�aw
 */
#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#define ABS(a) ((a) > 0?(a):-(a))
#define X first.first
#define Y first.second
#define ESCAPE second.first
#define NUMBER second.second

int points,
	bound[50050];
long long unsigned int result;
std::pair<int, int> origPoint[50050];
std::pair<std::pair<int, int>, std::pair<int, int> > point[100010];
std::set<std::pair<int, int> > tree;
std::set<std::pair<int, int> >::iterator position;

bool compare(const std::pair<std::pair<int, int>, std::pair<int, int> > &A, const std::pair<std::pair<int, int>, std::pair<int, int> > &B)
{
	if(A.X < B.X)
		return true;

	if(A.X > B.X)
		return false;

	if(A.Y > B.Y)
		return true;

	if(A.Y < B.Y)
		return false;

	if(A.ESCAPE > B.ESCAPE)
		return false;

	if(A.ESCAPE < B.ESCAPE)
		return true;

	return A.NUMBER < B.NUMBER;
}

int main(void)
{
	scanf("%d", &points);
	for(int p = 0; p < points; ++ p)
	{
		scanf("%d %d", &point[p].X, &point[p].Y);
		origPoint[p].first = point[p].X;
		origPoint[p].second = point[p].Y;
		point[p].ESCAPE = false;
		point[p].NUMBER = p;
	}

	for(int p = 0; p < points; ++ p)
	{
		scanf("%d %d", &point[points + p].X, &point[points + p].Y);
		point[points + p].ESCAPE = true;
		point[points + p].NUMBER = p;
	}

	std::sort(point, point + 2 * points, compare);
	for(int p = 0; p < 2 * points; ++ p)
	{
		if(!point[p].ESCAPE)
		{
			tree.insert(std::pair<int, int>(point[p].Y, point[p].NUMBER));
		}

		else
		{
			position = tree.lower_bound(std::pair<int, int>(point[p].Y, 0));
			bound[position->second] = point[p].NUMBER;
			result += ABS(origPoint[position->second].first - point[p].X) +
				ABS(origPoint[position->second].second - point[p].Y);
			tree.erase(position);
		}
	}

	printf("%llu\n", result);
	for(int p = 0; p < points; ++ p)
		printf("%d %d\n", p + 1, bound[p] + 1);

	return 0;
}
