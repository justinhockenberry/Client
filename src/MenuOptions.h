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
	bool login(int sockfd, char *buf, bool loggedIn);
	bool newAccount(int sockfd, char *buf, bool loggedIn);
	void addAppointment(int sockfd,char * buf);
	void deleteAppointment(int sockfd,char * buf);
	void updateAppointment(int sockfd,char * buf);

	void displayAppointTime(int sockfd,char * buf);
	void displayAppointRange(int sockfd,char * buf);

	void changeName(int sockfd,char * buf);
	void changePassword(int sockfd,char * bufvv);
	void changePhone(int sockfd,char * buf);
	void changeEmail(int sockfd,char * buf);
	void deleteUser(int sockfd,char * buf);
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
