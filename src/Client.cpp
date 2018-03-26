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
        recv(sockfd, buf, 127, 0);
        std::cout << "[Server]" << buf;

        //Send selection
        std::getline(std::cin, input);
        send(sockfd, input.c_str(), 127, 0);
        std::string loginChoice = input;
        bool validated = false;

        //If user wants to login
        if(!loginChoice.compare("A") || !loginChoice.compare("a")) {
            while (!validated) {
                //Get username
                input = getUserName();
                send(sockfd, input.c_str(), 127, 0);

                //Get password
                input = getPassword();
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
        else if(!loginChoice.compare("B") || !loginChoice.compare("b")){
            //Get username and check if user already exists
            bool exists =true;
            while(exists){

                input = getUserName();
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
            input = getPassword();
            send(sockfd, input.c_str(), 127, 0);

            //Get name
            input = getName();
            send(sockfd, input.c_str(), 127, 0);

            //Get email
            input = getEmail();
            send(sockfd, input.c_str(), 127, 0);

            //Get phone number
            input = getPhone();
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

            if(!input.compare("A") || !input.compare("a")){
                //A) Modify name
                input = getName();
                send(sockfd, input.c_str(), 127, 0);

            }else if(!input.compare("B") || !input.compare("b")){
                //Modify password
                input = getPassword();
                send(sockfd, input.c_str(), 127, 0);
            }
            else if(!input.compare("C") || !input.compare("c")){
                //Modify phone number
                input = getPhone();
                send(sockfd, input.c_str(), 127, 0);
            }
            else if(!input.compare("D") || !input.compare("d")){
                //Modify email
                input = getEmail();
                send(sockfd, input.c_str(), 127, 0);
            }
            else if(!input.compare("E") || !input.compare("e")){
                //Delete Account
                std::cout << "Are you sure Y/N\n";
                std::getline(std::cin, input);
                send(sockfd, input.c_str(), 127, 0);
                if(!input.compare("Y") || !input.compare("y")){
                    close(sockfd);
                    return(0);
                }
            }
            else if(!input.compare("F") || !input.compare("f")){
                //Add appointment
                if ((numbytes = recv(sockfd, buf, 512, 0)) == -1) {
                    perror("recv");
                    exit(1);
                }
                buf[numbytes] = '\0';
                printf("[Server]: %s\n", buf);
                std::string appDate = getDate("NEW");
                std::string appTime = getTime("NEW");
                std::string appReason = getReason("NEW");

                bool conflict = true;
                while (conflict){
                    send(sockfd, appDate.c_str(), 127, 0);
                    send(sockfd, appTime.c_str(), 127, 0);
                    numbytes = recv(sockfd, buf, 127, 0);
                    buf[numbytes] = '\0';
                    std::string success = buf;
                    if(!success.compare("Success")){
                        conflict = false;
                    }else{
                        std::cout << "There is already an appointment at that time please reschedule\n";
                        appDate = getDate("NEW");
                        appDate = getTime("NEW");
                    }
                }
                send(sockfd, appReason.c_str(), 127, 0);
            }
            else if(!input.compare("G") || !input.compare("g")){
                //Remove appointment
                if ((numbytes = recv(sockfd, buf, 512, 0)) == -1) {
                    perror("recv");
                    exit(1);
                }
                buf[numbytes] = '\0';
                printf("[Server]: %s\n", buf);
                std::string appDate = getDate("OLD");
                std::string appTime = getTime("OLD");

                send(sockfd, appDate.c_str(), 127, 0);
                send(sockfd, appTime.c_str(), 127, 0);
            }
            else if(!input.compare("H") || !input.compare("h")){
                //Update appointment
                if ((numbytes = recv(sockfd, buf, 512, 0)) == -1) {
                    perror("recv");
                    exit(1);
                }
                buf[numbytes] = '\0';
                printf("[Server]: %s\n", buf);
                std::string oldAppDate = getDate("OLD");
                std::string oldAppTime = getTime("OLD");
                std::string newAppDate = getDate("UPDATE");
                std::string newAppTime = getTime("UPDATE");
                std::string newAppReason = getReason("UPDATE") ;
                bool conflict = true;
                while (conflict){
                    send(sockfd, newAppDate.c_str(), 127, 0);
                    send(sockfd, newAppTime.c_str(), 127, 0);
                    numbytes = recv(sockfd, buf, 127, 0);
                    buf[numbytes] = '\0';
                    std::string success = buf;
                    if(!success.compare("Success")){
                        conflict = false;
                    }else{
                        std::cout << "There is already an appointment at that time please reschedule\n";
                        newAppDate = getDate("UPDATE");
                        newAppTime = getTime("UPDATE");
                    }
                }
                send(sockfd, newAppReason.c_str(), 127, 0);
                send(sockfd, oldAppTime.c_str(), 127, 0);
                send(sockfd, oldAppDate.c_str(), 127, 0);

            }
            else if(!input.compare("I") || !input.compare("i")){
                //Get Appointment at a time
                std::string appDate = getDate("OLD");
                std::string appTime = getTime("OLD");
                send(sockfd, appDate.c_str(), 127, 0);
                send(sockfd, appTime.c_str(), 127, 0);
            }
            else if(!input.compare("J") || !input.compare("j")){
                //Get Appointment in range
                std::string startDate = getDate("START");
                std::string endDate = getDate("END");

                std::cout << startDate << " " << endDate << "\n";

                send(sockfd, startDate.c_str(), 127, 0);
                send(sockfd, endDate.c_str(), 127, 0);

                numbytes = recv(sockfd, buf, 512, 0);
                buf[numbytes] = '\0';
                printf("[Server]: %s\n", buf);
            }
            else if(!input.compare("K") || !input.compare("k")){
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
