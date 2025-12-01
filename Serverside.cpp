//this is the serverside code for the data analysis/data cleaning software 
#include <cstring>
#include <iostream>
#include <fstream>
#include <netinet/in.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <fcntl.h>
using namespace std;


string FileNameAndFileSize(char *msg){
  string info = msg;
  const size_t Pos = info.find(';');

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
      /*
      todo:
      add check for the first recv(),that if it's the termination message, it doesn't start to parse it
      */
      char filenameAndFileSize[ 1024 ] = { 0 };  
      recv(clientSocket, filenameAndFileSize, sizeof(filenameAndFileSize), 0); //get the file back from the server
      string info = filenameAndFileSize;
      const size_t Pos = info.find(';');
      int fsize=stoi(info.substr(Pos + 1, std::string::npos)); //get the filesize from the filenameAndFileSize
      string filename=info.substr(0, Pos); //get the filename
      char buffer[ fsize ] = { 0 };
      recv(clientSocket, buffer, sizeof(buffer), 0);
      string terminateMSg=buffer;
        if(terminateMSg=="TerminateConncetion"){
          keepOpen=false;
          cout<<"connection terminated..."<<"\n";
        }else{
          ofstream filetoedit(filename);
          filetoedit<<buffer<<endl;
          filetoedit.close();
          string fname=filename; //this is technically just filename again, should be removed if possible
          string str="python3 dataCleaningandVisualization.py "+fname;
          const char* command = str.c_str();
          system(command);    
          int offset=0;
          fileData=open(filename.c_str(), O_RDONLY);
          sendfile(clientSocket, fileData, 0, BUFSIZ);
        }
}
    // closing the socket.
    close(serverSocket);
    return 0;
}