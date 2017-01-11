#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

/* Random Edit */

using namespace std;

int main(){
	int client, server;
    int portNum = 5000;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    char *ip = "127.0.0.1";

    struct sockaddr_in server_addr;
    socklen_t size;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if(client < 0){
    	cout << "Error creating a socket" << endl;
    	exit(1);
    }
    cout<< "Client socket created" << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = portNum;

    if(connect(client, (struct sockaddr*)&server_addr,sizeof(server_addr)) == 0){
    	cout << "Connecting to server" << endl;
    }
    recv(client, buffer, bufsize, 0);
    cout << "Connection confirmed" << endl;
    cout << "Enter # to end connection" << endl;

    do{
    	cout << "Client: ";
    	do{
    		cin >> buffer;
    		send(client, buffer, bufsize, 0);
    		if(*buffer == '#'){
    			*buffer ='*';
    			isExit = true;
    		}
    	}while(*buffer != 42);
    	cout << "Server: ";
    	do {
    		recv(client, buffer, bufsize, 0);
    		cout << buffer << " ";
    		if(*buffer == '#'){
    			*buffer = '*';
    			isExit = true;
    		}
    	}while(*buffer != 42);
    	cout << endl;
    }while(!isExit);

    cout << "Connection terminated.." << endl;
    cout << "Bye!.." << endl;

    close(client);
    return 0;

}
