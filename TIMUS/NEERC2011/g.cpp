/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<cstdio>
#include<string>
#include<map>
#include<vector>
#include<cctype>

// Constants
const std::string typeToString[5] = {
	"",
	"auto",
	"int",
	"real",
	"string",
};

std::map<std::string, unsigned int> typeHash,
									functionHash,
									variableHash;
unsigned int fhs = 1,
			 vhs = 1;

unsigned int declarations,
			 lines,
			 typed,
			 typedVariable[128],
			 variableType[128];

char buffer[512];
std::string parse_error,
			variableName[128];
std::vector<std::pair<std::vector<unsigned int>, unsigned int> > functions[128];

inline static const bool parseDeclaration(const char *declaration);
inline static const bool parseCode(const char *line);
inline static const unsigned int getTypeHash(const std::string type);
inline static const unsigned int getFunctionHash(const std::string name);
inline static const unsigned int getVariableHash(const std::string name);

int main(void)
{
	typeHash["auto"] = 1;
	typeHash["int"] = 2;
	typeHash["real"] = 3;
	typeHash["string"] = 4;

	scanf("%u ", &declarations);
	for(unsigned int d = 0; d < declarations; ++ d)
		parseDeclaration(fgets(buffer, 512, stdin));

	scanf("%u ", &lines);
	for(unsigned int l = 0; l < lines; ++ l)
		if(!parseCode(fgets(buffer, 512, stdin)))
		{
			printf("Error on line %u: %s\n", l + 1, parse_error.c_str());
			return 0;
		}

	for(unsigned int t = 0; t < typed; ++ t)
		printf("%s : %s\n", variableName[typedVariable[t]].c_str(), typeToString[variableType[typedVariable[t]]].c_str());

	return 0;
}

inline static const bool parseDeclaration(const char *declaration)
{
	/* state:
	 *	0 - get function name
	 *	1 - get arguments
	 *	2 - get type
	 */
	unsigned int state = 0,
				 argc = 0;
	std::string name,
				arguments[10],
				type;
	std::vector<unsigned int> args;
	for(unsigned int d = 0; declaration[d]; ++ d)
	{
		if(isspace(declaration[d]))
			continue;

		switch(state)
		{
			case 0:
				switch(declaration[d])
				{
					case '(':
						state = 1;
						break;

					default:
						name += declaration[d];
						break;
				}

				break;

			case 1:
				switch(declaration[d])
				{
					case ')':
						state = 2;
						break;

					case ',':
						++ argc;
						break;

					default:
						arguments[argc] += declaration[d];
						break;
				}

				break;

			case 2:
				if(isalpha(declaration[d]))
					type += declaration[d];

				break;
		}
	}

	if(!arguments[argc].empty())
		++ argc;

	for(unsigned int a = 0; a < argc; ++ a)
		args.push_back(getTypeHash(arguments[a]));

	functions[getFunctionHash(name)].push_back(std::make_pair(args, getTypeHash(type)));
	//printf("%s(", name.c_str());
	//for(unsigned int a = 0; a < argc; ++ a)
	//printf("%s%s", arguments[a].c_str(), a + 1 == argc?"":", ");
	//printf(") : %s\n", type.c_str());
	return false;
}

inline static const bool parseCode(const char *line)
{
	/* state:
	 *	0 - read type
	 *	1 - read name
	 *	2 - read function
	 *	3 - read arguments
	 */
	unsigned int state = 0,
				 argc = 0,
				 l = 0;
	std::string type,
				name,
				function,
				arguments[10];
	std::vector<unsigned int> args;

	while(isspace(line[l]))
		++ l;

	for(; line[l]; ++ l)
	{
		if(state && isspace(line[l]))
			continue;

		switch(state)
		{
			case 0:
				if(isspace(line[l]))
					state = 1;

				else
					type += line[l];

				break;

			case 1:
				switch(line[l])
				{
					case '=':
						state = 2;
						break;

					default:
						name += line[l];
						break;
				}

				break;

			case 2:
				switch(line[l])
				{
					case '(':
						state = 3;
						break;

					default:
						function += line[l];
						break;
				}

				break;

			case 3:
				switch(line[l])
				{
					case ')':
						state = 2;
						break;

					case ',':
						++ argc;
						break;

					default:
						arguments[argc] += line[l];
						break;
				}

				break;
		}
	}

	if(!arguments[argc].empty())
		++ argc;

	unsigned int nHash = getVariableHash(name),
				 fHash = getFunctionHash(function);
	if(variableType[nHash])
	{
		 parse_error = "Double declaration";
		 return false;
	}

	for(unsigned int a = 0; a < argc; ++ a)
	{
		if(!variableType[getVariableHash(arguments[a])])
		{
			parse_error = "Unknown variable";
			return false;
		}

		args.push_back(variableType[getVariableHash(arguments[a])]);
	}

	variableType[nHash] = getTypeHash(type);
	unsigned int f;
	for(f = 0; f < functions[fHash].size(); ++ f)
	{
		if(args.size() != functions[fHash][f].first.size())
			continue;
		
		bool good = true;
		for(unsigned int a = 0; good && a < args.size(); ++ a)
			if(args[a] != functions[fHash][f].first[a])
				good = false;

		if(good)
			break;
	}

	if(f == functions[fHash].size())
	{
		parse_error = "No such function";
		return false;
	}

	if(variableType[nHash] == 1)
	{
		variableType[nHash] = functions[fHash][f].second;
		typedVariable[typed ++] = nHash;
	}

	if(variableType[nHash] != functions[fHash][f].second)
	{
		parse_error = "Invalid initialization";
		return false;
	}

	//printf("%s %s = %s(", type.c_str(), name.c_str(), function.c_str());
	//for(unsigned int a = 0; a < argc; ++ a)
	//printf("%s%s", arguments[a].c_str(), a + 1 == argc?"":", ");
	//
	//puts(")");
	return true;
}

inline static const unsigned int getTypeHash(const std::string type)
{
	return typeHash[type];
}

inline static const unsigned int getFunctionHash(const std::string name)
{
	if(!functionHash[name])
		functionHash[name] = fhs ++;

	return functionHash[name];
}

inline static const unsigned int getVariableHash(const std::string name)
{
	if(!variableHash[name])
	{
		variableHash[name] = vhs;
		variableName[vhs ++] = name;
	}

	return variableHash[name];
}
