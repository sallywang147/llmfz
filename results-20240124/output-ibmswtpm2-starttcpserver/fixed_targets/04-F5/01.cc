#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

extern "C" {
#include "StartTcpServer.h"
}

int main() {
  int server_fd = StartTcpServer(8080);
  if (server_fd < 0) {
    std::cerr << "Failed to start TCP server" << std::endl;
    return -1;
  }

  // Accept connections and handle requests here

  close(server_fd);
  return 0;
}