/* 2015
 * Maciej Szeptuch
 * II UWr
 */
#include <algorithm>
//#include <cassert>
#include <cstdio>
#include <vector>
#include <list>

const int MAX_COMPONENTS    = 1048576;
const int MAX_CYCLE_SIZE    = 1048576;
const int MAX_PEOPLE        = 1048576;

char cycle[MAX_CYCLE_SIZE];
int component[MAX_COMPONENTS];
int components;
int cycleLength;
int length[MAX_COMPONENTS];
int minimal[MAX_CYCLE_SIZE];
int money[MAX_PEOPLE];
int people;
int position[MAX_CYCLE_SIZE];
int relative[MAX_CYCLE_SIZE];
int result[MAX_COMPONENTS];
long long int best = -1;
std::vector<std::pair<int, int>> values[MAX_COMPONENTS]; // value, position

void markComponent(const int start, const int _component);

int main(void)
{
    scanf("%d", &people);
    for(int p = 0; p < people; ++ p)
        scanf("%d", &money[p]);

    scanf("%d %s", &cycleLength, cycle);
    for(int c = 0; c < cycleLength; ++ c)
    {
        if(component[c])
            continue;

        markComponent(c, ++ components);
    }

    for(int p = 0; p < people; ++ p)
    {
        int _cycle      = p % cycleLength;
        int &_component = component[_cycle];
        int &_length    = length[_component];
        int &_minimal   = minimal[_cycle];
        int &_money     = money[p];
        int &_position  = position[_cycle];
        int &_relative  = relative[_cycle];
        int &_result    = result[_component];

        if(_result >= 0 && -_minimal < _money)
            continue;

        long long int played = 0L;
        if(_result < 0 && -_minimal < _money) // play full cycles
        {
            played = (_money + _minimal - _result - 1) / -_result;
            _money += _result * played;
            //fprintf(stderr, "%d: played=%lld\n", p, played);
            played *= 1L * people * _length;
        }

        //fprintf(stderr, "%d: money=%d minimal=%d result=%d played=%lld\n", p, _money, _minimal, _result, played);
        //assert(_money <= -_minimal);
        if(_money) // part of the cycle
        {
            auto it = std::upper_bound(
                std::begin(values[_component]),
                std::end(values[_component]),
                std::make_pair(-_money + _relative, _position));
            //assert(it != std::end(values[_component]));
            int steps = it->second - _position - 1;
            //for(const auto &value: values[_component])
            //    fprintf(stderr, "(%d, %d) ", value.first, value.second);
            //fputs("", stderr);
            //fprintf(stderr, "%d: wanted=(%d, %d) steps=%d\n", p, -_money + _relative, _position, steps);
            played += 1L * people * steps + 1L;
        }

        played += p;
        //fprintf(stderr, "%d: money=%d minimal=%d played=%lld\n", p, _money, _minimal, played);
        if(best == -1 || played < best)
            best = played;
    }

    printf("%lld\n", best);
    return 0;
}

void markComponent(const int start, const int _component)
{
    auto &_values   = values[_component];
    int &_length    = length[_component];
    int &_result    = result[_component];
    std::list<std::pair<int, int>> window;
    for(int c = start; !component[c]; c = (c + people) % cycleLength)
    {
        component[c] = _component;
        position[c] = _length ++;
        relative[c] = _result;
        //fprintf(stderr, "%d: component=%d position=%d relative=%d\n", c, component[c], position[c], relative[c]);
        _values.push_back({_result, position[c]});
        while(!window.empty() && window.back().first >= _result)
            window.pop_back();

        window.emplace_back(_result, position[c]);
        _result += cycle[c] == 'W' ? 1 : -1;
    }

    int c = start;
    int _position = length[_component];
    int _value = _result;
    do
    {
        while(!window.empty() && window.back().first >= _value)
            window.pop_back();

        window.emplace_back(_value, _position - 1);
        minimal[c] = window.front().first - relative[c];
        //fprintf(stderr, "%d: position=%d front=(%d,%d) minimal=%d\n", c, _position, window.front().first, window.front().second, minimal[c]);
        if(_position - cycleLength >= window.front().second)
            window.pop_front();

        _values.push_back({_value, _position});
        _value += cycle[c] == 'W' ? 1 : -1;
        _position ++;
        c = (c + people) % cycleLength;
    }
    while(c != start);

    std::sort(std::begin(_values), std::end(_values));
}
