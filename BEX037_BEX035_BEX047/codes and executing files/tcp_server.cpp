#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
using namespace std;
#define PORT "9034"
// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc,char *argv[]){
  //File descriptor list
  struct timeval tv; //timer for input
  tv.tv_sec=7;
  tv.tv_usec=100;
  fd_set master;    //master file descriptor list
  fd_set read_fds;  // temp file descriptor list for select()
  int fdmax;        // maximum file descriptor number

  //Create a socket for listening and newly accepted socket descriptor to connect to
  int listener,newfd;
  struct sockaddr_storage remoteaddr; //client address
  socklen_t addrlen;
  char buf[256]; // buffer for client data
  int nbytes;

  char remoteIP[INET6_ADDRSTRLEN];
  int yes=1;        // for setsockopt() SO_REUSEADDR, below
  int i, j, rv;

  struct addrinfo hints, *ai, *p;

  FD_ZERO(&master); // clear the master and temp sets
  FD_ZERO(&read_fds);

  //Create a socket and Bind the socket to an IP / port
  memset(&hints,0,sizeof(hints));
  hints.ai_family =AF_UNSPEC;
  hints.ai_socktype=SOCK_STREAM;
  hints.ai_flags=AI_PASSIVE;
  if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
    cerr<<"selectserver: "<<gai_strerror(rv)<<endl;
    exit(1);
  }

  for(p = ai; p != NULL; p = p->ai_next) {
    	listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listener < 0) {
			continue;
		}

		// lose the pesky "address already in use" error message
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
			close(listener);
			continue;
		}

		break;
	}

  //Not bound condition
  if(p == NULL){

    cerr<<"Server failed to bind"<<endl;
    exit(2);
  }

  freeaddrinfo(ai); //all done with this

  //REady to listen
  if(listen(listener,10)==-1){
    cerr<<"Error while listening!"<<endl;
    exit(3);
  }

  // add the listener to the master set
  FD_SET(listener, &master);

  // keep track of the biggest file descriptor
  fdmax = listener;

  //Main loop for communication
  while(true){
    read_fds=master;
    int t=select(fdmax+1, &read_fds, NULL, NULL, &tv);
    if (t == -1) {
        cerr<<"Error while select()ing"<<endl;
        exit(4);
    }

    // run through the existing connections looking for data to read
    for(i = 0; i <= fdmax; i++) {
        if (FD_ISSET(i, &read_fds)) { // we got one!!
            if (i == listener) {
            // handle new connections;
            addrlen=sizeof(remoteaddr);
            newfd= accept(listener,(struct sockaddr *)&remoteaddr,&addrlen);
                if(newfd == -1 ){
                      cerr<<"Problem with client connecting!";
                    }
                else{
                  FD_SET(newfd, &master); // add to master set
                  if (newfd > fdmax) {    // keep track of the max
                      fdmax = newfd;
                  }

                  cout<<"New connection from "<<inet_ntop(remoteaddr.ss_family,
                                get_in_addr((struct sockaddr *)&remoteaddr),
                                remoteIP,INET6_ADDRSTRLEN)<<newfd<<endl;
                }
              }
        else {
    //client data handling
    if((nbytes=recv(i,buf,sizeof(buf),0))<=0){
      // got error or connection closed by client
      if (nbytes== 0) {
          // connection closed
          cout<<"Socket "<<i <<" hung up!"<<endl;
      } else {
          cerr<<"Receiving error!"<<endl;
      }
      //Close the listening socket
      close(i);
      FD_CLR(i, &master); // remove from master set
    }
    else{
      // we got some data from a client
      for(j = 0; j <= fdmax; j++) {
          // send to everyone!
          if (FD_ISSET(j, &master)) {
              // except the listener and ourselves
              if (j != listener && j != i) {
                  if (send(j, buf, nbytes, 0) == -1) {
                      cerr<<"Error while sending!"<<endl;
                  }
              }
          }
       }
    }
  }
}
}
}
  return 0;
}
