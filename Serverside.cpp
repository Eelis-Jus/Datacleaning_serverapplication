//this is the serverside code for the data analysis/data cleaning software 
#include <cstring>
#include <iostream>
#include <fstream>
#include <netinet/in.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <fcntl.h>
using namespace std;


bool isTerminateMessage(char *msg){
  string info = msg;
  if(info=="TerminateConncetion"){
    return true;
  }else{
    cout<<"message is not a termination message"<<"\n";
    return false;
  }

}

int main(){ 
  bool keepOpen;
  keepOpen=true;
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
      /*
      todo:
      
      */

      char filenameAndFileSize[ 1024 ] = { 0 };  
      recv(clientSocket, filenameAndFileSize, sizeof(filenameAndFileSize), 0); //get the file back from the server
      cout<<"check if message is termination message"<<"\n";
      bool checkTermination=isTerminateMessage(filenameAndFileSize);
      if(checkTermination){
        keepOpen=false;
        break;        
      };
      cout<<"message is"<<filenameAndFileSize<<"\n";
      string info = filenameAndFileSize;
      const size_t Pos = info.find(';');
      int fsize=stoi(info.substr(Pos + 1, std::string::npos)); //get the filesize from the filenameAndFileSize
      string filename=info.substr(0, Pos); //get the filename
      cout<<"filename: "<<filename<<"\n";
      char buffer[ fsize ] = { 0 };
      recv(clientSocket, buffer, sizeof(buffer), 0);
      string terminateMSg=buffer;
        if(terminateMSg=="TerminateConncetion"){
          keepOpen=false;
          break;
        }else{
          ofstream filetoedit(filename);
          filetoedit<<buffer<<endl;
          filetoedit.close();
          string fname=filename; //this is technically just filename again, should be removed if possible
          cout<<"analyzing the file"<<"\n";
          string str="python3 dataCleaningandVisualization.py "+fname;
          cout<<"file analyzed"<<"\n";
          const char* command = str.c_str();
          system(command);    
          int offset=0;
          cout<<"sending the file back"<<"\n";
          fileData=open(filename.c_str(), O_RDONLY);
          sendfile(clientSocket, fileData, 0, BUFSIZ);
          remove(filename.c_str()); //remove the file from the server
        }
}
    // closing the socket.
  close(serverSocket);
  cout<<"connection terminated..."<<"\n";
  return 0;
}