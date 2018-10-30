run : uwecSocket.o sieveA.o
	g++ -o ./socket uwecSocket.o sieveA.o 

sieveA.o : SieveA.cpp  
	g++ -c SieveA.cpp

uwecSocket.o : uwecSocket.h uwecSocket.c
	g++ -c uwecSocket.h uwecSocket.c


clean : 
	rm socket
	rm uwecSocket.o
	rm sieveA.o
	rm uwecSocket.h.gch


