/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#define DEBUG(args...) fprintf(stderr, args)
//#define DEBUG(args...)

int tests;
char onwards[16384],
	 backwards[16384],
	 repr[16] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
std::vector<std::vector<int> > map;

inline static const int MAX(const int &a, const int &b){return a>b?a:b;}
inline static const int MIN(const int &a, const int &b){return a<b?a:b;}

enum Direction
{
	NORTH = 1,
	SOUTH = 2,
	WEST = 4,
	EAST = 8,
};

struct Cell
{
	int x, y,
		go[16];
	int mask;

	Cell(int _x, int _y);
};

class Grid
{
	private:
		std::vector<Cell> cells;
		Direction facing;
		int bottomWall,
			leftWall,
			rightWall,
			position;

	public:
		Grid(void);
		inline void clear(void);
		inline const int getHeight(void) const;
		inline const int getWidth(void) const;
		inline const int getLeftWall(void) const;

		/* MOVEMENT */
		inline const std::pair<int, int> getPosition(void) const;
		inline const int getMask(void) const;
		inline void setPassage(void);
		inline void moveForward(bool builder = true);
		inline void turnLeft(void);
		inline void turnRight(void);
};

Grid grid;

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		map.clear();
		grid.clear();
		scanf("%s", onwards);
		for(int b = 1; onwards[b + 1]; ++ b)
		{
			switch(onwards[b])
			{
				case 'W': grid.moveForward(); break;
				case 'L': grid.turnLeft(); break;
				case 'R': grid.turnRight(); break;
			}
		}

		grid.setPassage();
		grid.turnRight(); grid.turnRight();
		scanf("%s", backwards);
		for(int b = 1; backwards[b + 1]; ++ b)
		{
			switch(backwards[b])
			{
				case 'W': grid.moveForward(); break;
				case 'L': grid.turnLeft(); break;
				case 'R': grid.turnRight(); break;
			}
		}

		grid.turnRight(); grid.turnRight();
		map.resize(grid.getHeight());
		for(int h = 0; h < grid.getHeight(); ++ h)
			map[h].resize(grid.getWidth());

		printf("JOŁ\n");
		for(int b = 1; onwards[b + 1]; ++ b)
		{
			map[grid.getPosition().first][grid.getPosition().second - grid.getLeftWall()] = grid.getMask();
			switch(onwards[b])
			{
				case 'W': grid.moveForward(false); break;
				case 'L': grid.turnLeft(); break;
				case 'R': grid.turnRight(); break;
			}
		}

		printf("JOŁ2\n");
		grid.turnRight(); grid.turnRight();
		for(int b = 1; backwards[b + 1]; ++ b)
		{
			map[grid.getPosition().first][grid.getPosition().second - grid.getLeftWall()] = grid.getMask();
			switch(backwards[b])
			{
				case 'W': grid.moveForward(false); break;
				case 'L': grid.turnLeft(); break;
				case 'R': grid.turnRight(); break;
			}
		}

		printf("Case #%d:\n", t + 1);
		for(int h = 0; h < grid.getHeight(); ++ h)
		{
			for(int w = 0; w < grid.getWidth(); ++ w)
				putchar(repr[map[h][w]]);

			puts("");
		}
	}

	return 0;
}

Cell::Cell(int _x = 0, int _y = 0)
{
	x = _x;
	y = _y;
	mask = 0;
	for(int g = 0; g < 16; ++ g)
		go[g] = -1;

	return;
}

Grid::Grid(void)
{
	DEBUG("Grid\n");
	this->clear();
	this->facing = SOUTH;
	this->cells.push_back(Cell());
}

inline void Grid::clear(void)
{
	DEBUG("clear\n");
	this->cells.clear();
	this->bottomWall = 0;
	this->leftWall = 0;
	this->rightWall = 0;
	this->position = 0;
	return;
}

inline const int Grid::getHeight(void) const
{
	DEBUG("getHeight(%d)\n", this->bottomWall + 1);
	return this->bottomWall + 1;
}

inline const int Grid::getWidth(void) const
{
	DEBUG("getWidth(%d)\n", this->rightWall - this->leftWall + 1);
	return this->rightWall - this->leftWall + 1;
}

inline const int Grid::getLeftWall(void) const
{
	DEBUG("getLeftWall(%d)\n", this->leftWall);
	return this->leftWall;
}

inline const std::pair<int, int> Grid::getPosition(void) const
{
	DEBUG("getPosition(%d, %d)\n", this->cells[this->position].x, this->cells[this->position].y);
	return std::pair<int, int> (this->cells[this->position].y, this->cells[this->position].x);
}

inline const int Grid::getMask(void) const
{
	DEBUG("getMask(%d)\n", this->cells[this->position].mask);
	return this->cells[this->position].mask;
}

inline void Grid::setPassage(void)
{
	DEBUG("setPassage(%d)\n", this->facing);
	this->cells[this->position].mask |= this->facing;

	return;
}

inline void Grid::moveForward(bool builder)
{
	DEBUG("moveForward(%d, %d)\n", this->cells[this->position].x, this->cells[this->position].y);
	if(!builder)
	{
		this->position = this->cells[this->position].go[this->facing];
		if(this->position == -1)
			throw "DUPA";

		return;
	}

	this->setPassage();
	Cell &act = this->cells[this->position],
		 next = Cell(act.x + (this->facing == EAST) - (this->facing == WEST),
			act.y + (this->facing == SOUTH) - (this->facing == NORTH));

	switch(this->facing)
	{
		case NORTH: next.mask |= SOUTH; break;
		case SOUTH: next.mask |= NORTH; break;
		case EAST: next.mask |= WEST; break;
		case WEST: next.mask |= EAST; break;
	}

	next.go[next.mask] = this->position;
	this->position = this->cells.size();
	this->cells.push_back(next);
	act.go[this->facing] = this->position;

	this->leftWall = MIN(this->leftWall, next.x);
	this->rightWall = MAX(this->rightWall, next.x);
	this->bottomWall = MAX(this->bottomWall, next.y);
	return;
}

inline void Grid::turnLeft(void)
{
	DEBUG("turnLeft\n");
	switch(this->facing)
	{
		case NORTH: this->facing = WEST; break;
		case EAST: this->facing = NORTH; break;
		case SOUTH: this->facing = EAST; break;
		case WEST: this->facing = SOUTH; break;
	}

	return;
}

inline void Grid::turnRight(void)
{
	DEBUG("turnRight\n");
	switch(this->facing)
	{
		case NORTH: this->facing = EAST; break;
		case EAST: this->facing = SOUTH; break;
		case SOUTH: this->facing = WEST; break;
		case WEST: this->facing = NORTH; break;
	}

	return;
}
