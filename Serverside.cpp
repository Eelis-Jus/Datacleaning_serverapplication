//this is the serverside code for the data analysis/data cleaning software 
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <string>
using namespace std;

int main(){
    bool keepOpen=true;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying the address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // binding socket.
    bind(serverSocket, (struct sockaddr*)&serverAddress,sizeof(serverAddress));

    // listening to the assigned socket
    listen(serverSocket, 5);

    // accepting connection request
    int clientSocket = accept(serverSocket, nullptr, nullptr);

    // recieving data
    while(keepOpen){
        char buffer[1024] = { 0 }; 
        recv(clientSocket, buffer, sizeof(buffer), 0);
        if(sizeof(buffer)==0){
            keepOpen=false;
        }else{
            cout << "Message from client: " << buffer << endl;
        }
}
    // closing the socket.
    close(serverSocket);
    return 0;
}