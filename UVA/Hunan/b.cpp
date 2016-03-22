/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <vector>

struct Node
{
    int id;
    Node *prev;
    Node *next;

    void swap(Node &node);
    void insertBefore(Node &node);
    void insertAfter(Node &node);
};

int t,
    boxes,
    actions,
    type, first, second;
bool reversed;

Node list[131072];

inline long long int countOdd(bool rev);

int main(void)
{
    while(scanf("%d %d", &boxes, &actions) != -1)
    {
        reversed = false;
        for(int b = 0; b < boxes; ++ b)
        {
            list[b].id = b + 1;
            list[b].prev = &list[b - 1];
            list[b].next = &list[b + 1];
        }

        list[0].prev = NULL;
        list[boxes - 1].next = NULL;
        for(int a = 0; a < actions; ++ a)
        {
            scanf("%d", &type);
            if(type != 4)
            {
                scanf("%d %d", &first, &second);
                -- first;
                -- second;
            }

            if(reversed)
            {
                if(type == 1)
                    type = 2;

                else if(type == 2)
                    type = 1;
            }

            switch(type)
            {
                case 4:
                    reversed ^= 1;
                    break;

                case 3:
                    list[first].swap(list[second]);
                    break;

                case 2:
                    list[second].insertAfter(list[first]);
                    break;

                case 1:
                    list[second].insertBefore(list[first]);
                    break;
            }
        }

        printf("Case %d: %lld\n", ++ t, countOdd(reversed));
    }

    return 0;
}

inline long long int countOdd(bool rev)
{
    long long int sum = 0;
    Node* act = &list[0];
    if(rev)
    {
        while(act->next)
            act = act->next;

        while(act)
        {
            sum += act->id;
            act = act->prev;
            if(act) act = act->prev;
        }

        return sum;
    }

    while(act->prev)
        act = act->prev;

    while(act)
    {
        sum += act->id;
        act = act->next;
        if(act) act = act->next;
    }

    return sum;
}

inline void Node::swap(Node &node)
{
    if(node.id == id)
        return;

    Node *temp = NULL;

    if(next != &node)
    {
        temp = node.next;
        node.next = next;
        next = temp;
    }

    else
    {
        next = node.next;
        node.next = this;
    }


    if(prev != &node)
    {
        temp = node.prev;
        node.prev = prev;
        prev = temp;
    }

    else
    {
        prev = node.prev;
        node.prev = this;
    }

    if(node.prev)
        node.prev->next = &node;

    if(node.next)
        node.next->prev = &node;

    if(next)
        next->prev = this;

    if(prev)
        prev->next = this;
}

inline void Node::insertBefore(Node &node)
{
    if(node.id == id)
        return;

    if(prev && prev->id == id)
        return;

    if(node.prev)
        node.prev->next = node.next;

    if(node.next)
        node.next->prev = node.prev;
    
    if(prev)
        prev->next = &node;

    node.next = this;
    node.prev = prev;
    prev = &node;
}

inline void Node::insertAfter(Node &node)
{
    if(node.id == id)
        return;

    if(next && next->id == node.id)
        return;

    if(node.prev)
        node.prev->next = node.next;

    if(node.next)
        node.next->prev = node.prev;

    if(next)
        next->prev = &node;

    node.prev = this;
    node.next = next;
    next = &node;
}
