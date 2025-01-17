 #include <isc/mem.h>
#include <isc/task.h>
#include <isc/util.h>

#include <dns/zt.h>

#include "fuzz.h"

static isc_mem_t *mctx = NULL;
static dns_zt_t *zt = NULL;
static func_type *loaddone = NULL;
static char *arg = NULL;
static bool newonly = false;

int
LLVMFuzzerInitialize(int *argc, char ***argv) {
	isc_result_t result;

	isc_mem_create(&mctx);

	result = dns_zt_create(mctx, &zt);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_zt_create failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	return (0);
}

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	isc_result_t result;
	FuzzedDataProvider stream(data, size);

	newonly = stream.ConsumeBool();
	loaddone = (func_type *)stream.ConsumeIntegral<uint32_t>();
	arg = (char *)stream.ConsumeIntegral<uint32_t>();

	result = dns_zt_asyncload(zt, newonly, loaddone, arg);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_zt_asyncload failed: %s\n",
			isc_result_totext(result));
	}

	return (0);
}