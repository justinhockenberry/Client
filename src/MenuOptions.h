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
	bool login(int sockfd, char *buffer, bool loggedIn);
	bool newAccount(int sockfd, char *buffer, bool loggedIn);
	void addAppointment(int sockfd,char * buffer);
	void deleteAppointment(int sockfd,char * buffer);
	void updateAppointment(int sockfd,char * buffer);

	void displayAppointTime(int sockfd,char * buffer);
	void displayAppointRange(int sockfd,char * buffer);

	void changeName(int sockfd,char * buffer);
	void changePassword(int sockfd,char * buffervv);
	void changePhone(int sockfd,char * buffer);
	void changeEmail(int sockfd,char * buffer);
	void deleteUser(int sockfd,char * buffer);
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
