/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 * --------------
 *  Okienko.. o ile sie nie myle pesymistycznie O(n*sqrt(n)), optymistycznie O(n)
 */
#include<cstdio>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

const int BUFFER = 4096;
int p = BUFFER - 1;
char buffer[BUFFER];

int getNumber(void);

struct Node
{
	Node *next,
		 *previous;
	int id,
		b;

	Node(int ID, int B);
};
inline Node *remove(Node *act);

struct List
{
	Node *begin,
		 *end;

	List(void);
	inline bool empty(void);
	inline void clear(void);
	inline int extractBest(int reference);
	inline void append(int value);
};

int buildings,
	building[500050],
	rod[500050],
	sqrt[500050];
List bucket;

inline static int SQRT(int a);
inline static int ABS(int a);
inline static int MAX(int a, int b);
inline static void process(void);

int main(void)
{
	buildings = getNumber();
	//scanf("%d", &buildings);
	for(int b = 0; b < buildings; ++ b)
		building[b] = getNumber();
	//scanf("%d", &building[b]);

	process();
	for(int b = 0; b < buildings; ++ b)
		printf("%d\n", MAX(0, rod[b] - building[b]));

	return 0;
}

inline static void process(void)
{
	bucket.clear();
	for(int b = 0; b < buildings; ++ b)
	{
		bucket.append(b);
		rod[b] = bucket.extractBest(b);
	}

	bucket.clear();
	for(int b = buildings - 1; b >= 0; -- b)
	{
		bucket.append(b);
		rod[b] = MAX(rod[b], bucket.extractBest(b));
	}

	return;
}

inline static int MAX(int a, int b)
{
	return a>b?a:b;
}

inline static int ABS(int a)
{
	return a>0?a:-a;
}

inline void List::append(int value)
{
	if(!empty() && begin->b == 0 && building[begin->id] >= building[value])
		return;

	if(empty())
	{
		begin = end = new Node(value, 0);
		return;
	}

	begin->previous = new Node(value, 0);
	begin->previous->next = begin;
	begin = begin->previous;
	return;
}

inline int List::extractBest(int reference)
{
	Node *act = end;
	while(act)
	{
		if(SQRT(ABS(reference - act->id)) > act->b)
		{
			++ act->b;
			while(act->next && building[act->next->id] + act->next->b < building[act->id] + act->b)
			{
				if(act->next == end)
					end = act;

				remove(act->next);
			}

			if(act->next && (act->next->b == act->b || building[act->next->id] == building[act->id]))
			{
				if(act == begin)
					begin = act->next;

				act = remove(act);
			}
		}

		if(act)
			act = act->previous;
	}

	return end->b + building[end->id];
}

inline static int SQRT(int a)
{
	if(sqrt[a])
		return sqrt[a];

	sqrt[a] = 0;
	while(sqrt[a] * sqrt[a] < a)
		++ sqrt[a];

	return sqrt[a];
}

Node::Node(int ID, int B)
{
	next = previous = 0;
	id = ID;
	b = B;
}

inline Node *remove(Node *act)
{
	Node * ret = act->next;
	if(act->previous)
		act->previous->next = act->next;

	if(act->next)
		act->next->previous = act->previous;

	delete act;
	return ret;
}

List::List(void)
{
	begin = end = 0;
}

inline bool List::empty(void)
{
	return begin == 0;
}

inline void List::clear(void)
{
	if(empty())
		return;

	Node *act = begin;
	while(act)
		act = remove(act);

	begin = end = 0;
	return;
}

int getNumber(void)
{
	int number = 0;
	while((buffer[p] < '0' || buffer[p] > '9') && ++ p)
		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}

	while(buffer[p] >= '0' && buffer[p] <= '9')
	{
		number = number * 10 + buffer[p] - '0';
		++ p;

		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}
	}

	return number;
}
