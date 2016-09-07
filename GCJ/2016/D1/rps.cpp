/* 2016
 * Maciej Szeptuch
 * II UWr
 */

#include <algorithm>
#include <message.h>
#include <stdio.h>

#include "rps.h"

bool winner(long long first_id, long long second_id)
{
    char first = GetFavoriteMove(first_id);
    char second = GetFavoriteMove(second_id);

    if(first == second)
        return first_id < second_id;

    switch(first)
    {
        case 'R':
            return second == 'S';

        case 'P':
            return second == 'R';

        case 'S':
            return second == 'P';
    }

    return false;
}

int main(void)
{
    long long rounds = GetN();
    long long nodes = NumberOfNodes();

    if(nodes > (1LL << (rounds - 1)))
        nodes = (1LL << (rounds - 1));

    if(nodes & (nodes - 1))
        nodes &= nodes - 1;

    long long my_id = MyNodeId();

    if(my_id >= nodes)
        return 0;

    long long int players_per_node = ((1LL << rounds) + nodes - 1) / nodes;
    players_per_node += players_per_node % 2;

    long long int next_round[std::max(players_per_node / 2, nodes)];
    for(long long int p = players_per_node * my_id, end = std::min((1LL << rounds), players_per_node * (my_id + 1)), w = 0; p < end; p += 2, ++ w)
        next_round[w] = winner(p, p + 1) ? p : p + 1;

    for(long long int players_left = players_per_node / 2; players_left > 1; players_left /= 2)
        for(long long int p = 0; p < players_left; p += 2)
            next_round[p / 2] = winner(next_round[p], next_round[p + 1]) ? next_round[p] : next_round[p + 1];

    if(my_id)
    {
        PutLL(0, next_round[0]);
        Send(0);
        return 0;
    }

    for(long long int node = 1; node < nodes; ++ node)
    {
        Receive(node);
        next_round[node] = GetLL(node);
    }

    std::sort(next_round, next_round + nodes);
    for(long long int players_left = nodes; players_left > 1; players_left /= 2)
        for(long long int p = 0; p < players_left; p += 2)
            next_round[p / 2] = winner(next_round[p], next_round[p + 1]) ? next_round[p] : next_round[p + 1];

    printf("%lld\n", next_round[0]);
    return 0;
}
