#include <iostream>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main(){

    int client, server;
    int portNum = 5000;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];

    struct sockaddr_in server_addr;
    socklen_t size;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if(client < 0){
        cout << "Error establishing connection" << endl;
        exit(1);
    }

    cout << "Server socket connection established" << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    if(bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        cout << "Error  binding to socket" << endl;
        exit(1);
    }

    size = sizeof(server_addr);
    cout << "Looking for client connections" << endl;

    listen(client, 1);

    server = accept(client, (struct sockaddr*)&server_addr, &size);

    if(server < 0){
        cout << "Error accepting connection from client" << endl;
        exit(1);
    }

    while(server > 0){
        strcpy(buffer, "Server connected..\n");
        send(server, buffer, bufsize, 0);

        cout << "Connected with client" << endl;
        cout << "Enter `#` to end the connection" << endl;
        cout << "client: ";
        do {
            recv(server, buffer, bufsize, 0);
            cout << "buffer" << " ";
            if(*buffer == '#'){
                *buffer = '*';
                isExit = true;
            }
        } while(*buffer != '*');
        do{
            cout << "\nServer: ";
            do{
                cin >> buffer;
                send(server, buffer, bufsize, 0);
                if(*buffer == '#'){
                    *buffer = '*';
                    isExit = true;
                }
            }while(*buffer != '*');
            cout << "Client: ";
            do{
                recv(server, buffer, bufsize, 0);
                cout << buffer << " ";
                if(*buffer == '#'){
                    *buffer = '*';
                    isExit = true;
                }
            }while(*buffer != '*');
        }while(!isExit);

        cout << "Connection terminated" << endl;
        cout << "Bye!.." << endl;
        isExit = false;
        exit(1);
    }

    close(client);
    return 0;
}
