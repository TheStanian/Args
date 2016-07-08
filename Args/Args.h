/*
 * Quick note: this code uses the c++11 stl (specifically std::stoi and std::stod)
 * If you can't use c++11 for some reason, you could remove the getFlagValueInt(..) and getFlagValueDouble(..) methods.
 */

#ifndef ARGSHANDLER_H_
#define ARGSHANDLER_H_

#include <vector>
#include <string>
#include <map>
#include <utility>
#include <set>

/* Utility struct. Ignore this. */
struct Flag {
	std::string name;
	std::string value;
	std::vector<int> arguments;

	Flag();
	Flag(const Flag &flag);
	Flag(std::string input);
	void addArgument(int argNumber);
};

/* Handles arguments. */
class ArgsHandler {
private:
	std::vector<std::string> arguments;
	std::map<std::string, Flag> flags;
	std::vector<int> startargs;
	std::string execpath;
	std::set<std::string> checkedFlags;

	bool checkCheckedFlags = false;
public:
	/* Constructor, just pass the main function's argument data. */
	ArgsHandler(int argc, char * argv [], bool checkFlagsUsed = false);

	/* Copy ctor, default would've worked.. */
	ArgsHandler(const ArgsHandler& args);

	/* Default ctor */
	ArgsHandler();

	/* Check whether a given flag was used.*/
	bool hasFlag(std::string flag);

	/* Returns the flags that were used in the program so far if checkCheckedFlags is true. Else returns an empty set. */
	std::set<std::string> getCheckedFlags() const;

	/* Methods for returning different types of flag values (-flag=value), with a default */
	std::string getFlagValueString(std::string flag, std::string dflt = "");
	int getFlagValueInt(std::string flag, int dflt = 0);
	double getFlagValueDouble(std::string flag, double dflt = 0);
	bool getFlagValueBool(std::string flag, bool dflt = false);

	/* Get the filepath the program was run as. */
	std::string getExecutionPath() const;

	/* Get all the flags that were used. */
	std::vector<std::string> getFlags() const;

	/* Get the arguments for a certain flag. */
	std::vector<std::string> getFlagArguments(std::string flag);

	/* Get the arguments that were given before any flag. */
	std::vector<std::string> getStartArguments() const;

	/* Get all the arguments that were used. (This excludes any used flags.)*/
	std::vector<std::string> getArguments() const;

	/* Prints all currently detected flags. */
	void printCheckedFlags();

	friend std::ostream& operator<<(std::ostream& os, ArgsHandler &args);
};

/* Overload for ostreams. Prints all data in a tree-like structure. */
std::ostream& operator<<(std::ostream& os, ArgsHandler &args);

#endif /* ARGSHANDLER_H_ */
