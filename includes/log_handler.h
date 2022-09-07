#ifndef LOG_HANDLER_H
#define LOG_HANDLER_H
#include <iostream>
#include <string>

static std::string preMessage = "";

inline void printError(std::string message) {
	if (message != preMessage) {
		std::cout << "Error Message: " << message << "\n";
		preMessage = message;
	}
}

inline void printInfo(std::string message) {
	if (message != preMessage) {
		std::cout << "Info Message: " << message << "\n";
		preMessage = message;
	}
}
#endif