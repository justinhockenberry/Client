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

using std::cout;
using std::cin;

#define PORT 336958
#define MAXDATASIZE 512

int main(int argc, char *argv[]){
	int sockfd, numbytes;
	char buffer[MAXDATASIZE];
	char buff[MAXDATASIZE];
	char sendbuffer[MAXDATASIZE];
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



	bool loggedIn = false;
	string selection;
	while(!loggedIn){


		recv(sockfd, buffer, 512, 0);
		cout << "[Server]" << buffer;


		getline(cin, selection);
		send(sockfd, selection.c_str(), 127, 0);

		if(!selection.compare("1")) {

			loggedIn = menu.login(sockfd, buffer, loggedIn);
		}
		else if(!selection.compare("2")){

			loggedIn = menu.newAccount(sockfd, buffer, loggedIn);
		}
		else if(!selection.compare("3")){
			cout << "Connection terminated\n";
			close(sockfd);
			return 0;
		}
		else{
			cout << "Invalid Choice\n";
		}
	}


	for(;;){
		if ((numbytes = recv(sockfd, buffer, 512, 0)) == -1) {
			perror("recv");
			exit(1);
		}
		buffer[numbytes] = '\0';
		printf("[Server]: %s\n", buffer);

		string select;
		getline(cin, select);

		numbytes=sizeof(select.c_str());

		if(numbytes == 0 || strncmp(select.c_str(), "bye", 3) == 0){
			printf("Bye\n");
			break;
		}else {
			if ((numbytes = send(sockfd, select.c_str(), 127, 0)) == -1) {
				perror("send");
				close(sockfd);
				exit(1);
			}

			if(!select.compare("1")){

				menu.addAppointment(sockfd, buffer);
			}
			else if(!select.compare("2")){

				menu.deleteAppointment(sockfd, buffer);
			}
			else if(!select.compare("3")){

				menu.updateAppointment(sockfd, buffer);
			}
			else if(!select.compare("4")){

				menu.displayAppointTime(sockfd, buffer);
			}
			else if(!select.compare("5")){

				menu.displayAppointRange(sockfd, buffer);
			}
			else if(!select.compare("6")){

				menu.changeName(sockfd, buffer);
			}
			else if(!select.compare("7")){

				menu.changePassword(sockfd, buffer);
			}
			else if(!select.compare("8")){

				menu.changePhone(sockfd, buffer);
			}
			else if(!select.compare("9")){

				menu.changeEmail(sockfd, buffer);
			}
			else if(!select.compare("10")){

				menu.deleteUser(sockfd, buffer);
				break;
			}
			else if(!select.compare("11")){
				cout << "Connection terminated\n";
				break;
			}
			else{
				cout << "Invalid selection\n";
			}

			int numbyte;

			if ((numbyte = recv(sockfd, buff, 127, 0)) == -1) {
				perror("recv");
				exit(1);
			}

			buff[numbyte] = '\0';
			printf("[Server]: %s\n", buff);

		}
	}

	close(sockfd);
	return 0;
}
