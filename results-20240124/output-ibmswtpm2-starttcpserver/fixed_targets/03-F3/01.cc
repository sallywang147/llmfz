#include <iostream>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

extern "C" {
#include <libwebsockets.h>
}

using namespace std;

void StartTcpServer() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    cerr << "Error creating socket" << endl;
    return;
  }

  struct sockaddr_in servaddr;
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(8080);

  if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
    cerr << "Error binding socket" << endl;
    return;
  }

  if (listen(sockfd, 5) == -1) {
    cerr << "Error listening on socket" << endl;
    return;
  }

  while (true) {
    int connfd = accept(sockfd, (struct sockaddr *)NULL, NULL);
    if (connfd == -1) {
      cerr << "Error accepting connection" << endl;
      return;
    }

    thread t(handle_connection, connfd);
    t.detach();
  }

  close(sockfd);
}

int main() {
  StartTcpServer();
  return 0;
}