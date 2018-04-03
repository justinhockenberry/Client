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

#include "MenuOptions.h"



bool MenuOptions::login(int sockfd, char *buf, bool loggedIn) {

	long numbytes;
	std::string input = "";

	std::cout << "Please enter username\n";
	std::getline(std::cin, input);

	send(sockfd, input.c_str(), 127, 0);


	input = "";

	std::cout << "Please enter password\n";
	std::getline(std::cin, input);
	send(sockfd, input.c_str(), 127, 0);

	numbytes = recv(sockfd, buf, 127, 0);
	buf[numbytes] = '\0';
	std::string success = buf;
	if(!success.compare("Success")){

		loggedIn = true;
		std::cout << "Log in successful\n";
	}
	else{
		std::cout << "Log in failure please retry\n";
	}
	return loggedIn;
}
bool MenuOptions::newAccount(int sockfd, char *buf, bool loggedIn) {
	bool exists =true;
	string input;
	long numbytes;
	while(exists){

		std::string input = "";
		std::cout << "Please enter username\n";
		std::getline(std::cin, input);

		send(sockfd, input.c_str(), 127, 0);

		numbytes = recv(sockfd, buf, 127, 0);
		buf[numbytes] = '\0';
		std::string success = buf;
		if(!success.compare("Success")){
			exists = false;
		}
		else{
			std::cout << "Username already exists\n";
		}
	}

	input = "";
	std::cout << "Please enter password\n";
	std::getline(std::cin, input);
	send(sockfd, input.c_str(), 127, 0);

	input = "";
	std::cout << "Please enter name\n";
	std::getline(std::cin, input);
	send(sockfd, input.c_str(), 127, 0);


	input = "";
	std::cout << "Please enter your email\n";
	std::getline(std::cin, input);
	send(sockfd, input.c_str(), 127, 0);

	input = "";
	std::cout << "Please enter phone consisting of only 10 digits\n";
	std::getline(std::cin, input);
	send(sockfd, input.c_str(), 127, 0);
	//			validated = true;
	return loggedIn = true;
}
void MenuOptions::addAppointment(int sockfd, char *buf) {
	long numbytes;

	if ((numbytes = recv(sockfd, buf, 512, 0)) == -1) {
		perror("recv");
		exit(1);
	}
	buf[numbytes] = '\0';
	printf("[Server]: %s\n", buf);
	std::string beginTime = this->getTimeDate("NEW");
	std::string endTime = this->getTimeDate("END");
	std::string memo = this->getMemo("NEW");
	std::string place = this->getPlace("NEW");


	bool conflict = true;
	while (conflict){
		send(sockfd, beginTime.c_str(), 127, 0);
		send(sockfd, endTime.c_str(), 127, 0);

		numbytes = recv(sockfd, buf, 127, 0);
		buf[numbytes] = '\0';
		std::string success = buf;
		if(!success.compare("Success")){
			conflict = false;
		}else{
			std::cout << "There is already an appointment at that time please reschedule\n";
			beginTime = this->getTimeDate("NEW");
			endTime = this->getTimeDate("NEW");
		}
	}

	send(sockfd, memo.c_str(), 127, 0);
	send(sockfd, place.c_str(), 127, 0);
}
void MenuOptions::deleteAppointment(int sockfd,char * buf) {
	long numbytes;

	if ((numbytes = recv(sockfd, buf, 512, 0)) == -1) {
		perror("recv");
		exit(1);
	}
	buf[numbytes] = '\0';
	printf("[Server]: %s\n", buf);
	std::string beginTime = this->getTimeDate("OLD");
	send(sockfd, beginTime.c_str(), 127, 0);
}
void MenuOptions::updateAppointment(int sockfd,char * buf) {
	long numbytes;
	if ((numbytes = recv(sockfd, buf, 512, 0)) == -1) {
		perror("recv");
		exit(1);
	}
	buf[numbytes] = '\0';
	printf("[Server]: %s\n", buf);
	std::string oldBeginDate = this->getTimeDate("OLD");
	std::string newBeginDate = this->getTimeDate("UPDATE");
	std::string newEndDate = this->getTimeDate("END");
	std::string newMemo = this->getMemo("UPDATE");
	std::string newPlace = this->getPlace("UPDATE");

	bool conflict = true;
	while (conflict){
		send(sockfd, newBeginDate.c_str(), 127, 0);
		send(sockfd, newEndDate.c_str(), 127, 0);

		numbytes = recv(sockfd, buf, 127, 0);
		buf[numbytes] = '\0';
		std::string success = buf;
		if(!success.compare("Success")){
			conflict = false;
		}else{
			std::cout << "There is already an appointment at that time please reschedule\n";
			newBeginDate = this->getTimeDate("UPDATE");
			newEndDate = this->getTimeDate("UPDATE");
		}
	}
	send(sockfd, newMemo.c_str(), 127, 0);
	send(sockfd, newPlace.c_str(), 127, 0);
	send(sockfd, oldBeginDate.c_str(), 127, 0);
}
void MenuOptions::displayAppointTime(int sockfd,char * buf) {
	std::string beginTime = this->getTimeDate("OLD");
	send(sockfd, beginTime.c_str(), 127, 0);
}
void MenuOptions::displayAppointRange(int sockfd,char * buf) {
	long numbytes;
	std::string startDate = this->getTimeDate("START");
	std::string endDate = this->getTimeDate("END");

	std::cout << startDate << " " << endDate << "\n";

	send(sockfd, startDate.c_str(), 127, 0);
	send(sockfd, endDate.c_str(), 127, 0);

	numbytes = recv(sockfd, buf, 512, 0);
	buf[numbytes] = '\0';
	printf("[Server]: %s\n", buf);
}
void MenuOptions::changeName(int sockfd,char * buf) {
	std::string input;
	std::cout << "Please enter name\n";
	std::getline(std::cin, input);
	send(sockfd, input.c_str(), 127, 0);
}
void MenuOptions::changePassword(int sockfd,char * buf) {
	std::string input = "";
	std::cout << "Please enter password\n";
	std::getline(std::cin, input);
	send(sockfd, input.c_str(), 127, 0);
}
void MenuOptions::changePhone(int sockfd,char * buf) {
	std::string input = "";
	std::cout << "Please enter phone consisting of only 10 digits\n";
	std::getline(std::cin, input);
	send(sockfd, input.c_str(), 127, 0);
}
void MenuOptions::changeEmail(int sockfd,char * buf) {
	std::string input = "";
	std::cout << "Please enter your email\n";
	std::getline(std::cin, input);
	send(sockfd, input.c_str(), 127, 0);
}
void MenuOptions::deleteUser(int sockfd,char * buf) {
	std::string input = "";
	std::cout << "Are you sure Y/N\n";
	std::getline(std::cin, input);
	send(sockfd, input.c_str(), 127, 0);
	if(!input.compare("Y") || !input.compare("y")){
		close(sockfd);
	}
}
std::string MenuOptions::getUserName() {
	bool validated = false;
	std::string input;
	while(!validated){
		std::cout << "Please enter username\n";
		std::getline(std::cin, input);
		if (input.find(";") != std::string::npos) {
			std::cout << "Username cannot contain the ; character" << '\n';
		}else{
			validated = true;
		}
	}
	return input;
}

std::string MenuOptions::getPassword() {
	bool validated = false;
	std::string input;
	while(!validated){
		std::cout << "Please enter password\n";
		std::getline(std::cin, input);
		if (input.find(";") != std::string::npos) {
			std::cout << "Password cannot contain the ; character" << '\n';
		}else{
			validated = true;
		}
	}
	return input;
}

std::string MenuOptions::getTimeDate(std::string dateType) {
	bool validated = false;
	std::string input;
	while(!validated){
		if(!dateType.compare("OLD")){
			std::cout << "Please enter old appointment time (24 hour) & date in the format hh:mm mm/dd/yyyy\n";
		}else if(!dateType.compare("UPDATE")){
			std::cout << "Please enter updated new appointment time (24 hour) & date in the format hh:mm mm/dd/yyyy\n";
		}else if(!dateType.compare("START")){
			std::cout << "Please enter the starting time (24 hour) & date in the format hh:mm mm/dd/yyyy\n";
		}else if(!dateType.compare("END")){
			std::cout << "Please enter the ending time (24 hour) & date in the format hh:mm mm/dd/yyyy\n";
		}else {
			std::cout << "Please enter new appointment time (24 hour) & date in the format hh:mm mm/dd/yyyy\n";
		}
		std::getline(std::cin, input);
		std::regex pattern("^\\d{2}[\\:]\\d{2}[[:space:]]\\d{2}[\\/]\\d{2}[\\/]\\d{4}$");
		if (!std::regex_match(input, pattern)) {
			std::cout << "Time & date must be in hh:mm mm/dd/yyyy format please try again" << '\n';
		}else{
			validated = true;
		}
	}
	return input;
}

std::string MenuOptions::getMemo(std::string dateType) {
	bool validated = false;
	std::string input;
	while(!validated){
		if(!dateType.compare("OLD")){
			std::cout << "Please enter old appointment reason\n";
		}else if(!dateType.compare("UPDATE")){
			std::cout << "Please enter updated appointment reason\n";
		}else {
			std::cout << "Please enter new appointment reason\n";
		}
		std::getline(std::cin, input);
		if (input.find(";") != std::string::npos) {
			std::cout << "Your appointment reason cannot contain the ; character" << '\n';
		}else{
			validated = true;
		}
	}
	return input;
}

std::string MenuOptions::getPlace(std::string dateType) {
	bool validated = false;
	std::string input;
	while(!validated){
		if(!dateType.compare("OLD")){
			std::cout << "Please enter old appointment place\n";
		}else if(!dateType.compare("UPDATE")){
			std::cout << "Please enter updated appointment place\n";
		}else {
			std::cout << "Please enter new appointment place\n";
		}
		std::getline(std::cin, input);
		if (input.find(";") != std::string::npos) {
			std::cout << "Your appointment place cannot contain the ; character" << '\n';
		}else{
			validated = true;
		}
	}
	return input;
}


std::string getName() {
	bool validated = false;
	std::string input;
	while(!validated){
		std::cout << "Please enter name\n";
		std::getline(std::cin, input);
		if (input.find(";") != std::string::npos) {
			std::cout << "Your name cannot contain the ; character" << '\n';
		}else{
			validated = true;
		}
	}
	return input;
}

std::string MenuOptions::getEmail() {
	bool validated = false;
	std::string input;
	while(!validated){
		std::cout << "Please enter your email\n";
		std::getline(std::cin, input);
		if (input.find(";") != std::string::npos) {
			std::cout << "Your email cannot contain the ; character" << '\n';
		}else{
			validated = true;
		}
	}
	return input;
}


std::string MenuOptions::getPhone() {
	bool validated = false;
	std::string input;
	while(!validated){
		std::cout << "Please enter phone consisting of only 10 digits\n";
		std::getline(std::cin, input);
		std::regex pattern("^\\d{10}$");
		if (!std::regex_match(input, pattern)) {
			std::cout << "Your phone can only consist of 10 digits" << '\n';
		}else{
			validated = true;
		}
	}
	return input;
}

