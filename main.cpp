/*
 * Quick note: this code uses the c++11 stl (specifically std::stoi and std::stod)
 * If you can't use c++11 for some reason, you could remove the getFlagValueInt(..) and getFlagValueDouble(..) methods.
 */

#include <iostream>

#include "Args/Args.h"

int main(int argc, char *argv[]) {
	/* It's as simple as creating an instance of ArgsHandler! */
	ArgsHandler args(argc, argv, true);

	/* Printing all args could be useful for debugging purposes. */
	std::cout << args << std::endl;

	// Checking for flag "flag" (-flag)
	if (args.hasFlag("flag")) {
		std::cout << "We have a flag called flag!" << std::endl;
	}

	/* Checking for a flag's value (-flag=value) */
	if (args.hasFlag("flag")) {
		std::cout << "It even has a value of \"" << args.getFlagValueString("flag") << "\"!" << std::endl;
	}

	/* No need to ensure the flag actually has been set, as you can easily provide a default! */
	if (!args.hasFlag("flag")) {
		std::cout << "There is no flag called flag, but we can still get the default value of \""
				<< args.getFlagValueString("flag", "_defaultValue") << "\"."<< std::endl;
	}
	/*
	 * (I have also provided methods for doubles, ints and bools.
	 *  I decided not to go with templates here, as implementation for every case is different, and templates are messy.)
	 */

	/* You can get the arguments after a specific flag (-flag in this case) like so: */
	std::vector<std::string> argsAfterFlag = args.getFlagArguments("flag");
	std::cout << "arguments after flag \"flag\": ";
	for (std::string &s:argsAfterFlag) {
		std::cout << s << "; ";
	}
	std::cout << std::endl;

	/* In some cases it can be useful to check which flags you've checked for so far.
	 * You can get them as a std::set<std::string> or printed to cout.
	 */
	args.printCheckedFlags();

	return 0;
}
