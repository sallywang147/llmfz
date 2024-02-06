#include <fuzzer/FuzzedDataProvider.h>
#include <fftw3.h>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  if (stream.remaining_bytes() < sizeof(int)) {
    return 0;
  }

  // Consume an integer for the size of the tensor
  int tensor_size = stream.ConsumeIntegral<int>();
  if (tensor_size <= 0 || tensor_size > 1000) {
    return 0;
  }

  // Create a tensor of the desired size
  struct tensor *vecsz = fftw_mktensor_1d(tensor_size, 1, 1);
  if (vecsz == nullptr) {
    return 0;
  }

  // Consume two arrays of doubles for the input and output
  std::vector<double> I = stream.ConsumeBytes<double>(tensor_size);
  std::vector<double> O = stream.ConsumeBytes<double>(tensor_size);

  // Make sure we have enough data to fill the input array
  if (I.size() < tensor_size || O.size() < tensor_size) {
    fftw_tensor_destroy(vecsz);
    return 0;
  }

  // Create the problem
  struct problem_s *problem = fftw_mkproblem_rdft_0_d(vecsz, I.data(), O.data());
  if (problem == nullptr) {
    fftw_tensor_destroy(vecsz);
    return 0;
  }

  // Clean up
  fftw_problem_destroy(problem);
  fftw_tensor_destroy(vecsz);

  return 0;
}