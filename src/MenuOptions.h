/*
 * MenuOptions.h
 *
 *  Created on: Mar 24, 2018
 *      Author: justin
 */



#ifndef CLIENT_MENUOPTIONS_H
#define CLIENT_MENUOPTIONS_H
#include <string>
#include <regex>
using std::string;

class MenuOptions {
private:

public:
	string getUserName();
	string getPassword();
	string getName();
	string getEmail();
	string getPhone();
	string getTimeDate(string);
	string getMemo(string);
	string getPlace(string);


};
#endif //CLIENT_MENUOPTIONS_H
