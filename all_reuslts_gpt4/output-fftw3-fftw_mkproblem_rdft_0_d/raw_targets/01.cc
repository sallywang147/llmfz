#include <fuzzer/FuzzedDataProvider.h>
#include <fftw3.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define the size of the tensor
  int tensor_size = stream.ConsumeIntegralInRange<int>(1, 10);
  
  // Create the tensor
  fftw_iodim iodims[tensor_size];
  for (int i = 0; i < tensor_size; ++i) {
    iodims[i].n = stream.ConsumeIntegralInRange<int>(1, 10);
    iodims[i].is = stream.ConsumeIntegralInRange<int>(1, 10);
    iodims[i].os = stream.ConsumeIntegralInRange<int>(1, 10);
  }
  struct tensor * vecsz = fftw_mktensor(tensor_size, iodims);

  // Create the input and output arrays
  int array_size = tensor_size * 2; // Assume complex numbers
  double *I = new double[array_size];
  double *O = new double[array_size];

  // Fill the input array with fuzz data
  for (int i = 0; i < array_size; ++i) {
    I[i] = stream.ConsumeFloatingPoint<double>();
  }

  // Create the problem
  struct problem_s * problem = fftw_mkproblem_rdft_0_d(vecsz, I, O);

  // Clean up
  fftw_tensor_destroy(vecsz);
  delete[] I;
  delete[] O;

  return 0;
}