#include <iostream>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <net/if.h>
#include <netdb.h>
#include <fcntl.h>

extern "C" {
#include <plat/plat_types.h>
#include <plat/plat_common.h>
}

#define PORT 12345

// Declare the function prototype
int RegularCommandService(int *PortNumber);

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
  int PortNumber = PORT;
  RegularCommandService(&PortNumber);
  return 0;
}

int RegularCommandService(int *PortNumber)
{
  int sockfd;
  struct sockaddr_in servaddr;

  // Create a socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    perror("socket creation failed");
    return -1;
  }

  // Set socket options
  int opt = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
  {
    perror("setsockopt failed");
    return -1;
  }

  // Bind the socket to the port
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(*PortNumber);
  if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
  {
    perror("bind failed");
    return -1;
  }

  // Listen for connections
  if (listen(sockfd, 5) < 0)
  {
    perror("listen failed");
    return -1;
  }

  // Accept connections
  int newsockfd;
  struct sockaddr_in cliaddr;
  socklen_t clilen = sizeof(cliaddr);
  while ((newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen)))
  {
    if (newsockfd < 0)
    {
      perror("accept failed");
      return -1;
    }

    // Handle the connection
    char buffer[256];
    int n;
    while ((n = read(newsockfd, buffer, sizeof(buffer))) > 0)
    {
      // Process the data
      // ...

      // Send a response
      write(newsockfd, "Hello, world!", 13);
    }

    // Close the connection
    close(newsockfd);
  }

  // Close the socket
  close(sockfd);

  return 0;
}