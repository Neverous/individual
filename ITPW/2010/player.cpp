/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<string>
#include<cstdlib>
#include<sstream>
#include<ctime>

std::string action,
			response,
			map[1024],
			last[256];
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
	srand(time(0));
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
		map[r] = std::string(row);
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
	if(!last[(int)division[0]].empty() && rand() % 3 != 2)
		return last[(int)division[0]];

	stream<<1<<" "<<rand() % cols<<" "<<rand() % rows<<" "<<(rand() % 2) * 2 - 1<<" "<<(rand() % 2) * 2 - 1<<" "<<rand() % 2;
	return last[(int)division[0]] = stream.str();
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
	scanf("%s %u %u %u %d %d %u", division, &attack, &x, &y, &dx, &dy, &prefer);
	throw 1;
	return std::string();
}
