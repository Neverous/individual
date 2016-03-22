/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<list>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

struct Measure
{
	int high,
		low;
};

class Queue
{
	private:
		std::list<std::pair<int, int> > data;

	public:
		Queue(void);
		inline void push(const std::pair<int, int> &v);
		inline std::pair<int, int> top(void) const;
		inline void pop_front(void);
};

int measures,
	best;
Measure measure[1048576];
Queue que;

inline static int MAX(const int &a, const int &b){return a>b?a:b;}

int main(void)
{
	scanf("%d", &measures);
	for(int m = 0; m < measures; ++ m)
		scanf("%d %d", &measure[m].low, &measure[m].high);

	for(int m = 0, l = 0; m < measures && l < measures; ++ m)
	{
		while(l < measures && que.top().first <= measure[l].high)
		{
			que.push(std::make_pair(measure[l].low, l));
			++ l;
		}

		best = MAX(best, l - m);
		if(que.top().second == m)
			que.pop_front();
	}

	printf("%d\n", best);
	return 0;
}

Queue::Queue(void)
{
	return;
}

inline void Queue::push(const std::pair<int, int> &v)
{
	if(this->data.empty())
	{
		this->data.push_back(v);
		return;
	}

	while(!this->data.empty() && this->data.back() < v)
		this->data.pop_back();


	this->data.push_back(v);
	return;
}

inline std::pair<int, int> Queue::top(void) const
{
	if(this->data.empty())
		return std::make_pair(-1000000000, 0);

	return this->data.front();
}

inline void Queue::pop_front(void)
{
	if(this->data.empty())
		return;

	this->data.pop_front();
	return;
}
