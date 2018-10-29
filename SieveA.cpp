#include <iostream>
#include "uwecSocket.h"
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

void calculateCurrentIndex(int index, bool prime[], int upperBound){
	if(prime[index]){
		for(int i=index*2; i<=upperBound; i += index){
			prime[i] = false;
		}
	}	
}

int main(int argc, char** argv){
	if(argc!=2){   //executable comes in as first parameter
		cout << "Upper range is needed.\n";
		return -1;
	}

	int serverSocket = setupServerSocket(11331);
	int socket = serverSocketAccept(serverSocket);

	int n = stoi(argv[1]);
	bool prime[n+1];
	memset(prime, true, sizeof(prime));
	
	int index = 2;

	calculateCurrentIndex(index, prime, n);	


	writeInt(5, socket);
	
	//send prime array to sieve B
	index+=2;
	calculateCurrentIndex(index, prime, n);	
	
	for(int p=2; p<=n; p++){
		if(prime[p]){	
			cout << p << " ";
		}
	}
	//Sieve(stoi(argv[1]));
	return 0;

}


