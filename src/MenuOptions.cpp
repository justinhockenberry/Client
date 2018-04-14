/*
 * MenuOptions.cpp
 *
 *  Created on: Mar 24, 2018
 *      Author: justin
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <regex>
#include <sstream>

#include "MenuOptions.h"

using std::cout;
using std::cin;
using std::regex;
using std::stringstream;

bool MenuOptions::login(int sockfd, char *buffer, bool loggedIn) {

	long bytes;
	string input = "";

	cout << "Enter username\n";
	getline(cin, input);

	send(sockfd, input.c_str(), 127, 0);


	input = "";

	cout << "Enter password\n";
	getline(cin, input);
	send(sockfd, input.c_str(), 127, 0);

	bytes = recv(sockfd, buffer, 127, 0);
	buffer[bytes] = '\0';
	string success = buffer;
	if(!success.compare("Success")){

		loggedIn = true;
		cout << "Login successful\n";
	}
	else{
		cout << "Login failure please retry\n";
	}
	return loggedIn;
}
bool MenuOptions::newAccount(int sockfd, char *buffer, bool loggedIn) {
	bool exists =true;
	string input;
	long bytes;
	while(exists){

		string input = "";
		cout << "Enter username\n";
		getline(cin, input);

		send(sockfd, input.c_str(), 127, 0);

		bytes = recv(sockfd, buffer, 127, 0);
		buffer[bytes] = '\0';
		string success = buffer;
		if(!success.compare("New Username accepted")){
			exists = false;
		}
		else{
			cout << "Username already exists\n";
		}
	}

	input = "";
	cout << "Enter password\n";
	getline(cin, input);
	send(sockfd, input.c_str(), 127, 0);

	input = "";
	cout << "Enter name\n";
	getline(cin, input);
	send(sockfd, input.c_str(), 127, 0);


	input = "";
	cout << "Enter your email\n";
	getline(cin, input);
	send(sockfd, input.c_str(), 127, 0);

	input = "";
	cout << "Enter 10 digit phone number\n";
	getline(cin, input);
	send(sockfd, input.c_str(), 127, 0);

	return loggedIn = true;
}
void MenuOptions::addAppointment(int sockfd, char *buffer) {
	long bytes;

	if ((bytes = recv(sockfd, buffer, 512, 0)) == -1) {
		perror("recv");
		exit(1);
	}
	buffer[bytes] = '\0';
	printf("All appointments: %s\n", buffer);
	string beginTime = this->getTimeDate("");
	string endTime = this->getTimeDate("4");
	string memo = this->getMemo("");
	string place = this->getPlace("");


	bool conflict = true;
	while (conflict){
		send(sockfd, beginTime.c_str(), 127, 0);
		send(sockfd, endTime.c_str(), 127, 0);

		bytes = recv(sockfd, buffer, 127, 0);
		buffer[bytes] = '\0';
		string success = buffer;
		if(!success.compare("Success")){
			conflict = false;
		}else{
			cout << "Already appointment at same time\n";
			beginTime = this->getTimeDate("");
			endTime = this->getTimeDate("");
		}
	}

	send(sockfd, memo.c_str(), 127, 0);
	send(sockfd, place.c_str(), 127, 0);
}
void MenuOptions::deleteAppointment(int sockfd,char * buffer) {
	long bytes;

	if ((bytes = recv(sockfd, buffer, 512, 0)) == -1) {
		perror("recv");
		exit(1);
	}
	buffer[bytes] = '\0';
	printf("[Server]: %s\n", buffer);
	string beginTime = this->getTimeDate("1");
	send(sockfd, beginTime.c_str(), 127, 0);
}
void MenuOptions::updateAppointment(int sockfd,char * buffer) {
	long bytes;
	if ((bytes = recv(sockfd, buffer, 512, 0)) == -1) {
		perror("recv");
		exit(1);
	}
	buffer[bytes] = '\0';
	printf("[Server]: %s\n", buffer);
	string oldBeginDate = this->getTimeDate("1");
	string newBeginDate = this->getTimeDate("2");
	string newEndDate = this->getTimeDate("4");
	string newMemo = this->getMemo("2");
	string newPlace = this->getPlace("2");

	bool conflict = true;
	while (conflict){
		send(sockfd, newBeginDate.c_str(), 127, 0);
		send(sockfd, newEndDate.c_str(), 127, 0);

		bytes = recv(sockfd, buffer, 127, 0);
		buffer[bytes] = '\0';
		string success = buffer;
		if(!success.compare("Update successful")){
			conflict = false;
		}else{
			cout << "Already an appointment at same time\n";
			newBeginDate = this->getTimeDate("2");
			newEndDate = this->getTimeDate("2");
		}
	}
	send(sockfd, newMemo.c_str(), 127, 0);
	send(sockfd, newPlace.c_str(), 127, 0);
	send(sockfd, oldBeginDate.c_str(), 127, 0);
}
void MenuOptions::displayAppointTime(int sockfd,char * buffer) {
	string beginTime = this->getTimeDate("1");
	send(sockfd, beginTime.c_str(), 127, 0);
}
void MenuOptions::displayAppointRange(int sockfd,char * buffer) {
	long bytes;
	string startDate = this->getTimeDate("3");
	string endDate = this->getTimeDate("4");

	cout << startDate << " " << endDate << "\n";

	send(sockfd, startDate.c_str(), 127, 0);
	send(sockfd, endDate.c_str(), 127, 0);

	bytes = recv(sockfd, buffer, 512, 0);
	buffer[bytes] = '\0';
	printf("[Server]: %s\n", buffer);
}
void MenuOptions::changeName(int sockfd,char * buffer) {
	string input;
	cout << "Enter name\n";
	getline(cin, input);
	send(sockfd, input.c_str(), 127, 0);
}
void MenuOptions::changePassword(int sockfd,char * buffer) {
	string input = "";
	cout << "Enter password\n";
	getline(cin, input);
	send(sockfd, input.c_str(), 127, 0);
}
void MenuOptions::changePhone(int sockfd,char * buffer) {
	string input = "";
	cout << "Enter 10 digit phone number\n";
	getline(cin, input);
	send(sockfd, input.c_str(), 127, 0);
}
void MenuOptions::changeEmail(int sockfd,char * buffer) {
	string input = "";
	cout << "Enter your email\n";
	getline(cin, input);
	send(sockfd, input.c_str(), 127, 0);
}
void MenuOptions::deleteUser(int sockfd,char * buffer) {
	string input = "";
	cout << "Delete user this user account Y/N\n";
	getline(cin, input);
	send(sockfd, input.c_str(), 127, 0);
	if(!input.compare("Y") || !input.compare("y")){
		close(sockfd);
	}
}
string MenuOptions::getUserName() {

	string input;
	cout << "Enter username\n";
	getline(cin, input);
	return input;
}

string MenuOptions::getPassword() {
	string input;
	cout << "Enter password\n";
	getline(cin, input);
	return input;
}

string MenuOptions::getTimeDate(string number) {
	bool formatCheck = false;
	string input;
	while(!formatCheck){
		if(!number.compare("1")){
			cout << "Enter current appointment time (24 hour) & date in the format hh:mm mm/dd/yyyy\n";
		}else if(!number.compare("2")){
			cout << "Enter updated new appointment time (24 hour) & date in the format hh:mm mm/dd/yyyy\n";
		}else if(!number.compare("3")){
			cout << "Enter the starting time (24 hour) & date in the format hh:mm mm/dd/yyyy\n";
		}else if(!number.compare("4")){
			cout << "Enter the ending time (24 hour) & date in the format hh:mm mm/dd/yyyy\n";
		}else {
			cout << "Enter appointment time (24 hour) & date in the format hh:mm mm/dd/yyyy\n";
		}
		getline(cin, input);
		formatCheck = checkFormat(input);
	}
	return input;
}
bool MenuOptions::checkFormat(string timeDate) {
	bool formatCheck = false;
	stringstream ss0;
	stringstream ss1;
	stringstream ss2;
	stringstream ss3;
	string colon;
	string space;
	string slash00;
	string slash01;

	ss0 << timeDate[2];
	ss0 >> colon;
	ss1 << timeDate[5];
	ss1 >> space;
	ss2 << timeDate[8];
	ss2 >> slash00;
	ss3 << timeDate[11];
	ss3 >> slash01;

	if(!colon.compare(":"))
	{
		if(!space.compare("")){
			if(!slash00.compare("/")){
				if(!slash01.compare("/")){
					formatCheck = true;
				}
			}
		}
	}
	if(!formatCheck){
		cout << "Time & date must be in hh:mm mm/dd/yyyy format please try again" << '\n';
	}



	return formatCheck;
}

string MenuOptions::getMemo(string number) {

	string input;

	if(!number.compare("1")){
		cout << "Please enter old appointment memo\n";
	}else if(!number.compare("2")){
		cout << "Please enter updated appointment memo\n";
	}else {
		cout << "Please enter new appointment memo\n";
	}
	getline(cin, input);

	return input;
}

string MenuOptions::getPlace(string number) {

	string input;
	if(!number.compare("1")){
		cout << "Please enter old appointment place\n";
	}else if(!number.compare("2")){
		cout << "Please enter updated appointment place\n";
	}else {
		cout << "Please enter new appointment place\n";
	}
	getline(cin, input);

	return input;
}

string getName() {
	string input;
	cout << "Please enter name\n";
	getline(cin, input);

	return input;
}

string MenuOptions::getEmail() {
	string input;
	cout << "Please enter your email\n";
	getline(cin, input);

	return input;
}

string MenuOptions::getPhone() {
	string input;
	cout << "Please enter phone consisting of only 10 digits\n";
	getline(cin, input);

	return input;
}

