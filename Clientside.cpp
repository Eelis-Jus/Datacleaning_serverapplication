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
   //find out what ? is in the sizeofmsg message
   //make so, that the server doesn't throw error when client sends the "terminateconnection" message
   //////
    string message;
    string sizeofmsg;
    while(keepMessaging){     // sending data
        cout<<"give your message: "<<"\n";
        cin>>message;
        //sizeofmsg=to_string(sizeof(message));
        //send(clientSocket, sizeofmsg.c_str(), strlen(sizeofmsg.c_str()), 0); //send the size of message
        //sleep(1);
        send(clientSocket, message.c_str(), strlen(message.c_str()), 0);
        char buffer[1024] = { 0 }; 
       // recv(clientSocket, buffer, sizeof(buffer), 0); nämä ovat sitä varten, kun halutaan implementoida vastaus serveriltä
       // cout<<"message from server: "<<buffer<<"\n";
        do{
        cout<<"keep messsaging? (y/n)"<<"\n";
        cin>>keepconnection;
        keepconnection=tolower(keepconnection); //changing the closeconnetion answer to lowercase, so the user input doesn't matter
        }while(keepconnection!='y' && keepconnection!='n');
        if(keepconnection=='y'){

        }else{
            string terminatemsg="TerminateConncetion";
            //sizeofmsg=to_string(sizeof(terminatemsg));
            //send(clientSocket, sizeofmsg.c_str(), strlen(sizeofmsg.c_str()), 0); //send the size of message
            send(clientSocket, terminatemsg.c_str(), strlen(terminatemsg.c_str()), 0);
            keepMessaging=false;
        }

    }
    cout<<"closing connection..."<<"\n";
    sleep(1);
    // closing socket
    close(clientSocket);

    return 0;
}