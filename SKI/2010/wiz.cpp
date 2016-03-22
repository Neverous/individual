/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

class Application
{
	public:
		unsigned int start,
					 end,
					 cash;

		Application(void);
		bool operator<(const Application &B) const;
		bool first(const Application &B) const;
		bool second(const Application &B) const;
		bool third(const Application &B) const;
		bool fourth(const Application &B) const;
		bool fifth(const Application &B) const;
		bool sixth(const Application &B) const;
};

unsigned int applications,
			 reserved,
			 state;
long long unsigned int cash,
					   best;
Application appl[10010];

int main(void)
{
	srand(42);
	scanf("%u", &applications);
	for(unsigned int a = 0; a < applications; ++ a)
		scanf("%u %u %u", &appl[a].start, &appl[a].end, &appl[a].cash);

	for(unsigned int s = 0; s < 6; ++ s)
	{
		state = s;
		cash = 0;
		reserved = 0;
		std::sort(appl, appl + applications);
		for(unsigned int a = 0; a < applications; ++ a)
		{
			if(appl[a].end <= reserved)
				continue;

			cash += appl[a].cash;
			if(appl[a].start > reserved + 1)
				reserved = appl[a].start;

			else
				reserved += 1;
		}

		if(cash > best)
			best = cash;
	}

	/* TIME FOR SHUFFLE ^^ */
	for(unsigned int s = 0; s < 2000; ++ s)
	{
		cash = 0;
		reserved = 0;
		std::random_shuffle(appl, appl + applications);
		for(unsigned int a = 0; a < applications; ++ a)
		{
			if(appl[a].end <= reserved)
				continue;

			cash += appl[a].cash;
			if(appl[a].start > reserved + 1)
				reserved = appl[a].start;

			else
				reserved += 1;
		}

		if(cash > best)
			best = cash;
	}

	printf("%llu\n", best);
	return 0;
}

Application::Application(void)
{
	start = end = cash = 0;
}

bool Application::operator<(const Application &B) const
{
	switch(state)
	{
		case 0:
			return this->first(B);
			break;

		case 1:
			return this->second(B);
			break;

		case 2:
			return this->third(B);
			break;

		case 3:
			return this->fourth(B);
			break;

		case 4:
			return this->fifth(B);
			break;

		case 5:
			return this->sixth(B);
			break;
	}

	return false;
}

bool Application::first(const Application &B) const
{
	if(this->start < B.start)
		return true;

	if(this->start > B.start)
		return false;

	if(this->end < B.end)
		return true;

	if(this->end > B.end)
		return false;

	if(this->cash > B.cash)
		return true;

	if(this->cash < B.cash)
		return false;

	return false;
}

bool Application::second(const Application &B) const
{
	if(this->start < B.start)
		return true;

	if(this->start > B.start)
		return false;

	if(this->cash > B.cash)
		return true;

	if(this->cash < B.cash)
		return false;

	if(this->end < B.end)
		return true;

	if(this->end > B.end)
		return false;

	return false;

}

bool Application::third(const Application &B) const
{
	if(this->end < B.end)
		return true;

	if(this->end > B.end)
		return false;

	if(this->start < B.start)
		return true;

	if(this->start > B.start)
		return false;

	if(this->cash > B.cash)
		return true;

	if(this->cash < B.cash)
		return false;

	return false;
}

bool Application::fourth(const Application &B) const
{
	if(this->end < B.end)
		return true;

	if(this->end > B.end)
		return false;

	if(this->cash > B.cash)
		return true;

	if(this->cash < B.cash)
		return false;

	if(this->start < B.start)
		return true;

	if(this->start > B.start)
		return false;

	return false;
}

bool Application::fifth(const Application &B) const
{
	if(this->cash > B.cash)
		return true;

	if(this->cash < B.cash)
		return false;

	if(this->start < B.start)
		return true;

	if(this->start > B.start)
		return false;

	if(this->end < B.end)
		return true;

	if(this->end > B.end)
		return false;

	return false;
}

bool Application::sixth(const Application &B) const
{
	if(this->cash > B.cash)
		return true;

	if(this->cash < B.cash)
		return false;

	if(this->end < B.end)
		return true;

	if(this->end > B.end)
		return false;

	if(this->start < B.start)
		return true;

	if(this->start > B.start)
		return false;

	return false;
}
