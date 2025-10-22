//this is the clientside code for the client-server part of the data cleaning/data analysis software
#include <cstring>
#include <iostream>
//#include <netinet/in.h>
#include <winsock.h> //in linux change this to <sys/socket.h>
#include <Ws2tcpip.h>
#include <windows.h>
#include <unistd.h>

using namespace std;

int main(){
    cout<<"Welcome to the program!"<<"\n";
    int clientSocket=socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in Serveraddress; 
    Serveraddress.sin_family = AF_INET;
    Serveraddress.sin_port = htons(8080);
    Serveraddress.sin_addr.s_addr = INADDR_ANY;

    connect(clientSocket, (struct sockaddr*)&Serveraddress,sizeof(Serveraddress));  //Establish the connection

    // sending data
    const char* message = "Hello, server!";
    send(clientSocket, message, strlen(message), 0);

    // closing socket
    close(clientSocket);

    return 0;
}