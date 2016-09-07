/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
#include<algorithm>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...) {}

class iTree
{
	private:
		static const int SIZE = (1 << 19);
		int data[SIZE * 2];

	public:
		iTree(void);
		void insert(const int &point);
		inline int getInterval(const int &start, const int &end, const int &iStart = 0, const int &iEnd = SIZE - 1, const int &pos = 1);
};

enum Direction
{
	UP = 1,
	RIGHT = 2,
	DOWN = 4,
	LEFT = 8,
};

const int MAX_COORD = 200002;
inline static int _(const int &a){return a + MAX_COORD;}

int points,
	polygons,
	verts,
	x, y,
	nX, nY,
	result[32768];
Direction direction,
		  lDirection;
std::vector<std::pair<std::pair<int, int>, int> > point;
std::vector<std::pair<int, int> > polygon,
								  action;

iTree tree;

int main(void)
{
	scanf("%d %d", &points, &polygons);
	for(int p = 0; p < points; ++ p)
	{
		scanf("%d %d", &x, &y);
		x = _(x); y = _(y);
		point.push_back(std::make_pair(std::make_pair(x, y), 0)); // coords, action(if not 0)
	}

	/* READ POLYGON */
	for(int p = 0; p < polygons; ++ p)
	{
		scanf("%d", &verts);
		polygon.clear();
		for(int v = 0; v < verts; ++ v)
		{
			scanf("%d %d", &x, &y);
			polygon.push_back(std::make_pair(_(x), _(y)));
		}

		for(int v = 0; v < verts; ++ v)
		{
			x = polygon[v].first; y = polygon[v].second;
			nX = polygon[(v + 1) % verts].first; nY = polygon[(v + 1) % verts].second;

			if(nX - x > 0) direction = RIGHT;
			else if(nX - x < 0) direction = LEFT;
			else if(nY - y > 0) direction = UP;
			else direction = DOWN;

			switch(direction)
			{
				case UP: // -
					-- x;
					if(lDirection == RIGHT) ++ y;
					action.push_back(std::make_pair(y, -p - 1));
					point.push_back(std::make_pair(std::make_pair(x, nY), action.size()));
					break;

				case DOWN: // +
					if(lDirection == LEFT) -- y;
					action.push_back(std::make_pair(nY, p + 1));
					point.push_back(std::make_pair(std::make_pair(x, y), action.size()));
					break;

				case LEFT:
					if(action.empty())
						break;

					if(lDirection == UP) -- point.back().first.second;
					if(point.back().first.second < action.back().first)
					{
						point.pop_back();
						action.pop_back();
					}
					break;

				case RIGHT:
					if(action.empty())
						break;

					if(lDirection == DOWN) ++ action.back().first;
					if(point.back().first.second < action.back().first)
					{
						point.pop_back();
						action.pop_back();
					}
					break;
			}

			lDirection = direction;
		}

		/* REPAIR STARTING POINT */
		x = polygon[0].first; y = polygon[0].second;
		nX = polygon[1].first; nY = polygon[1].second;

		if(nX - x > 0) direction = RIGHT;
		else if(nX - x < 0) direction = LEFT;
		else if(nY - y > 0) direction = UP;
		else direction = DOWN;
		switch(direction)
		{
			case LEFT:
				if(action.empty())
					break;

				if(lDirection == UP) -- point.back().first.second;
				if(point.back().first.second < action.back().first)
				{
					point.pop_back();
					action.pop_back();
				}
				break;

			case RIGHT:
				if(action.empty())
					break;

				if(lDirection == DOWN) ++ action.back().first;
				if(point.back().first.second < action.back().first)
				{
					point.pop_back();
					action.pop_back();
				}
				break;
		}
	}

	/* TIME TO WORK */
	std::sort(point.begin(), point.end());
	for(int p = 0, poly, start, res; p < point.size(); ++ p)
	{
		if(!point[p].second)
		{
			tree.insert(point[p].first.second);
			DEBUG(">>%d\n", point[p].first.second);
			continue;
		}

		start = action[point[p].second - 1].first;
		poly = action[point[p].second - 1].second;
		res = tree.getInterval(start, point[p].first.second);
		DEBUG("(%d) ASK[%d, %d] => %d\n", poly, start - MAX_COORD, point[p].first.second - MAX_COORD, res);
		if(poly < 0)
		{
			res *= -1;
			poly = -poly;
		}

		result[poly - 1] += res;
	}

	for(int p = 0; p < polygons; ++ p)
		printf("%d\n", result[p]);

	return 0;
}

iTree::iTree(void)
{
	for(int s = 0; s < this->SIZE * 2; ++ s)
		this->data[s] = 0;
}

void iTree::insert(const int &point)
{
	for(int pos = this->SIZE + point; pos > 0; pos /= 2)
		++ this->data[pos];

	return;
}

inline int iTree::getInterval(const int &start, const int &end, const int &iStart, const int &iEnd, const int &pos)
{
	if(iStart == start && iEnd == end)
		return this->data[pos];

	const int iMiddle = (iStart + iEnd) / 2;
	if(end <= iMiddle)
		return this->getInterval(start, end, iStart, iMiddle, pos * 2);

	if(start > iMiddle)
		return this->getInterval(start, end, iMiddle + 1, iEnd, pos * 2 + 1);

	return this->getInterval(start, iMiddle, iStart, iMiddle, pos * 2) +
		   this->getInterval(iMiddle + 1, end, iMiddle + 1, iEnd, pos * 2 + 1);
}
