/* 2015
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <vector>
#include <unordered_map>

typedef long long int lld;
typedef std::unordered_map<int, lld> Prices;

lld bestPrice(const int _center);
Prices findPrices(int v);

const int MAX_STATIONS = 524288;

bool processed[MAX_STATIONS];
int center;
int end;
int foreign;
int width[MAX_STATIONS];
int start;
int stations;
std::vector<int> tree[MAX_STATIONS];

int main(void)
{
    scanf("%d %d", &stations, &foreign);
    for(int s = 1; s < stations; ++ s)
    {
        scanf("%d %d", &start, &end);
        -- start;
        -- end;
        tree[start].push_back(end);
        tree[end].push_back(start);
    }

    for(int f = 0; f < foreign; ++ f)
        scanf("%d", &width[f]);

    // TODO: find tree center
    center = foreign + (stations - foreign) / 2;

    printf("%lld\n", bestPrice(center));
    return 0;
}

lld bestPrice(const int _center)
{
    lld bestPrice = -1;

    for(const auto &price: findPrices(_center))
        if(bestPrice == -1 || price.second < bestPrice)
            bestPrice = price.second;

    return bestPrice;
}

Prices findPrices(int v)
{
    Prices result;
    std::vector<Prices> children;

    processed[v] = true;
    for(const int &child: tree[v])
    {
        if(processed[child]) continue;
        children.push_back(findPrices(child));
    }

    if(children.size() == 0)
        result[width[v]] = 0;

    if(children.size() == 1)
        result = children[0];

    for(const Prices &prices: children)
        for(const auto &price: prices)
            result[price.first] = -1;

    for(const Prices &prices: children)
        for(const auto &price: prices)
        {
            lld actualPrice = 0;
            for(const Prices &mergePrices: children) if(&mergePrices != &prices)
            {
                lld bestPrice = -1;
                for(const auto &mergePrice: mergePrices)
                    if(bestPrice == -1 || bestPrice > std::abs(price.first - mergePrice.first) + price.second + mergePrice.second)
                        bestPrice = std::abs(price.first - mergePrice.first) + price.second + mergePrice.second;

                actualPrice += bestPrice;
                if(result[price.first] != -1 && actualPrice > result[price.first])
                    break;
            }

            if(result[price.first] == -1 || actualPrice < result[price.first])
                result[price.first] = actualPrice;
        }

    return result;
}
