 #include "astcenc_internal.h"

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	FuzzedDataProvider stream(data, size);

	// Select a block size to test
	int xdim = stream.ConsumeIntegralInRange<int>(0, 128);
	int ydim = stream.ConsumeIntegralInRange<int>(0, 128);

	// Call the function under test
	bool is_legal = is_legal_2d_block_size(xdim, ydim);

	return 0;
}