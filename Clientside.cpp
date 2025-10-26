//this is the clientside code for the client-server part of the data cleaning/data analysis software
#include <cstring>
#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <bits/stdc++.h>
using namespace std;

int main(){
    bool keepMessaging=true;
    char keepconnection;
    cout<<"Welcome to the program!"<<"\n";
    int clientSocket=socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in Serveraddress; 
    Serveraddress.sin_family = AF_INET;
    Serveraddress.sin_port = htons(8080);
    Serveraddress.sin_addr.s_addr = INADDR_ANY;

    connect(clientSocket, (struct sockaddr*)&Serveraddress,sizeof(Serveraddress));  //Establish the connection


   //////
   //TODO:
   //-send size of the message before the message
   //////
    string message;
    while(keepMessaging){     // sending data
        cout<<"give your message: "<<"\n";
        cin>>message;
        send(clientSocket, message.c_str(), strlen(message.c_str()), 0);
        do{
        cout<<"keep messsaging? (y/n)"<<"\n";
        cin>>keepconnection;
        keepconnection=tolower(keepconnection); //changing the closeconnetion answer to lowercase, so the user input doesn't matter
        }while(keepconnection!='y' && keepconnection!='n');
        if(keepconnection=='y'){

        }else{
            char terminatemsg[0];
            send(clientSocket, terminatemsg, strlen(terminatemsg), 0);
            keepMessaging=false;
        }

    }
    cout<<"closing connection...";
    sleep(1);
    // closing socket
    close(clientSocket);

    return 0;
}