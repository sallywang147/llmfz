#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <boost/asio.hpp>

using namespace boost::asio;

// Wrap the header with extern "C" {} to fix the linking issue
extern "C" {
#include "StartTcpServer.h"
}

int main() {
  // Create a thread to run the TCP server
  std::thread server_thread(StartTcpServer);

  // Wait for the server thread to finish
  server_thread.join();

  return 0;
}