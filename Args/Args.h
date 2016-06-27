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

/* Utility struct. Ignore this. */
struct Flag {
	std::string name;
	std::string value;
	std::vector<int> arguments;

	Flag();
	Flag(std::string input);
	void addArgument(int argNumber);
};

/* Handles arguments. */
class ArgsHandler {
private:
	std::vector<std::string> arguments;
	std::map<std::string, Flag> flags;
	std::vector<int> startargs;
	std::string execPath;
public:
	/* Constructor, just pass the main function's argument data. */
	ArgsHandler(int argc, char * argv []);

	/* Check whether a given flag was used.*/
	bool hasFlag(std::string flag) const;

	/* Methods for returning different types of flag values (-flag=value), with a default */
	std::string getFlagValueString(std::string flag, std::string dflt = "") const;
	int getFlagValueInt(std::string flag, int dflt = 0) const;
	double getFlagValueDouble(std::string flag, double dflt = 0) const;
	bool getFlagValueBool(std::string flag, bool dflt = false) const;

	/* Get the filepath the program was run as. */
	std::string getExecutionPath() const;

	/* Get all the flags that were used. */
	std::vector<std::string> getFlags() const;

	/* Get the arguments for a certain flag. */
	std::vector<std::string> getFlagArguments(std::string flag) const;

	/* Get the arguments that were given before any flag. */
	std::vector<std::string> getStartArguments() const;

	/* Get all the arguments that were used. (This excludes any used flags.)*/
	std::vector<std::string> getArguments() const;
};

/* Overload for ostreams. Prints all data in a tree-like structure. */
std::ostream& operator<<(std::ostream& os, const ArgsHandler &args);

#endif /* ARGSHANDLER_H_ */
