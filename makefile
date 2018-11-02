run : uwecSocket.o SieveA.cpp
	g++ -o ./socket uwecSocket.o SieveA.cpp

uwecSocket.o : uwecSocket.h uwecSocket.c
	g++ -c uwecSocket.h uwecSocket.c

b : uwecSocket.o SieveB.cpp   
	g++ uwecSocket.o SieveB.cpp -o ./Bsock

clean : 
	rm socket
	rm Bsock
	rm uwecSocket.o
	rm uwecSocket.h.gch


