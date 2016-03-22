/* 2014
 * Maciej Szeptuch
 * II UWr
 */
#include "kollib.h"
#include "message.h"

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <algorithm>
#include <random>
#include <functional>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <chrono>

using namespace std;

typedef long long               ll;
typedef unsigned long long      llu;
typedef vector<ll>              Array;
typedef vector<pair<ll, ll>>    Graph;
typedef unordered_map<ll, ll>   Map;

ll  node,
    nodes,
    students,
    queries;
llu workers;


// SERVER
Graph graph[512];
Array mapping;

void    runServer(void);
void    chooseStartPoints(void);
void    renumber(void);
ll      renumber(ll vert);
void    readGraph(void);
void    solve(void);


// WORKER
Array stop;
Array edge;

void    runWorker(void);
void    readQueries(void);
ll      readStartPoints(void);
void    traverse(ll start);
void    sendVertex(ll &last, ll &current, ll &count);


int main(void)
{
    node    = MyNodeId();
    nodes   = NumberOfNodes();
    workers = nodes - 1;

    students    = NumberOfStudents();
    queries     = NumberOfQueries();

    nodes   = min(nodes, students + 1);

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
inline
void runServer(void)
{
#ifndef NDEBUG
    assert(workers > 0 && "Invalid number of workers");
    fprintf(stderr, "Running server\n");
    fprintf(stderr, "    Nodes:     %llu\n", nodes);
    fprintf(stderr, "    Students:  %llu\n", students);
    fprintf(stderr, "    Queries:   %llu\n", queries);
    fprintf(stderr, "    Workers:   %llu\n", workers);
#endif // NDEBUG

    // Choose worker start points
    chooseStartPoints();

    // Renumber vertices
    renumber();

    // Read graph edges
    readGraph();

    // Calculate answer
    solve();
}

inline
void chooseStartPoints(void)
{
    default_random_engine           rand;
    random_device                   device;
    uniform_int_distribution<ll>    distribution(1, students);
    auto random = bind(distribution, rand);
    set<ll> startPoints;

#ifndef NDEBUG
    fprintf(stderr, "Choosing start points\n");
#endif // NDEBUG

    rand.seed(device());
    while(startPoints.size() < workers)
        startPoints.insert(random());

    mapping = Array(begin(startPoints), end(startPoints));
#ifndef NDEBUG
    for(auto p = 0LLU; p < workers; ++ p)
        fprintf(stderr, "Worker %llu got %llu as starting point\n", p + 1, mapping[p]);

#endif // NDEBUG

    for(auto w = 0LLU; w < workers; ++ w)
    {
        for(auto p = 0LLU; p < workers; ++ p)
            PutLL(w + 1, mapping[p]);

        Send(w + 1);
#ifndef NDEBUG
        fprintf(stderr, "Sent start points to %llu\n", w + 1);
#endif // NDEBUG
    }
}

inline
void renumber(void)
{
#ifndef NDEBUG
    fprintf(stderr, "Renumbering vertices\n");
#endif // NDEBUG
    for(auto q = 0LL; q < queries; ++ q)
    {
        mapping.push_back(QueryFrom(q + 1));
        mapping.push_back(QueryTo(q + 1));
    }

    sort(begin(mapping), end(mapping));
    mapping.erase(unique(begin(mapping), end(mapping)), end(mapping));
#ifndef NDEBUG
    assert(mapping.size() < 512 && "Invalid mapping size");
    fprintf(stderr, "Renumbered %lu vertices\n", mapping.size());
#endif // NDEBUG
}

inline
ll renumber(ll vert)
{
#ifndef NDEBUG
    assert(binary_search(begin(mapping), end(mapping), vert) && "Not mapped vertex?");
#endif // NDEBUG
    return distance(begin(mapping), lower_bound(begin(mapping), end(mapping), vert));
}

inline
void readGraph(void)
{
#ifndef NDEBUG
    fprintf(stderr, "Reading graph edges\n");
#endif // NDEBUG

    unordered_set<ll> finished;
    for(auto w = 0LLU; w < workers; ++ w)
        finished.insert(w);

    while(!finished.empty())
    {
        ll sender = Receive(-1);
#ifndef NDEBUG
        assert(sender > 0 && "Error receiving graph edges");
#endif // NDEBUG

        ll action = GetLL(sender);

        // Worker has finished processing its part
        if(action == -1)
        {
            auto repr = finished.find(sender - 1);
#ifndef NDEBUG
            assert(repr != end(finished) && "Invalid communication");
            fprintf(stderr, "Received End Of Work from %llu\n", sender);
#endif // NDEBUG
            finished.erase(repr);
            continue;
        }

        ll  from    = action,
            to      = GetLL(sender),
            cost    = GetLL(sender);

#ifndef NDEBUG
        fprintf(stderr, "Received (%lld, %lld, %lld) edge from %llu\n", from, to, cost, sender);
#endif // NDEBUG

        from    = renumber(from);
        to      = renumber(to);

        graph[from].push_back(make_pair(to, cost));
    }
}

inline
void solve(void)
{
#ifndef NDEBUG
    fprintf(stderr, "Calculating shortest paths\n");
#endif // NDEBUG

    ll distance[512];
    fill(distance, distance + 512, (1LL << 31));

    distance[0] = 0;

    ll current = 0;
#ifndef NDEBUG
    llu cnt = 0;
#endif // NDEBUG

    while(true)
    {
#ifndef NDEBUG
        assert(graph[current].size() == 2 && "Incomplete graph");
        ++ cnt;
#endif // NDEBUG

        ll g = distance[graph[current][0].first] < (1LL << 31);
        if(distance[graph[current][g].first] < (1LL << 31))
            break;

        auto &next = graph[current][g];
        distance[next.first] = min(distance[next.first], distance[current] + next.second);
        current = next.first;
    }

#ifndef NDEBUG
    assert(cnt == mapping.size() && "Incomplete graph");
    fprintf(stderr, "Printing answer\n");
#endif // NDEBUG

    for(auto q = 0; q < queries; ++ q)
    {
        ll dist = abs(distance[renumber(QueryFrom(q + 1))] - distance[renumber(QueryTo(q + 1))]);
        printf("%lld\n", min(dist, students - dist));
    }
}

/******************************************************************************
 * WORKER
 *****************************************************************************/
inline
void runWorker(void)
{
#ifndef NDEBUG
    fprintf(stderr, "Running %llu worker\n", node);
#endif // NDEBUG

    ll start;

    // Read Queries
    readQueries();

    // Read start points
    start = readStartPoints();

    // Traverse cycle + send graph edges
    traverse(start);

    // Finished
    PutLL(0, -1);
    Send(0);
}

inline
void readQueries(void)
{
#ifndef NDEBUG
    fprintf(stderr, "Reading queries\n");
#endif // NDEBUG

    for(auto q = 0; q < queries; ++ q)
    {
        edge.push_back(QueryFrom(q + 1));
        edge.push_back(QueryTo(q + 1));
    }

    sort(begin(edge), end(edge));
    edge.erase(unique(begin(edge), end(edge)), end(edge));
}

inline
ll readStartPoints(void)
{
    ll start = -1;
#ifndef NDEBUG
    fprintf(stderr, "Reading start points\n");
#endif // NDEBUG

    Receive(0);
    for(auto w = 0LL; w < nodes - 1; ++ w)
    {
        ll act = GetLL(0);
        if(w + 1 == node)
            start = act;

        stop.push_back(act);
    }

#ifndef NDEBUG
    assert(is_sorted(begin(stop), end(stop)) && unique(begin(stop), end(stop)) == end(stop) && "Communication error");
    fprintf(stderr, "Worker %llu starting in %lld point\n", node, start);
    assert(start > 0 && "Invalid start point");
#endif // NDEBUG

    return start;
}

inline
void traverse(ll start)
{
    ll previous = start,
       last     = start,
       current  = start,
       count    = 0;

    // Walking "left"
    do
    {
        ll next = FirstNeighbor(current);
        if(next == previous)
            next = SecondNeighbor(current);

        previous    = current;
        current     = next;
        ++ count;
        if(binary_search(begin(edge), end(edge), current))
            sendVertex(last, current, count);
    }
    while(!binary_search(begin(stop), end(stop), current));

    if(last != current)
        sendVertex(last, current, count);

#ifndef NDEBUG
    fprintf(stderr, "'left' went from %lld to %lld\n", start, current);
#endif // NDEBUG

    previous    = start;
    last        = start;
    current     = start;
    count       = 0;
    // Walking "right"
    do
    {
        ll next = SecondNeighbor(current);
        if(next == previous)
            next = FirstNeighbor(current);

        previous    = current;
        current     = next;
        ++ count;
        if(binary_search(begin(edge), end(edge), current))
            sendVertex(last, current, count);
    }
    while(!binary_search(begin(stop), end(stop), current));

    if(last != current)
        sendVertex(last, current, count);

#ifndef NDEBUG
    fprintf(stderr, "'right' went from %lld to %lld\n", start, current);
#endif // NDEBUG
}

inline
void sendVertex(ll &last, ll &current, ll &count)
{
#ifndef NDEBUG
    fprintf(stderr, "Sending (%lld, %lld, %lld)\n", last, current, count);
#endif // NDEBUG
    PutLL(0, last);
    PutLL(0, current);
    PutLL(0, count);
    Send(0);
    last = current;
    count = 0;
}
