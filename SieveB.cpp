#include <iostream>
#include <stdbool.h>
#include "uwecSocket.h"

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


int main(){

	int socket = callServer("localhost", 11332);
	int n = readInt(socket); //upper bound
	
	int currentIndex = readInt(socket);
	bool* prime = readBoolArray(socket, n-1);
		int first = 0;
                int second = 0;
                int third = 0;

                int last = 0;
                int secondLast = 0;
                int thirdLast = 0;
	findFirstThree(currentIndex, &first, &second, &third, prime, n-1);
        findLastThree(&last, &secondLast, &thirdLast, prime, n-1);
        cout << "Recd: " << first << "," << second << "," << third <<  ",...," << thirdLast << "," << secondLast << "," << last <<"\n";
	bool iFinished = true;
	while( calculateCurrentIndex(&currentIndex, &prime, n)){
		iFinished = false;

		 cout << "Prime: " << currentIndex+2 <<"\n";

		currentIndex++;
		writeInt(currentIndex, socket);
		
		findFirstThree(currentIndex, &first, &second, &third, prime, n-1);
                findLastThree(&last, &secondLast, &thirdLast, prime, n-1);
                cout << "Sent: " << first << "," << second << "," << third <<  ",...," << thirdLast << "," << secondLast << "," << last <<"\n";
		
		writeBoolArray(prime, socket, n-1);

		cout << "\n";

		currentIndex = readInt(socket);		

		if(currentIndex == -1){
			break; // SieveA finished so just break out
		}

		free(prime);
		prime = readBoolArray(socket, n-1);
		findFirstThree(currentIndex, &first, &second, &third, prime, n-1);
                findLastThree(&last, &secondLast, &thirdLast, prime, n-1);
                cout << "Recd: " << first << "," << second << "," << third <<  ",...," << thirdLast << "," << secondLast << "," << last <<"\n";

		iFinished = true;
        }
	if(iFinished){
		currentIndex++;
		writeInt(currentIndex, socket);
        	writeBoolArray(prime, socket, n-1);
	}
	free(prime);
	return 0;

}
