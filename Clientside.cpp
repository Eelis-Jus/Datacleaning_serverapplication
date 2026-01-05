//this is the clientside code for the client-server part of the data cleaning/data analysis software
#include <cstring>
#include <iostream>
#include <fcntl.h>
#include <fstream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <filesystem>
#include <sys/sendfile.h>
#include <unistd.h>
#include <bits/stdc++.h>
using namespace std;
 
   ////// 
   //TODO:
   //  
   //
   //////

string fileExists(string filename){ //check if the file exists
string file = filename;
    if(filesystem::exists(file)==true){
        return "file exists";
    }else if(filesystem::exists(file)==false){
        return "file doesn't exist";
    }else{
        return "unknown error";
    }
}



 int main(){
    bool keepMessaging=true;
    char keepconnection;
    int fileData;
    int filesize;
    struct stat file_stat;
        int offset;
        int remain_data;
    cout<<"Welcome to the program!"<<"\n";
    int clientSocket=socket(AF_INET, SOCK_STREAM, 0); //AF_INET means a ipv4 protocol and SOCK_STREAM means a tcp-socket,  int sockfd declares an integer variable that will store the socket file descriptor, lets the system choose the default protocol for the specified address family and socket type (which is TCP in this case).
    sockaddr_in Serveraddress; 
    Serveraddress.sin_family = AF_INET;
    Serveraddress.sin_port = htons(8080); //htons(): Converts port to network byte order.
    Serveraddress.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY: Accept connections on any IP.

    connect(clientSocket, (struct sockaddr*)&Serveraddress,sizeof(Serveraddress));  //Establish the connection
   
    string message; //this is the whole first message, it includes the size of the file and name of the file
    string sentFile; //name of the file
    string file_exists;
    //string sizeofmsg; 
    while(keepMessaging){     // sending data
        do{
            cout<<"give the name of your file: "<<"\n";
            cin>>sentFile;
            file_exists=fileExists(sentFile);
            cout<<file_exists<<"\n";
        }while(file_exists != "file exists");
        //string currentPath=filesystem::current_path();
        filesystem::path filePath = filesystem::current_path() / sentFile; 
        //string filePath=filesystem::path(message);
        cout<<"filepath: "<<filePath<<"\n";
        string fileSize=to_string(filesystem::file_size(filePath));
        message=sentFile+";"+fileSize;
        cout<<"sending the size and name"<<"\n";
        send(clientSocket, message.c_str(), strlen(message.c_str()), 0); //send the name and the size of the file
        cout<<"size and name has been sent"<<"\n";
        sleep(2);
        
        fileData=open(sentFile.c_str(), O_RDONLY);
        //filesize=filesystem::file_size(message); //what has this been used for?
        offset=0;
        cout<<"sending the file"<<"\n";
        sendfile(clientSocket, fileData, 0, BUFSIZ);
        cout<<"file sent"<<"\n";
        sleep(2);
        char buffer[ 3072 ] = { 0 };
        recv(clientSocket, buffer, sizeof(buffer), 0); //get the file back from the server
        ofstream filetoedit(sentFile);
        filetoedit<<buffer<<endl;
        filetoedit.close();
        cout<<"filename: "<<sentFile<<"\n";
        cout<<"message received from server: "<<buffer<<"\n";
        do{
            cout<<"keep messsaging? (y/n)"<<"\n";
            cin>>keepconnection;
            keepconnection=tolower(keepconnection); //changing the closeconnetion answer to lowercase, so the user input doesn't matter
        }while(keepconnection!='y' && keepconnection!='n');
        if(keepconnection=='y'){

        }else{
            string terminatemsg="TerminateConncetion";
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