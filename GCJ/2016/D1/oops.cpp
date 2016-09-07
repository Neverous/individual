/* 2016
 * Maciej Szeptuch
 * II UWr
 */

#include <algorithm>
#include <message.h>
#include <stdio.h>

#include "oops.h"

int main(void)
{
    long long numbers = GetN();
    long long nodes = NumberOfNodes();

    if(nodes > numbers)
        nodes = numbers;

    long long my_id = MyNodeId();

    if(my_id >= nodes)
        return 0;

    long long min = GetNumber(0);
    long long max = min;

    long long int numbers_per_node = (numbers + nodes - 1) / nodes;


    for(long long n = numbers_per_node * my_id, end = std::min(numbers, numbers_per_node * (my_id + 1)); n < end; ++ n)
    {
        long long num = GetNumber(n);
        if(num < min)
            min = num;

        if(num > max)
            max = num;
    }

    if(my_id)
    {
        PutLL(0, min);
        PutLL(0, max);
        Send(0);
        return 0;
    }

    for(long long node = 1; node < nodes; ++ node)
    {
        Receive(node);
        long long node_min = GetLL(node);
        long long node_max = GetLL(node);
        if(node_min < min) min = node_min;
        if(node_min > max) max = node_min;
        if(node_max < min) min = node_max;
        if(node_max > max) max = node_max;
    }

    printf("%lld\n", max - min);
    return 0;
}
