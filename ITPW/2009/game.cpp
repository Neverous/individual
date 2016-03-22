/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<set>
#include<cstring>
#include<vector>

using namespace std;

#define VALUE(a) VALUE[(int)a]
#define COLOR(a) COLOR[(int)a]
int VALUE[256],
	COLOR[256];

struct Card // Karta
{
	char value, // Wartość
		 color; // Kolor

	Card(void)
	{
		value = color = 0; // Zerowanie
	}

	Card(char *card) // Karta ze stringa
	{
		value = card[0];
		color = card[1];
	}

	const bool operator<(const Card card) const // Operator mniejszości dla Seta
	{
		if(color == card.color)
			return VALUE(value) < VALUE(card.value);

		return COLOR(color) > COLOR(card.color);
	}

	const bool operator>(const Card card) const // Operator większości dla Seta
	{
		if(color == card.color)
			return VALUE(value) > VALUE(card.value);

		return COLOR(color) < COLOR(card.color);
	}
};

struct Player // Gracz
{
	set<Card> cards; // Karty na ręce
	int declared, //Zadeklarowana ilość branych lew
		id; // Identyfikator gracza
	Card actual; // Aktualna karta na stole

	Player(int playerId)
	{
		id = playerId;
		declared = 0;
	}

	Player(void)
	{
		id = declared = 0;
	}
};

struct Strife // Rozdanie
{
	int cards, // Ilość kart na ręke
		starts, // Kto zaczyna
		id, // Identyfikator rozdania
		level, // Ilość kart na stole
		players, // Ilość graczy
		color; // Kolor aktualnej lewy
	Player player[16]; // Gracze

	Strife(int strifeId, int scards, int sstarts, int splayers)
	{
		id = strifeId;
		cards = scards;
		starts = sstarts;
		players = splayers;
		level = 0;
		color = 0;
		for(int p = 0; p < players; ++ p)
			player[p] = Player(p);
	}

	Strife(void)
	{
		id = cards = starts = players = level = color = 0;
	}

	void cardPlayed(int playerId, Card card)
	{
		player[playerId].actual = card;
		if(level % players == 0)
			color = card.color;

		++ level;
		if(level % players == 0)
			for(int p = 0; p < players; ++ p)
				player[p].actual = Card();
	}
};

struct Game // Gra
{
	char *result; // Wynik do wypisania
	Strife strife[16]; // Rozdania - max 16
	int players, // Ilość graczy
		myId, // Mój ID
		strifes, // Ilość rozdań
		actStrife, // Aktualne rozdanie
		time; // Pozostało czasu
	
	Game(void)
	{
		result = new char[256];
		memset(result, 0, sizeof(char) * 256);
	}

	void quit(void) // Wyjście z gry
	{
		delete [] result;
	}

	char *setDeck(char *deck, char *colors) // Własności gry
	{
		result[0] = 0;
		for(int d = 0; deck[d]; ++ d)
		{
			VALUE[(int)deck[d]] = d + 1;
			VALUE[0] = VALUE[d + 1] = (int)deck[d];
		}

		for(int c = 0; colors[c]; ++ c)
		{
			COLOR[(int)colors[c]] = c + 1;
			COLOR[0] = COLOR[c + 1] = (int)colors[c];
		}
	
		return result;
	}

	char *setPlayers(int splayers, int smyId) // Ustawienie graczy
	{
		result[0] = 0;
		players = splayers;
		myId = smyId;
		return result;
	}

	char *setGame(int hands, int *cards, int *starting) // Ustawienia gry 
	{
		result[0] = 0;
		strifes = hands;
		actStrife = 0;
		for(int c = 0; cards[c]; ++ c)
			strife[c] = Strife(c, cards[c], starting[c], players);

		return result;
	}
	
	char *setCards(int count, char cards[128][128]) // Moje karty
	{
		result[0] = 0;
		for(int c = 0; c < count; ++ c)
			strife[actStrife].player[myId].cards.insert(Card(cards[c]));

		return result;
	}
	
	char *timeLeft(int ms) // Ile jescze zostało czasu
	{
		result[0] = 0;
		time = ms;
		return result;
	}

	char *setDeclare(void) // Ile lew weźmiesz
	{
		result[0] = 0;
		sprintf(result, "%d", (int)(((double)rand() / RAND_MAX) * strife[actStrife].cards));
		return result;
	}
	
	char *getDeclare(int playerId, int declaration) // Gracz zadeklarował, że weźmie x lew
	{
		result[0] = 0;
		strife[actStrife].player[playerId].declared = declaration;
		return result;
	}

	char *throwCard(void) // Rzuć kartę
	{
		result[0] = 0;
		Card Winner = Card(),
			 C = Card();
		Player *player = strife[actStrife].player;
		int table = 0;
		for(int p = 0; p < strife[actStrife].players; ++ p) // Ile jest kart na stole
			if(strife[actStrife].player[p].actual.color)
				++ table;

		if(!table) // Jeśli ja zaczynam
			C = *(player[myId].cards.rbegin()); // Rzuć najwyższą kartę jaką mam

		else
		{
			for(int p = 0; p < strife[actStrife].players; ++ p) // Znajdź najwyższą kartę na stole
				if(player[p].actual > Winner && (player[p].actual.color == strife[actStrife].color || COLOR(player[p].actual.color) == COLOR(COLOR[1])))
					Winner = strife[actStrife].player[p].actual;

			if(Winner.color != strife[actStrife].color) // Ktoś wyrzucił atut
			{
				for(set<Card>::iterator i = player[myId].cards.begin(); i != player[myId].cards.end(); ++ i) // Znajdź najmniejszą do koloru
					if((!C.color || (*i) > C) && (*i).color == strife[actStrife].color)
						C = (*i);

				if(!C.color) // Nie mam do koloru przebij atuta
				{
					for(set<Card>::iterator i = player[myId].cards.begin(); i != player[myId].cards.end(); ++ i)
						if(COLOR((*i).color) == COLOR(COLOR[1]) && C < (*i) && Winner < (*i))
							C = (*i);
				}

				if(!C.color) // Nie mam atutu na przebicie
				{
					for(set<Card>::iterator i = player[myId].cards.begin(); i != player[myId].cards.end(); ++ i) // znajdź najmniejszy nie atut
						if(COLOR((*i).color) != COLOR(COLOR[1]) && (!C.color || C > (*i)))
							C = (*i);
				}
			}
			else
			{
				for(set<Card>::iterator i = player[myId].cards.begin(); i != player[myId].cards.end(); ++ i) // Znajdź największą u mnie na ręce w tym samym kolorze co wygrywająca
					if((*i) > C && (*i).color == Winner.color)
						C = (*i);

				if(Winner > C) // Największa w tym kolorze i tak jest za mała
				{
					for(set<Card>::iterator i = player[myId].cards.begin(); i != player[myId].cards.end(); ++ i) // To znajdź najmniejszą
						if((!C.color || (*i) < C) && (*i).color == Winner.color)
							C = (*i);
				}
				else // znajmniejsz większa od...
				{
					for(set<Card>::iterator i = player[myId].cards.begin(); i != player[myId].cards.end(); ++ i)
						if((!C.color || (*i) < C) && (*i).color == Winner.color && (*i) > Winner)
							C = (*i);
				}

			}
			
			if(!C.color) // Ni atutu ni do koloru... mogę rzucić co chcę... - najmniejsze co mam
				C = *(player[myId].cards.begin());
		}

		if(!C.color) // Na wszelki wypadek ^^
		{
			vector<Card> avail;
			copy(player[myId].cards.begin(), player[myId].cards.end(), back_inserter(avail));
			C = avail[rand() % avail.size()];
		}

		sprintf(result, "%c%c", C.value, C.color);
		return result;
	}

	char *getCard(int playerId, char *card) // Gracz wyrzucił kartę
	{
		result[0] = 0;
		strife[actStrife].cardPlayed(playerId, Card(card));
		if(playerId == myId)
			strife[actStrife].player[myId].cards.erase(Card(card));

		if(strife[actStrife].level == strife[actStrife].cards * players)
			++ actStrife;

		return result;
	}
};


/*====================[MAIN LOOP]====================*/
Game game;
char command[16],
	 sBuffer1[128],
	 sBuffer2[128],
	 *result,
	 sTabBuffer[128][128];

int iBuffer1,
	iBuffer2,
	iTabBuffer[256];

int main(void)
{
	srand((unsigned)time(NULL));
	while(true)
	{
		result = 0;
		scanf("%s", command);
		if(!strcmp(command, "quit"))
		{
			game.quit();       
			break;
		} // quit

		if(!strcmp(command, "set_deck"))
		{
			scanf("%s%s", sBuffer1, sBuffer2);
			result = game.setDeck(sBuffer1, sBuffer2);
		} // setDeck

		else if(!strcmp(command, "set_players"))
		{
			scanf("%d%d", &iBuffer1, &iBuffer2);
			result = game.setPlayers(iBuffer1, iBuffer2);
		} // setPlayers

		else if(!strcmp(command, "set_game"))
		{
			scanf("%d", &iBuffer1);
			for(int h = 0; h < iBuffer1; ++ h)
				scanf("%d%d", &iTabBuffer[h], &iTabBuffer[h+iBuffer1]);

			result = game.setGame(iBuffer1, iTabBuffer, iTabBuffer + iBuffer1);
		} // setGame

		else if(!strcmp(command, "set_cards"))
		{
			scanf("%d", &iBuffer1);
			for(int c = 0; c < iBuffer1; ++ c)
				scanf("%s", sTabBuffer[c]);

			result = game.setCards(iBuffer1, sTabBuffer);
		} // setCards

		else if(!strcmp(command, "time_left"))
		{
			scanf("%d", &iBuffer1);
			result = game.timeLeft(iBuffer1);
		} // timeLeft

		else if(!strcmp(command, "gen_declare"))
		{
			result = game.setDeclare();
		} // setDeclare

		else if(!strcmp(command, "declare"))
		{
			scanf("%d%d", &iBuffer1, &iBuffer2);
			result = game.getDeclare(iBuffer1, iBuffer2);
		} // getDeclare

		else if(!strcmp(command, "gen_move"))
		{
			result = game.throwCard();
		} // throwCard

		else if(!strcmp(command, "play"))
		{
			scanf("%d%s", &iBuffer1, sBuffer1);
			result = game.getCard(iBuffer1, sBuffer1);
		} // getCard

		else
		{
			scanf("%*[^\n]");
			printf("? nieznane polecenie '%s'\n\n", command);
			fflush(stdout);
			continue;
		}

		printf("= %s\n\n", result);
		fflush(stdout);
	}

	return 0;
}
