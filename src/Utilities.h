/*
 * Utilities.h
 *
 *  Created on: Mar 24, 2018
 *      Author: justin
 */

#include <string>
#include <regex>

#ifndef CLIENT_UTILITIES_H
#define CLIENT_UTILITIES_H

std::string getUserName();
std::string getPassword();
std::string getName();
std::string getEmail();
std::string getPhone();
std::string getTimeDate(std::string);
//std::string getTime(std::string);
std::string getMemo(std::string);
std::string getPlace(std::string);

#endif //CLIENT_UTILITIES_H
