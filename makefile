run : uwecSocket.o SieveA.cpp
	g++-7 -o ./socket uwecSocket.o SieveA.cpp

uwecSocket.o : uwecSocket.h uwecSocket.c
	g++ -c uwecSocket.h uwecSocket.c -o uwecSocket.o

Bsock :
	g++ uwecSocket.c SieveB.cpp -o Bsock

clean : 
	rm socket
	rm Bsock
	rm uwecSocket.o
	rm uwecSocket.h.gch


