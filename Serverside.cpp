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
      //  char *msgSize = new char;
      //  recv(clientSocket, msgSize, sizeof(msgSize), 0); //get the size of the coming message
      //  string size=msgSize; //convert char to string, so I can use stoi to convert the size to int
      //  cout<<"size of msg; "<<size<<"\n"; //testing that this works
       // int sizeToInt=stoi(size);
        //char buffer[sizeToInt] = { 0 }; 
      //  delete msgSize; //delete the memory used to house the size of message
      char buffer[ 1024 ] = { 0 };
        recv(clientSocket, buffer, sizeof(buffer), 0);
        string terminateMSg=buffer;
        if(terminateMSg=="TerminateConncetion"){
            keepOpen=false;
            cout<<"connection terminated..."<<"\n";
        }else{
            cout << "Message from client: " << buffer << endl;
          //  string message="message received";
          //  send(clientSocket, message.c_str(), strlen(message.c_str()), 0);
        }
}
    // closing the socket.
    close(serverSocket);
    return 0;
}