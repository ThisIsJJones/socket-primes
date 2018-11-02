#include <iostream>
#include "uwecSocket.h"
#include <string.h>
using namespace std;

bool calculateCurrentIndex(int* index, bool** prime, int upperBound){
	//bumpedIndex is the actual value at that index position :)
	int bumpedIndex = (*index)+2;
	bool result = true;
	bool keepGoing = true;
	while(keepGoing){
		if(bumpedIndex * bumpedIndex <= upperBound){
			if((*prime)[(*index)]){
				for(int i=bumpedIndex * bumpedIndex; i<=upperBound; i += bumpedIndex){
					(*prime)[i-2] = false;
				}
				keepGoing = false;
			}else{
				//the current index is false (not a prime)
				(*index)++;
				bumpedIndex++;
			}
		}else{
			keepGoing = false;
			result = false;
		}
	}
	return result;
}

void findFirstThree(int startingIndex, int* f, int* s, int* t, bool* prime, int totalAmount){
	int primeCount = 0;
	for(int i=startingIndex; i<totalAmount && primeCount<3; i++){
		if(prime[i]){
			primeCount++;
			(*f) = (*s);
			(*s) = (*t);
			(*t) = i+2; 
		}
	}
}

void findLastThree(int* f, int* s, int* t, bool* prime, int totalAmount){
	for(int i=0; i<totalAmount; i++){
		if(prime[i]){
			(*t) = (*s);
			(*s) = (*f);
			(*f) = i+2; 
		}
	}
}


int main(int argc, char** argv){
	if(argc!=2){   //executable comes in as first parameter
		cout << "Upper range is needed.\n";
		return -1;
	}

	int serverSocket = setupServerSocket(11332);
	int socket = serverSocketAccept(serverSocket);

	int n = stoi(argv[1]);

	bool* primePointer = (bool*)malloc(sizeof(bool)*n-1);
	memset(primePointer, true, sizeof(bool) * (n-1));
	int index=0;
	writeInt(n, socket);

	int primesFound[n-1];
	int primeCounter = 0; 	
	while( calculateCurrentIndex(&index, &primePointer, n)){
		primesFound[primeCounter] = index+2;
		primeCounter++;
		cout << "Prime: ";
		for(int j = 0; j<primeCounter; j++){
			cout <<  primesFound[j] << ",";
		}
		cout << "\n";
		index++;
		writeInt(index, socket);
		int first = 0;
		int second = 0;
		int third = 0;
		
		int last = 0;
		int secondLast = 0;		
		int thirdLast = 0;

		findFirstThree(index, &first, &second, &third, primePointer, n-1);
		findLastThree(&last, &secondLast, &thirdLast, primePointer, n-1);
		cout << "Sent: " << first << "," << second << "," << third <<  ",...," << thirdLast << "," << secondLast << "," << last <<"\n";
		
		writeBoolArray(primePointer, socket, n-1);

		cout << "\n";

		index = readInt(socket);	

		primesFound[primeCounter] = index+1;
		primeCounter++;

		free(primePointer);
		primePointer = readBoolArray(socket, n-1);
		findFirstThree(index, &first, &second, &third, primePointer, n-1);
		findLastThree(&last, &secondLast, &thirdLast, primePointer, n-1);
		cout << "Recd: " << first << "," << second << "," << third <<  ",...," << thirdLast << "," << secondLast << "," << last <<"\n";
	}

	writeInt(-1, socket);
	cout << "\n";
//	cout << "ALL PRIMES:\n";
//	for(int p=0; p<n-1; p++){
//		if(primePointer[p]){
//			cout << p+2 << " ";
//		}
//	}
//	cout << "\n";

	return 0;

}


