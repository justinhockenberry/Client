clientRun: Client.o MenuOptions.o
	g++ -std=c++11 Client.o MenuOptions.o -o clientRun

Client.o: Client.cpp
	g++ -c -std=c++11 Client.cpp

MenuOptions.o: MenuOptions.cpp
	g++ -c -std=c++11 MenuOptions.cpp

clean:
	rm *.o clientRun
