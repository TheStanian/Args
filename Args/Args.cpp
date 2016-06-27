#include <string>
#include <algorithm>
#include <iostream>
#include "Args.h"

ArgsHandler::ArgsHandler(int argc, char * argv []) {
	std::string lastFlag = "";
	execPath = std::string(argv[0]);
	for (int i = 1; i < argc; ++i) {
		std::string current(argv[i]);
		if (current.at(0) == '-') {
			std::string fname;
			if (current.find('=') != current.npos) {
				fname = current.substr(1, current.find_first_of("=")-1);
			} else {
				fname = current.substr(1);
			}
			flags.insert(std::pair<std::string, Flag>(fname, Flag(current.substr(1))));
			lastFlag = fname;
		} else {
			arguments.push_back(current);
			if (lastFlag != "") {
				flags[lastFlag].addArgument(arguments.size()-1);
			} else {
				startargs.push_back(arguments.size()-1);
			}
		}
	}
}

bool ArgsHandler::hasFlag(std::string flag) const {
	return (flags.find(flag) != flags.end());
}

std::string ArgsHandler::getFlagValueString(std::string flag, std::string dflt) const {
	if (hasFlag(flag)) {
		return flags.find(flag)->second.value;
	} else {
		return dflt;
	}
}

int ArgsHandler::getFlagValueInt(std::string flag, int dflt) const {
	if (hasFlag(flag)) {
		std::string flgstr = flags.find(flag)->second.value;
		int ret = dflt;
		try {
			ret = std::stoi(flgstr);
		} catch (std::invalid_argument &e) {
			// ret is still dflt, so all good.
		}
		return ret;
	} else {
		return dflt;
	}
}

double ArgsHandler::getFlagValueDouble(std::string flag, double dflt) const {
	if (hasFlag(flag)) {
		std::string flgstr = flags.find(flag)->second.value;
		double ret = dflt;
		try {
			ret = std::stod(flgstr);
		} catch (std::invalid_argument &e) {
			// ret is still dflt, so all good.
		}
		return ret;
	} else {
		return dflt;
	}
}

bool ArgsHandler::getFlagValueBool(std::string flag, bool dflt) const {
	if (hasFlag(flag)) {
			std::string flgstr = flags.find(flag)->second.value;
			bool ret = dflt;
			if (flgstr == "true") {
				ret = true;
			} else if (flgstr == "false") {
				ret = false;
			}
			return ret;
		} else {
			return dflt;
		}
}

std::string ArgsHandler::getExecutionPath() const {
	return execPath;
}

std::vector<std::string> ArgsHandler::getFlagArguments(std::string flag) const {
	std::vector<std::string> flagArguments;
	if (!hasFlag(flag)) {
		return flagArguments;
	}

	for (int arg:(flags.find(flag)->second.arguments)) {
		flagArguments.push_back(arguments[arg]);
	}

	return flagArguments;
}

std::vector<std::string> ArgsHandler::getStartArguments() const {
	std::vector<std::string> startArguments;

	for (int arg:startargs) {
		startArguments.push_back(arguments[arg]);
	}

	return startArguments;
}

std::vector<std::string> ArgsHandler::getArguments() const {
	return arguments;
}

std::vector<std::string> ArgsHandler::getFlags() const {
	std::vector<std::string> strflags;
	for (auto pair:flags) {
		strflags.push_back(pair.first);
	}
	return strflags;
}

Flag::Flag(std::string input) {
	if (input.find("=") != input.npos) {
	name = input.substr(0, input.find_first_of("="));
	value = input.substr(input.find_first_of("=")+1);
	} else {
		name = input;
		value = "";
	}
}

Flag::Flag() {
	name = "";
	value = "";
}

void Flag::addArgument(int argNumber) {
	arguments.push_back(argNumber);
}

std::ostream& operator<<(std::ostream& os, const ArgsHandler &args) {
	os << "-----------------------------" << std::endl
			<< "This program was run as:" << std::endl << "    " << args.getExecutionPath() << std::endl
			<< "with the following flags and arguments:" << std::endl;
	if (args.getStartArguments().size() > 0) {
		os << "    flagless arguments:" << std::endl;
		for (std::string arg:args.getStartArguments()) {
			os << "        " << arg << std::endl;
		}
	}
	for (std::string flag:args.getFlags()) {
		os << "    flag \"" << flag << "\"";
		std::string flval = args.getFlagValueString(flag);
		if (flval != "") {
			os << " with value \"" << flval << "\"";
		}

		std::vector<std::string> flargs = args.getFlagArguments(flag);
		if (flargs.size() > 0) {
			os << ":";
		}

		os << std::endl;

		for (std::string arg:args.getFlagArguments(flag)) {
			os << "        " << arg << std::endl;
		}
	}
	os << "-----------------------------";
	return os;
}
