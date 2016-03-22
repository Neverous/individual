/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<string>
#include<cstdlib>
#include<sstream>
#include<ctime>
#include<vector>
#include<algorithm>
#define _PLAYER1(sign) ((sign) >= 'A' && (sign) <= 'Z')
#define _PLAYER2(sign) ((sign) >= 'a' && (sign) <= 'z')
#define _DIVISION(sign) (_PLAYER1(sign)?(sign) - 'A':(_PLAYER2(sign)?(sign) - 'a':sign))
/* STRUCTURES/CLASSES ETC. */
namespace Map //Mapa
{
	enum Field
	{
		WALKABLE,
		BLOCKED,
	};
};

namespace Player // Gracz
{
	class Soldier // Żołnierz
	{
		public:
			unsigned int x,
						 y;
			Soldier(unsigned int X = 0, unsigned int Y = 0);
	};

	class Division // Dywizja
	{
		public:
			std::vector<Soldier> soldiers;
			unsigned int headX,
						 headY;
			int deltaX,
				deltaY;
			bool attack,
				 prefer;
			Soldier getPosition(void);
	};
};

namespace Game
{
	void moveDivision(Player::Division &d);
};

Map::Field map[1024][1024];
Player::Division division1[30],
	division2[30];
Player::Soldier cel,
	cel2,
	cel3;

std::string action,
	response;
unsigned int cols,
			 rows,
			 rounds,
			 strength,
			 left;

std::string error[2] = {
	"Unknown command",
	"Not implemented",
};

std::string getAction(void);
std::string setGame(void);
std::string timeLeft(void);
std::string genMove(void);
std::string play(void);

int main(void)
{
	//srand(time(0));
	while(true)
	{
		try
		{
			action = getAction();
			if(action == "set_game")
			{
				response = setGame();
			}

			else if(action == "time_left")
			{
				response = timeLeft();
			}

			else if(action == "gen_move")
			{
				response = genMove();
			}

			else if(action == "play")
			{
				response = play();
			}

			else
			{
				throw 0;
			}

			printf("= %s\n\n", response.c_str());
		}
		catch(int code)
		{
			printf("? %d %s\n\n", code, error[code].c_str());
		}

		fflush(stdout);
	}
	return 0;
}

std::string getAction(void)
{
	char command[16];
	scanf("%s", command);
	return std::string(command);
}

std::string setGame(void)
{
	char row[1024];
	scanf("%u %u %u %u", &cols, &rows, &rounds, &strength);
	for(unsigned int r = 0; r < rows; ++ r)
	{
		scanf("%s", row);
		for(unsigned int c = 0; row[c]; ++ c)
		{
			map[r][c] = (row[c] != '.')?Map::BLOCKED:Map::WALKABLE;
			if(_PLAYER1(row[c]))
				division1[_DIVISION(row[c])].soldiers.push_back(Player::Soldier(c, r));

			if(_PLAYER2(row[c]))
				division2[_DIVISION(row[c])].soldiers.push_back(Player::Soldier(c, r));
		}
	}

	return std::string();
}

std::string timeLeft(void)
{
	scanf("%u", &left);
	return std::string();
}

std::string genMove(void)
{
	std::stringstream stream;
	char division[2];
	scanf("%s", division);
	if(rand() % 3)
	{
		Player::Division *act;
		int d = rand() % 30;
		if(_PLAYER1(division[0]))
			act = division2;

		else
			act = division1;

		while(!act[d].soldiers.size())
			d = rand() % 30;

		Player::Soldier pos = act[d].getPosition();
		stream<<1<<" "<<pos.x<<" "<<pos.y<<" "<<(rand() % 2) * 2 - 1<<" "<<(rand() % 2) * 2 - 1<<" "<<rand() % 2;

	}
	else
		stream<<1<<" "<<rand() % cols<<" "<<rand() % rows<<" "<<(rand() % 2) * 2 - 1<<" "<<(rand() % 2) * 2 - 1<<" "<<rand() % 2;

	return stream.str();
}

std::string play(void)
{
	unsigned int attack,
				 x,
				 y,
				 prefer;
	int dx,
		dy;
	char division[2];
	Player::Division *act;
	scanf("%s %u %u %u %d %d %u", division, &attack, &x, &y, &dx, &dy, &prefer);
	if(_PLAYER1(division[0]))
		act = &division1[_DIVISION(division[0])];

	else
		act = &division2[_DIVISION(division[0])];

	act->attack = attack;
	act->headX = x;
	act->headY = y;
	act->deltaX = dx;
	act->deltaY = dy;
	act->prefer = prefer;
	Game::moveDivision(*act);
	return std::string();
}

/* CLASSES METHODS */
Player::Soldier::Soldier(unsigned int X, unsigned int Y)
{
	this->x = X;
	this->y = Y;
}

Player::Soldier Player::Division::getPosition(void)
{
	Soldier result;
	for(unsigned int s = 0; s < this->soldiers.size(); ++ s)
	{
		result.x += this->soldiers[s].x;
		result.y += this->soldiers[s].y;
	}

	result.x /= this->soldiers.size();
	result.y /= this->soldiers.size();
	return result;
}

int distance(int x, int x2, int y, int y2)
{
	return (x - x2) * (x - x2) + (y - y2) * (y - y2);
}

bool comp(const Player::Soldier &A, const Player::Soldier &B)
{
	int roz = distance(A.x, cel.x, A.y, cel.y) - distance(B.x, cel.x, B.y, cel.y);
	if(roz != 0)
		return roz < 0;

	roz = distance(A.x, cel2.x, A.y, cel2.y) - distance(B.x, cel2.x, B.y, cel2.y);
	if(roz != 0)
		return roz < 0;

	roz = distance(A.x, cel3.x, A.y, cel3.y) - distance(B.x, cel3.x, B.y, cel3.y);
	return roz < 0;
}

void Game::moveDivision(Player::Division &d)
{
	cel = Player::Soldier(d.headX, d.headY);
	cel2 = d.prefer?Player::Soldier(d.headX + d.deltaX, d.headY):Player::Soldier(d.headX, d.headY + d.deltaY);
	cel3 = d.prefer?Player::Soldier(d.headX, d.headY + d.deltaY):Player::Soldier(d.headX + d.deltaX, d.headY);
	std::sort(d.soldiers.begin(), d.soldiers.end(), comp);
	for(std::vector<Player::Soldier>::iterator s = d.soldiers.begin(); s != d.soldiers.end(); ++ s)
	{
		int bestX = s->x,
			bestY = s->y;

		for(int i = -1; i < 2; ++ i)
			for(int j = -1; j < 2; ++ j)
			{
				if(s->x + i < 0 ||
						s->x + i > cols ||
						s->y + j < 0 ||
						s->y + j > rows ||
						map[s->y + j][s->x + i] == Map::BLOCKED)
					continue;

				if(comp(Player::Soldier(s->x + i, s->y + j), Player::Soldier(bestX, bestY)))
				{
					bestX = s->x + i;
					bestY = s->y + j;
				}
			}

		map[s->y][s->x] = Map::WALKABLE;
		map[bestY][bestX] = Map::BLOCKED;
		s->x = bestX;
		s->y = bestY;
	}
}

