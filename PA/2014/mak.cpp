/* 2014
 * Maciej Szeptuch
 * II UWr
 */
#include "maklib.h"
#include "message.h"

#include <cstdio>
#include <algorithm>

using namespace std;

long long   node,
            nodes,
            size,
            range,
            stages;

long long   prefix,
            suffix,
            whole,
            inside;

void moveData(long long s);
void mergeData(long long s);

int main(void)
{
    node    = MyNodeId();
    nodes   = NumberOfNodes();

    size    = Size();
    range   = (size + nodes - 1) / nodes;

    nodes = min(nodes, size);

    // Too many workers, don't need that much
    if(node >= nodes)
        return 0;

    while((1 << stages) < nodes)
        ++ stages;

    // FIRST STAGE
    long long _min = 0;
    for(long long s = node * range, e = (node + 1) * range; s < e && s < size; ++ s)
    {
        whole += ElementAt(s + 1);
        _min = min(_min, whole);

        prefix = max(prefix, whole);
        inside = max(inside, whole - _min);
    }

    suffix = whole - _min;
    moveData(0);

    // GATHERING STAGES
    for(long long stage = 1; (node % (1 << stage)) == 0 && stage <= stages; ++ stage)
    {
        mergeData(stage);
        moveData(stage);
    }

    if(!node)
        printf("%lld\n", inside);

    return 0;
}

inline
void moveData(long long s)
{
    long long senders     = (1 << (s + 1));
    long long recipient   = node - (1 << s);
    if(node % senders)
    {
        PutLL(recipient, prefix);
        PutLL(recipient, suffix);
        PutLL(recipient, whole);
        PutLL(recipient, inside);
        Send(recipient);
        //fprintf(stderr, "%lld/%lld sending to %lld\n", s, node, recipient);
    }

    //fprintf(stderr, "%lld/%lld: %lld %lld %lld %lld\n", s, node, prefix, suffix, whole, inside);
}

inline
void mergeData(long long s)
{
    long long sender = node + (1 << (s - 1));
    if(sender >= nodes)
        return;

    Receive(sender);
    //fprintf(stderr, "%lld reading from %lld\n", node, sender);
    long long   _prefix,
                _suffix,
                _whole,
                _inside;

    _prefix = GetLL(sender);
    _suffix = GetLL(sender);
    _whole  = GetLL(sender);
    _inside = GetLL(sender);

    inside = max(inside, _inside);
    inside = max(inside, suffix + _prefix);

    prefix = max(prefix, whole + _prefix);
    suffix = max(_whole + suffix, _suffix);
    whole += _whole;

    inside = max(inside, prefix);
    inside = max(inside, suffix);
    inside = max(inside, whole);
}

/*
0 1 2 3 4 5 6 7 8 9
0 # 2 # 4 # 6 # 8 #
0 # # # 4 # # # 8 #
0 # # # # # # # 8 #
0 # # # # # # # # #
*/
