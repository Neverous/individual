/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<string>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	integer;
std::string input;

inline static const std::string readString(int maxLength = 1024);
inline static const int AlienToInteger(const std::string number, const std::string base);
inline static const std::string IntegerToAlien(const int number, const std::string base);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		input = readString();
		integer = AlienToInteger(input, readString());
		printf("Case #%d: %s\n", t + 1, IntegerToAlien(integer, readString()).c_str());
	}

	return 0;
}

inline static const std::string readString(int maxLength)
{
	char buffer[maxLength];
	scanf("%s", buffer);

	return std::string(buffer);
}

inline static const int AlienToInteger(const std::string number, const std::string base)
{
	int repr[256] = {0},
		result = 0;

	for(int b = 0; base[b]; ++ b)
		repr[(int)base[b]] = b;

	for(int n = number.size() - 1, b = 1; n >= 0; -- n, b *= base.size())
		result += b * repr[(int)number[n]];

	return result;
}

inline static const std::string IntegerToAlien(const int number, const std::string base)
{
	std::string result;
	for(int temp = number; temp > 0; temp /= base.size())
		result += base[temp % base.size()];

	std::reverse(result.begin(), result.end());
	return result;
}
