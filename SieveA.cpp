#include <iostream>
#include "uwecSocket.h"
#include <string>
using namespace std;


void Sieve(int n){
	bool prime[n+1];
	memset(prime, true, sizeof(prime));

	for(int p=2; p*p<=n; p++){
		if(prime[p] == true){
			for(int i=p*2; i<=n; i +=p){
				prime[i] = false;
			}
		}
	}

	for(int p=2; p<=n; p++){
		if(prime[p]){	
			cout << p << " ";
		}
	}
}

bool calculateCurrentIndex(int* index, bool prime[], int upperBound){
	//bumpedIndex is the actual value at that index position :)
	int bumpedIndex = (*index)+2;
	bool result = true;
	bool keepGoing = true;
	while(keepGoing){
		if(bumpedIndex * bumpedIndex <= upperBound){	
			if(prime[(*index)]){
				for(int i=bumpedIndex * bumpedIndex; i<=upperBound; i += bumpedIndex){
					prime[i-2] = false;
				}
				keepGoing = false;
			}else{
				//the current index is false (not a prime)
				(*index)+=1;
				bumpedIndex+=1;	
			}
		}else{
			keepGoing = false;
			result = false;
		}
	}
	return result;
}

int main(int argc, char** argv){
	if(argc!=2){   //executable comes in as first parameter
		cout << "Upper range is needed.\n";
		return -1;
	}

	int serverSocket = setupServerSocket(11332);
	int socket = serverSocketAccept(serverSocket);

	int n = stoi(argv[1]);
		
	bool prime[n-1];
	memset(prime, true, sizeof(bool) * (n-1));
	int index = 0;
	writeInt(n, socket);

		for(int p=0; p<n-1; p++){
			cout << prime[p] << " ";
		}

	writeBoolArray(prime, socket, n-1);

//	bool* primePointer = prime;	
//	while( calculateCurrentIndex(&index, primePointer, n)){
//		for(int p=0; p<n-1; p++){
//			cout << prime[p] << " ";
//		}
//
//		writeBoolArray(prime, socket, n-1);
//		primePointer = readBoolArray(socket, n-1);
//		index+=2;
//	}	
	
	for(int p=0; p<n-1; p++){
		if(prime[p]){	
			cout << p+2 << " ";
		}
	}
	
	return 0;

}


