/* 2015
 * Maciej Szeptuch
 * II UWr
 *
 * Based on:
 *  On maximal suffixes and constant-space linear-time versions of KMP algorithm
 *  by Wojciech Rytter
 */
#include <algorithm>

#define NDEBUG

#include "message.h"
#include "poszukiwania.h"

typedef unsigned int uint;

void runServer(void);
void runWorker(void);

void longestSelfMaxPrefix(uint &k, uint &period, const uint i, const uint j);
void maxSufAndPeriod(uint &v, uint &period, const uint j);
int approximatePeriod(const uint j);
bool isPeriod(const uint period, const uint j);

uint node;
uint nodes;
uint sequence;
uint signal;

int main(void)
{
    node    = MyNodeId();
    nodes   = NumberOfNodes();

    signal      = SignalLength();
    sequence    = SeqLength();

    nodes   = std::min(nodes, sequence - signal + 1);

    // Too many workers
    if(node >= nodes)
        return 0;

    if(!node)
        runServer();

    else
        runWorker();

    return 0;
}

/******************************************************************************
 * SERVER
 *****************************************************************************/
void runServer(void)
{
#ifndef NDEBUG
    assert(nodes > 0 && "Invalid number of nodes");
    fprintf(stderr, "Running server\n");
    fprintf(stderr, "    Nodes:     %u\n", nodes);
    fprintf(stderr, "    Signal:    %u\n", signal);
    fprintf(stderr, "    Sequence:  %u\n", sequence);
#endif // NDEBUG
    runWorker();

    uint result = 0U;
    for(uint n = 0; n < nodes; ++ n)
    {
        int source = Receive(-1);
        uint nodeResult = GetInt(source);
#ifndef NDEBUG
        fprintf(stderr, "Result from %u: %u\n", source, nodeResult);
#endif // NDEBUG
        result += nodeResult;
    }

    printf("%u\n", result);
}

/******************************************************************************
 * WORKER
 *****************************************************************************/
void runWorker(void)
{
#ifndef NDEBUG
    fprintf(stderr, "Running %u worker\n", node);
#endif // NDEBUG
    uint result = 0U;

    uint size = (sequence - signal + nodes) / nodes;
    uint start = node * size;
    uint end = std::min((node + 1) * size, sequence - signal + 1);

#ifndef NDEBUG
    fprintf(stderr, "%u: Processing [%u, %u)\n", node, start, end);
#endif // NDEBUG

    int period = signal;
    for(uint i = start, j = 0, R = 0; i < end;)
    {
        while(j < signal && SignalAt(j + 1) == SeqAt(i + j + 1))
            ++ j;

        if(j == signal) ++ result;
        if(period == -1 || (j < 2 * period || j > R))
        {
            period = approximatePeriod(j);
            R = j;
        }

        if(period == -1)
        {
            i += (j + 2) / 2;
            j = 0;
        }
        else
        {
            i += std::max(1, period);
            j -= period;
        }
    }

    PutInt(0, result);
#ifndef NDEBUG
    fprintf(stderr, "Sending %u result: %u\n", node, result);
#endif // NDEBUG
    Send(0);
}

void longestSelfMaxPrefix(uint &k, uint &period, const uint i, const uint j)
{
    period = 1;
    for(uint l = 2; l < j - i + 1; ++ l)
    {
        uint sig = SignalAt(i + l);
        uint sig2 = SignalAt(i + l - period);
        if(sig < sig2)
            period = l;

        else if(sig > sig2)
        {
            k = l - 1;
            return;
        }
    }

    k = j - i + 1;
}

void maxSufAndPeriod(uint &v, uint &period, const uint j)
{
    uint i = 1;
    uint k = 0;
    while(true)
    {
        longestSelfMaxPrefix(k, period, i, j);
        if(k == j - i + 1)
        {
            v = j - i + 1;
            return;
        }

        i += k - (k % period);
    }
}

int approximatePeriod(const uint j)
{
    uint period = 0;
    uint v      = 0;
    maxSufAndPeriod(v, period, j);

    if(v >= j / 2 and isPeriod(period, j))
        return period;

    return -1;
}

bool isPeriod(const uint period, const uint j)
{
    for(uint i = 1; i <= j - period; ++ i)
        if(SignalAt(i) != SignalAt(i + period))
            return false;

    return true;
}
