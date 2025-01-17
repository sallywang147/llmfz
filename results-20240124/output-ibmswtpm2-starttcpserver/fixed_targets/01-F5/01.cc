#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

// Include the header file and wrap it with extern "C" {} to fix the linking issue.
extern "C" {
#include "StartTcpServer.h"
}

int main() {
  // Create a mutex and a condition variable to synchronize the main thread and the worker thread.
  mutex mtx;
  condition_variable cv;

  // Create a boolean flag to indicate whether the server has started.
  bool server_started = false;

  // Create a worker thread to start the TCP server.
  thread worker([&]() {
    // Start the TCP server.
    StartTcpServer();

    // Signal the main thread that the server has started.
    lock_guard<mutex> lock(mtx);
    server_started = true;
    cv.notify_one();
  });

  // Wait until the server has started.
  {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [&]() { return server_started; });
  }

  // Keep the main thread alive until the user presses Enter.
  cout << "Press Enter to stop the server..." << endl;
  cin.get();

  // Stop the TCP server.
  StopTcpServer();

  // Join the worker thread.
  worker.join();

  return 0;
}