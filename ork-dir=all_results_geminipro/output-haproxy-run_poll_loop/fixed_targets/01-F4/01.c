#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include <poll.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Initialize the fuzzer.
  FuzzedDataProvider provider(data, size);

  // Read the input data.
  std::vector<uint8_t> input_data = provider.ConsumeRemainingBytes<uint8_t>();

  // Call the function under test.
  run_poll_loop(input_data.data(), input_data.size());

  // Return 0 to indicate success.
  return 0;
}

// Define the run_poll_loop function.
void run_poll_loop(const uint8_t* data, size_t size) {
  // Initialize the pollfd structure.
  struct pollfd pfd;
  pfd.fd = 0;  // File descriptor for stdin.
  pfd.events = POLLIN;  // Wait for input.

  // Poll for input.
  int ret = poll(&pfd, 1, 1000);  // Timeout after 1 second.

  // Check the result of the poll.
  if (ret == -1) {
    // An error occurred.
    perror("poll");
    exit(EXIT_FAILURE);
  } else if (ret == 0) {
    // No input received within the timeout.
    printf("No input received.\n");
  } else {
    // Input received.
    printf("Input received: ");
    for (size_t i = 0; i < size; i++) {
      printf("%02X ", data[i]);
    }
    printf("\n");
  }
}