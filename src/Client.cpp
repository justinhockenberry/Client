//============================================================================
// Name        : Client.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

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
#include <string>
#include "Utilities.h"

#define PORT 336958
#define MAXDATASIZE 512

int main(int argc, char *argv[]){
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	char sendbuf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in their_addr;

	//Check for command line arguments
	if(argc != 2){
		fprintf(stderr, "usage: client hostname\n");
		exit(1);
	}

	//assign the hostname to the first command line argument
	if((he=gethostbyname(argv[1])) == NULL){
		perror("gethostbyname");
		exit(1);
	}
	//create a TCP socket
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
	}

	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(PORT);
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(&(their_addr.sin_zero), '\0', 8);

	//check for connection
	if(connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1){
		perror("connect");
		exit(1);
	}

	printf("connection has been established with server. Type any message for server\n");
	//main connection loop
	/**
	 * Login sequence
	 */
	//Get Login Menu
	bool loggedIn = false;
	std::string input;
	while(!loggedIn){


		recv(sockfd, buf, 512, 0);
		std::cout << "[Server]" << buf;

		//Send selection
		std::getline(std::cin, input);
		send(sockfd, input.c_str(), 127, 0);
		std::string loginChoice = input;
		bool validated = false;

		//If user wants to login
		if(!loginChoice.compare("1")) {
			while (!validated) {
				//Get username
				//                input = getUserName();
				//            	bool validated = false;
				std::string input = "";
				//            	while(!validated){
				std::cout << "Please enter username\n";
				std::getline(std::cin, input);
				//            		if (input.find(";") != std::string::npos) {
				//            			std::cout << "Username cannot contain the ; character" << '\n';
				//            		}else{
				//            			validated = true;
				//            		}
				//            	}
				send(sockfd, input.c_str(), 127, 0);

				//Get password
				//                input = getPassword();
				//            	validated = false;
				input = "";
				//            	while(!validated){
				std::cout << "Please enter password\n";
				std::getline(std::cin, input);
				//            		if (input.find(";") != std::string::npos) {
				//            			std::cout << "Password cannot contain the ; character" << '\n';
				//            		}else{
				//            			validated = true;
				//            		}
				//            	}
				send(sockfd, input.c_str(), 127, 0);

				numbytes = recv(sockfd, buf, 127, 0);
				buf[numbytes] = '\0';
				std::string success = buf;
				if(!success.compare("Success")){
					validated = true;
					loggedIn = true;
					std::cout << "Log in successful\n";
				}
				else{
					std::cout << "Log in failure please retry\n";
				}
			}
		}// If user wants to create an account
		else if(!loginChoice.compare("2")){
			//Get username and check if user already exists
			bool exists =true;
			while(exists){

				//                input = getUserName();
				//            	bool validated = false;
				std::string input = "";
				//            	while(!validated){
				std::cout << "Please enter username\n";
				std::getline(std::cin, input);
				//            		if (input.find(";") != std::string::npos) {
				//            			std::cout << "Username cannot contain the ; character" << '\n';
				//            		}else{
				//            			validated = true;
				//            		}
				//            	}
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


			//Get password
			//            input = getPassword();
			//            bool validated = false;
			input = "";
			//            while(!validated){
			std::cout << "Please enter password\n";
			std::getline(std::cin, input);
			//            	if (input.find(";") != std::string::npos) {
			//            		std::cout << "Password cannot contain the ; character" << '\n';
			//            	}else{
			//            		validated = true;
			//            	}
			//            }
			send(sockfd, input.c_str(), 127, 0);

			//Get name
			//            input = getName();
			//            validated = false;
			input = "";
			//            while(!validated){
			std::cout << "Please enter name\n";
			std::getline(std::cin, input);
			//            	if (input.find(";") != std::string::npos) {
			//            		std::cout << "Your name cannot contain the ; character" << '\n';
			//            	}else{
			//            		validated = true;
			//            	}
			//            }
			send(sockfd, input.c_str(), 127, 0);

			//Get email
			//            input = getEmail();
			//            validated = false;
			input = "";
			//            while(!validated){
			std::cout << "Please enter your email\n";
			std::getline(std::cin, input);
			//            	if (input.find(";") != std::string::npos) {
			//            		std::cout << "Your email cannot contain the ; character" << '\n';
			//            	}else{
			//            		validated = true;
			//            	}
			//            }
			send(sockfd, input.c_str(), 127, 0);

			//Get phone number
			//            input = getPhone();
			//            validated = false;
			input = "";
			//            while(!validated){
			std::cout << "Please enter phone consisting of only 10 digits\n";
			std::getline(std::cin, input);
			//            	std::regex pattern("^\\d{10}$");
			//            	if (!std::regex_match(input, pattern)) {
			//            		std::cout << "Your phone can only consist of 10 digits" << '\n';
			//            	}else{
			//            		validated = true;
			//            	}
			//            }
			send(sockfd, input.c_str(), 127, 0);
			validated = true;
			loggedIn = true;


		}
		else{
			std::cout << "Invalid Choice\n";
		}
	}


	for(;;){
		//receive the choices
		if ((numbytes = recv(sockfd, buf, 512, 0)) == -1) {
			perror("recv");
			exit(1);
		}
		buf[numbytes] = '\0';
		printf("[Server]: %s\n", buf);
		//read input
		std::getline(std::cin, input);

		numbytes=sizeof(input.c_str());

		if(numbytes == 0 || strncmp(input.c_str(), "bye", 3) == 0){
			printf("Bye\n");
			break;
		}else {
			//send choice or value to server
			if ((numbytes = send(sockfd, input.c_str(), 127, 0)) == -1) {
				perror("send");
				close(sockfd);
				exit(1);
			}

			printf("[Client]: %s\n", input.c_str());


			if(!input.compare("1")){
				//Add appointment
				if ((numbytes = recv(sockfd, buf, 512, 0)) == -1) {
					perror("recv");
					exit(1);
				}
				buf[numbytes] = '\0';
				printf("[Server]: %s\n", buf);
				std::string beginTime = getTimeDate("NEW");
				std::string endTime = getTimeDate("END");
				std::string memo = getMemo("NEW");
				std::string place = getPlace("NEW");


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
						beginTime = getTimeDate("NEW");
						endTime = getTimeDate("NEW");
					}
				}

				send(sockfd, memo.c_str(), 127, 0);
				send(sockfd, place.c_str(), 127, 0);
			}
			else if(!input.compare("2")){
				//Remove appointment
				if ((numbytes = recv(sockfd, buf, 512, 0)) == -1) {
					perror("recv");
					exit(1);
				}
				buf[numbytes] = '\0';
				printf("[Server]: %s\n", buf);
				std::string beginTime = getTimeDate("OLD");
//				std::string appTime = getTime("OLD");

				send(sockfd, beginTime.c_str(), 127, 0);
//				send(sockfd, appTime.c_str(), 127, 0);
			}
			else if(!input.compare("3")){
				//Update appointment
				if ((numbytes = recv(sockfd, buf, 512, 0)) == -1) {
					perror("recv");
					exit(1);
				}
				buf[numbytes] = '\0';
				printf("[Server]: %s\n", buf);
				std::string oldBeginDate = getTimeDate("OLD");
				std::string newBeginDate = getTimeDate("UPDATE");
				std::string newEndDate = getTimeDate("END");
				std::string newMemo = getMemo("UPDATE");
				std::string newPlace = getPlace("UPDATE");

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
						newBeginDate = getTimeDate("UPDATE");
						newEndDate = getTimeDate("UPDATE");
					}
				}
				send(sockfd, newMemo.c_str(), 127, 0);
				send(sockfd, newPlace.c_str(), 127, 0);
				send(sockfd, oldBeginDate.c_str(), 127, 0);

			}
			else if(!input.compare("4")){
				//Get Appointment at a time
				std::string beginTime = getTimeDate("OLD");
//				std::string appTime = getTime("OLD");
				send(sockfd, beginTime.c_str(), 127, 0);
//				send(sockfd, appTime.c_str(), 127, 0);
			}
			else if(!input.compare("5")){
				//Get Appointment in range
				std::string startDate = getTimeDate("START");
				std::string endDate = getTimeDate("END");

				std::cout << startDate << " " << endDate << "\n";

				send(sockfd, startDate.c_str(), 127, 0);
				send(sockfd, endDate.c_str(), 127, 0);

				numbytes = recv(sockfd, buf, 512, 0);
				buf[numbytes] = '\0';
				printf("[Server]: %s\n", buf);
			}
			else if(!input.compare("6")){
				//A) Modify name
				//                input = getName();
				//            	bool validated = false;
				std::string input;
				//            	while(!validated){
				std::cout << "Please enter name\n";
				std::getline(std::cin, input);
				//            		if (input.find(";") != std::string::npos) {
				//            			std::cout << "Your name cannot contain the ; character" << '\n';
				//            		}else{
				//            			validated = true;
				//            		}
				//            	}
				send(sockfd, input.c_str(), 127, 0);

			}else if(!input.compare("7")){
				//Modify password
				//                input = getPassword();
				//            	bool validated = false;
				input = "";
				//            	while(!validated){
				std::cout << "Please enter password\n";
				std::getline(std::cin, input);
				//            		if (input.find(";") != std::string::npos) {
				//            			std::cout << "Password cannot contain the ; character" << '\n';
				//            		}else{
				//            			validated = true;
				//            		}
				//            	}
				send(sockfd, input.c_str(), 127, 0);
			}
			else if(!input.compare("8")){
				//Modify phone number
				//                input = getPhone();
				//            	bool validated = false;
				input = "";
				//            	while(!validated){
				std::cout << "Please enter phone consisting of only 10 digits\n";
				std::getline(std::cin, input);
				//            		std::regex pattern("^\\d{10}$");
				//            		if (!std::regex_match(input, pattern)) {
				//            			std::cout << "Your phone can only consist of 10 digits" << '\n';
				//            		}else{
				//            			validated = true;
				//            		}
				//            	}
				send(sockfd, input.c_str(), 127, 0);
			}
			else if(!input.compare("9")){
				//Modify email
				//                input = getEmail();
				//            	bool validated = false;
				input = "";
				//            	while(!validated){
				std::cout << "Please enter your email\n";
				std::getline(std::cin, input);
				//            		if (input.find(";") != std::string::npos) {
				//            			std::cout << "Your email cannot contain the ; character" << '\n';
				//            		}else{
				//            			validated = true;
				//            		}
				//            	}
				send(sockfd, input.c_str(), 127, 0);
			}
			else if(!input.compare("10")){
				//Delete Account
				std::cout << "Are you sure Y/N\n";
				std::getline(std::cin, input);
				send(sockfd, input.c_str(), 127, 0);
				if(!input.compare("Y") || !input.compare("y")){
					close(sockfd);
					return(0);
				}
			}
			else if(!input.compare("11")){
				std::cout << "Good Bye!\n";
				break;
			}
			else{
				std::cout << "Invalid Input\n";
			}

			if ((numbytes = recv(sockfd, buf, 127, 0)) == -1) {
				perror("recv");
				exit(1);
			}
			buf[numbytes] = '\0';
			printf("[Server]: %s\n", buf);
		}
	}

	close(sockfd);
	return 0;
}
