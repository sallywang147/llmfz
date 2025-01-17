#include "astcenc_internal.h"

#include <fuzzer/FuzzedDataProvider.h>
#include <array>
#include <vector>

struct BlockSizes
{
	int x;
	int y;
	int z;
};

std::array<BlockSizes, 3> testSz {{
	{ 4,  4, 1}, // Highest bitrate
	{12, 12, 1}, // Largest 2D block
	{6,  6,  6}  // Largest 3D block
}};

std::array<block_size_descriptor, 3> testBSD;

/**
 * @brief Utility function to create all of the block size descriptors needed.
 *
 * This is triggered once via a static initializer.
 *
 * Triggering once is important so that we only create a single BSD per block
 * size we need, rather than one per fuzzer iteration (it's expensive). This
 * improves fuzzer throughput by ~ 1000x!
 *
 * Triggering via a static initializer, rather than a lazy init in the fuzzer
 * function, is important because is means that the BSD is allocated before
 * fuzzing starts. This means that leaksanitizer will ignore the fact that we
 * "leak" the dynamic allocations inside the BSD (we never call term()).
 */
bool bsd_initializer()
{
	for (int i = 0; i < testSz.size(); i++)
	{
		init_block_size_descriptor(
		    testSz[i].x,
		    testSz[i].y,
		    testSz[i].z,
		    false,
		    4,
		    1.0f,
		    &testBSD[i]);
	}

	return true;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	// Preinitialize the block size descriptors we need
	static bool init = bsd_initializer();

	// Must have 4 (select block size) and 16 (payload) bytes
	if (size < 4 + 16)
	{
		return 0;
	}

	FuzzedDataProvider stream(data, size);

	// Select a block size to test
	int i = stream.ConsumeIntegralInRange<int>(0, testSz.size() - 1);

	// Populate the symbolic block
	std::vector<uint8_t> buffer = stream.ConsumeBytes<uint8_t>(16);
	symbolic_compressed_block scb;
	std::memcpy(&scb, buffer.data(), 16);

	// Call the function under test
	physical_compressed_block pcb;
	symbolic_to_physical(testBSD[i], scb, &pcb);

	return 0;
}