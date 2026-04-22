//this is the serverside code for the data analysis/data cleaning software 
#include <cstring>
#include <iostream>
#include <thread>
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

int open_connection(int server_socket){ //waits to get the connection and returns the socket 
  int client_socket=accept(server_socket, nullptr, nullptr);
  return client_socket;
}

void analyze_the_file(string filename){
  string fname=filename; //this is technically just filename again, should be removed if possible
  cout<<"analyzing the file"<<"\n";
  string cmd_str="python3 dataCleaningandVisualization.py "+fname; 
  const char* command = cmd_str.c_str();
  system(command);    
  cout<<"file analyzed"<<"\n";
  int offset=0;
  cout<<"sending the file back"<<"\n";
  return;
}

int receive_the_file(int filesize, string filename, int clientsocket){
      char buffer[ filesize ] = { 0 };
      recv(clientsocket, buffer, sizeof(buffer), 0);
      string terminateMSg=buffer;
        if(terminateMSg=="TerminateConncetion"){
          close(clientsocket);
          return 1;
        }else{
          ofstream filetoedit(filename);
          filetoedit<<buffer<<endl;
          filetoedit.close();
          analyze_the_file(filename);
        return 0;
}
}

int check_message(int client_socket){
  cout<<"New thread. Thread id: "<<this_thread::get_id()<<"\n";
  int fileData;
  char filenameAndFileSize[ 1024 ] = { 0 };  
  recv(client_socket, filenameAndFileSize, sizeof(filenameAndFileSize), 0); //get the file size and name from the client
  cout<<"check if message is termination message"<<"\n";
  bool checkTermination=isTerminateMessage(filenameAndFileSize);
  if(checkTermination){
    return 1;
  }
  cout<<"message is"<<filenameAndFileSize<<"\n";
  string info = filenameAndFileSize;
  const size_t Pos = info.find(';');
  int fsize=stoi(info.substr(Pos + 1, std::string::npos)); //get the filesize from the filenameAndFileSize
  string name_of_the_received_file=info.substr(0, Pos); //get the filename 
  cout<<"filename: "<<name_of_the_received_file<<"\n";
  cout<<"size of the file: "<<fsize<<"\n";
  receive_the_file(fsize, name_of_the_received_file, client_socket);
  fileData=open(name_of_the_received_file.c_str(), O_RDONLY); //send the file back to the client
  sendfile(client_socket, fileData, 0, BUFSIZ);
  remove(name_of_the_received_file.c_str()); //remove the file from the server
  return 0;
  }

int main(){ 
  bool keepOpen;
  keepOpen=true;
  int fileData;
  int thread_count=1;
  vector<thread> threads;
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
    
    // receiving data

  //while (serverOpen){ 
    //while(keepOpen){ 
    while(1){
    int clientSocket=open_connection(serverSocket); 
      threads.push_back(thread(check_message, clientSocket));
      }
    //}
    
    // closing the socket.
  for(int i=0; i<threads.size(); i++){
    threads[i].join();
  }
  close(serverSocket);
  cout<<"connection terminated..."<<"\n";
  return 0;
}