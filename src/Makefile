clientRun: Client.o Utilities.o
	g++ -std=c++11 Client.o Utilities.o -o clientRun

Client.o: Client.cpp
	g++ -c -std=c++11 Client.cpp

Utilities.o: Utilities.cpp
	g++ -c -std=c++11 Utilities.cpp

clean:
	rm *.o clientRun
