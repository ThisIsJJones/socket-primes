#include <iostream>
#include <stdbool.h>
#include "uwecSocket.h"

using namespace std;

int main(){
	
	int socket = callServer("localhost", 11331);
	int f = readInt(socket);
	cout << f;
	return 0;

}
