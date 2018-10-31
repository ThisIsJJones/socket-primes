#include <iostream>
#include <stdbool.h>
#include "uwecSocket.h"

using namespace std;



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


int main(){

	int socket = callServer("localhost", 11332);
	int n = readInt(socket); //upper bound
	cout << "Got upper bound: " << n << "\n";


	bool* prime = readBoolArray(socket, n);
	for(int i = 0; i<n-1; i++){
		cout << prime[i] << ", ";
	}

	int index = 1;
	while( calculateCurrentIndex(&index, prime, n)){
                writeBoolArray(prime, socket, n-1);
                prime = readBoolArray(socket, n-1);
                index+=2;
        }

	cout << "done";
	return 0;

}
