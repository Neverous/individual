/* 2013
 * Maciej Szeptuch
 * II UWr
 */
#include <cstdio>
#include <algorithm>

const long long int MOD = 1000000007LL;

long long int tests,
    numbers,
    subset,
    number[16384],
    factorial[16384];

inline std::pair<long long int, long long int> extEuclides(const long long int &a, const long long int &b);
inline void preprocess(void);
inline long long int inverse(const long long int &a);
inline long long int newton(const long long int &n, const long long int &k);
inline long long int solve(const long long int &n, const long long int &k);

int main(void)
{
    preprocess();
    scanf("%lld", &tests);
    for(long long int t = 0; t < tests; ++ t)
    {
        scanf("%lld %lld", &numbers, &subset);
        for(long long int n = 0; n < numbers; ++ n)
        {
            scanf("%lld", &number[n]);
            number[n] %= MOD;
        }

        printf("Case #%lld: %lld\n", t + 1, solve(numbers, subset));
    }

    return 0;
}

inline void preprocess(void)
{
    factorial[0] = 1;
    for(long long int n = 1; n < 16384; ++ n)
        factorial[n] = factorial[n - 1] * n % MOD;
}

inline long long int inverse(const long long int &a)
{
    return extEuclides(a, MOD).first;
}

inline long long int newton(const long long int &n, const long long int &k)
{
    return factorial[n] * inverse(factorial[k] * factorial[n - k]) % MOD;
}

inline long long int solve(const long long int &n, const long long int &k)
{
    long long int result = 0;
    std::sort(number, number + numbers);
    for(long long int i = 1; i <= n - k + 1; ++ i)
        result = (result + number[numbers - i] * newton(n - i, k - 1)) % MOD;

    return result;
}

inline std::pair<long long int, long long int> extEuclides(const long long int &a, const long long int &b)
{
    std::pair<long long int, long long int> result(1, 0);
    if(!b)
        return result;

    result = extEuclides(b, a % b);
    long long int temp = result.first;
    result.first = result.second;
    result.second = (temp - result.second * (a / b)) % MOD;
    if(result.second < 0)
    {
        temp = (result.second - MOD + 1) / MOD;
        result.second -= MOD * temp;
    }

    return result;
}
