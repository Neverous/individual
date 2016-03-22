/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<algorithm>
#define DEBUG if(1)

unsigned int size,
			 seq[2020],
			 count[2],
			 m;
bool visited[2020],
	 worked;
std::vector<int> steps;

inline static unsigned int visit(unsigned int s);
inline static void moveA(unsigned int pos = 0);
inline static void moveB(int move = 1);

int main(void)
{
	scanf("%u", &size);
	for(unsigned int s = 0; s < size; ++ s)
	{
		scanf("%u", &seq[s]);
		-- seq[s];
	}

	/* CHECK IF POSSIBLE */
	if(size % 2)
	{
		for(unsigned int s = 0 ; s < size; ++ s)
			if(!visited[s])
				++ count[visit(s) % 2];

		if(count[0] % 2)
		{
			puts("NIE DA SIE");
			return 0;
		}
	}

	/* POSSIBLE, NOW TRY TO SORT IT */
	worked = true;
	for(unsigned int sp = 0; size > 3 && sp < 2; ++ sp)
	{
		while(worked)
		{
			//for(unsigned int s = 0; s < size; ++ s)
			//printf("%u%c", seq[s], s + 1 == size?'\n':' ');

			worked = false;
			for(unsigned int p = 0; p < size; ++ p)
			{
				moveA(p);
				if(seq[p] == 0)
				{
					/* SPECIAL CASE A */
					if(size - seq[(p + 2) % size] - 1 <= (seq[(p + 2) % size] < seq[(p + 1) % size]))
					{
						worked = true;
						moveB();
					}

					continue;
				}

				if(seq[(p + 1) % size] == 0)
				{
					/* SPECIAL CASE B */
					if(size - seq[(p + 2) % size] - 1 <= (seq[(p + 2) % size] < seq[p]))
					{
						worked = true;
						moveB();
					}

					continue;
				}

				if(seq[(p + 2) % size] == 0)
				{
					/* SPECIAL CASE C */
					continue;
				}

				while(seq[p] > seq[(p + 2) % size] || seq[(p + 1) % size] > seq[(p + 2) % size])
				{
					worked = true;
					moveB();
				}
			}
		}

		for(unsigned int p = 0; p < size; ++ p)
		{
			moveA(p);
			if(seq[p] == 0)
			{
				/* SPECIAL CASE A */
				if(size - seq[(p + 2) % size] - 1 <= (seq[(p + 2) % size] < seq[(p + 1) % size]))
				{
					worked = true;
					moveB();
				}
			}

			if(seq[(p + 1) % size] == 0)
			{
				/* SPECIAL CASE B */
				if(size - seq[(p + 2) % size] - 1 <= (seq[(p + 2) % size] < seq[p]))
				{
					worked = true;
					moveB();
				}

				continue;
			}

			if(seq[(p + 2) % size] == 0)
			{
				/* SPECIAL CASE C */
				continue;
			}

			while(seq[p] > seq[(p + 2) % size] || seq[(p + 1) % size] > seq[(p + 2) % size])
			{
				worked = true;
				moveB();
			}
		}
	}

	/* BACK TO ONE */
	for(unsigned int p = 0; p < size; ++ p)
		if(seq[p] == 0)
		{
			moveA(p);
			break;
		}

	//for(unsigned int s = 0; s < size; ++ s)
	//printf("%u%c", seq[s], s + 1 == size?'\n':' ');

	printf("%u\n", (unsigned int)steps.size());
	for(unsigned int s = 0; s < steps.size(); ++ s)
		if(steps[s] < 0)
			printf("%ub ", -steps[s]);

		else
			printf("%ua ", steps[s]);

	puts("");
	return 0;
}

inline static unsigned int visit(unsigned int s)
{
	unsigned int res = 0;
	while(!visited[s])
	{
		visited[s] = true;
		++ res;
		s = seq[s];
	}

	return res;
}

inline static void moveA(unsigned int pos)
{
	if(steps.empty() || steps.back() < 0)
		steps.push_back(0);

	*steps.rbegin() = (*steps.rbegin() + (size - pos + m) % size) % size;
	m = pos;

	if(!steps.back())
		steps.pop_back();

	return;
}

inline static void moveB(int move)
{
	if(steps.empty() || steps.back() > 0)
		steps.push_back(0);

	*steps.rbegin() = (*steps.rbegin() - move) % 3;
	for(int b = 0; b < move; ++ b)
	{
		std::swap(seq[m], seq[(m + 2) % size]);
		std::swap(seq[(m + 2) % size], seq[(m + 1) % size]);
	}

	if(!steps.back())
		steps.pop_back();

	return;
}

