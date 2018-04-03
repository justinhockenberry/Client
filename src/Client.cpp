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

#include "MenuOptions.h"

#define PORT 336958
#define MAXDATASIZE 512

int main(int argc, char *argv[]){
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	char sendbuf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in their_addr;
	MenuOptions menu;


	if(argc != 2){
		fprintf(stderr, "usage: client hostname\n");
		exit(1);
	}


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


	if(connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1){
		perror("connect");
		exit(1);
	}

	printf("connection has been established with server. Type any message for server\n");

	bool loggedIn = false;
	std::string input;
	while(!loggedIn){


		recv(sockfd, buf, 512, 0);
		std::cout << "[Server]" << buf;


		std::getline(std::cin, input);
		send(sockfd, input.c_str(), 127, 0);
		std::string loginChoice = input;

		if(!loginChoice.compare("1")) {

			loggedIn = menu.login(sockfd, buf, loggedIn);
		}
		else if(!loginChoice.compare("2")){

			loggedIn = menu.newAccount(sockfd, buf, loggedIn);
		}
		else{
			std::cout << "Invalid Choice\n";
		}
	}


	for(;;){

		if ((numbytes = recv(sockfd, buf, 512, 0)) == -1) {
			perror("recv");
			exit(1);
		}
		buf[numbytes] = '\0';
		printf("[Server]: %s\n", buf);

		std::getline(std::cin, input);

		numbytes=sizeof(input.c_str());

		if(numbytes == 0 || strncmp(input.c_str(), "bye", 3) == 0){
			printf("Bye\n");
			break;
		}else {

			if ((numbytes = send(sockfd, input.c_str(), 127, 0)) == -1) {
				perror("send");
				close(sockfd);
				exit(1);
			}

			printf("[Client]: %s\n", input.c_str());


			if(!input.compare("1")){

				menu.addAppointment(sockfd, buf);
			}
			else if(!input.compare("2")){

				menu.deleteAppointment(sockfd, buf);
			}
			else if(!input.compare("3")){

				menu.updateAppointment(sockfd, buf);
			}
			else if(!input.compare("4")){

				menu.displayAppointTime(sockfd, buf);
			}
			else if(!input.compare("5")){

				menu.displayAppointRange(sockfd, buf);
			}
			else if(!input.compare("6")){

				menu.changeName(sockfd, buf);
			}
			else if(!input.compare("7")){

				menu.changePassword(sockfd, buf);
			}
			else if(!input.compare("8")){

				menu.changePhone(sockfd, buf);
			}
			else if(!input.compare("9")){

				menu.changeEmail(sockfd, buf);
			}
			else if(!input.compare("10")){

				menu.deleteUser(sockfd, buf);
				break;
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
