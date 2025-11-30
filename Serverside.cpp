//this is the serverside code for the data analysis/data cleaning software 
#include <cstring>
#include <iostream>
#include <fstream>
#include <netinet/in.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <string>
#include <fcntl.h>
using namespace std;


void binaryToFile(char fileBinary){
  ofstream fileToBeMade("fileToBeTreated.csv", ios::out | ios::app);
  fileToBeMade.put(fileBinary);
  fileToBeMade.clear();
}

int main(){
  bool keepOpen=true;
  int fileData;
  FILE *received_file;

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
      char filename[ 3072 ] = { 0 };  
      recv(clientSocket, filename, sizeof(filename), 0); //get the file back from the server
      char buffer[ 3072 ] = { 0 };
        recv(clientSocket, buffer, sizeof(buffer), 0);
        string terminateMSg=buffer;
        if(terminateMSg=="TerminateConncetion"){
            keepOpen=false;
            cout<<"connectionee terminated..."<<"\n";
        }else{
          ofstream filetoedit(filename);
          filetoedit<<buffer<<endl;
          filetoedit.close();
          string fname=filename; //this is technically just filename again, should be removed if possible
          string str="python3 dataCleaningandVisualization.py "+fname;
          const char* command = str.c_str();
          system(command);
          //sleep(20);
          int offset=0;
          fileData=open(filename, O_RDONLY);
          sendfile(clientSocket, fileData, 0, BUFSIZ);
          //cout << "Message from client: " << buffer << endl;
          //  string message="message received";
          //  send(clientSocket, message.c_str(), strlen(message.c_str()), 0);
        }
}
    // closing the socket.
    close(serverSocket);
    return 0;
}