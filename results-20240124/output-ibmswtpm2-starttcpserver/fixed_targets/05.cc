#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <boost/asio.hpp>

using namespace boost::asio;

// Include the header file that defines the StartTcpServer function
#include "StartTcpServer.h"

int main() {
  // Create a thread to run the TCP server
  std::thread server_thread(StartTcpServer);

  // Wait for the server thread to finish
  server_thread.join();

  return 0;
}