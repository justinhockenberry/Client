###Readme Documentation

# Code dev environment
Used Eclipse IDE running on Ubuntu 16.4 OS

# Files Association 
Server Package
--> Server.cpp
--> MenuOptions.cpp
--> MenuOptions.h
--> User.cpp
--> User.h
--> md5.cpp
--> md5.h

Client Package
--> Client.cpp
--> MenuOptions.cpp
--> MenuOptions.h

# Server Operation 
Launch this package first. Take note of server IP address.

To compile this code:
$ make

To run this code after compile:
$ ./serverRun

# Client Operation
Launch this package second.

To compile this code:
$ make

To run this code after compile with the argument of the IP address you launched the server:
$ ./clientRun serverIPaddress


