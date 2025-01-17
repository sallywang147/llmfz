 #include <isc/list.h>
#include <isc/mem.h>
#include <isc/util.h>

#include "dns/zt.h"
#include "dns/zt_private.h"

#include "fuzz.h"

static isc_mem_t *mctx = NULL;
static dns_zt_t *zt = NULL;

int
LLVMFuzzerInitialize(int *argc ISC_ATTR_UNUSED, char ***argv ISC_ATTR_UNUSED) {
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
	bool newonly = false;
	func_type *loaddone = NULL;
	char *arg = NULL;

	if (size < 1) {
		return (0);
	}
	newonly = (*data & 0x80) != 0;
	data++;
	size--;

	result = dns_zt_asyncload(zt, newonly, loaddone, arg);
	if (debug) {
		fprintf(stderr, "dns_zt_asyncload => %s\n",
			isc_result_totext(result));
	}

	return (0);
}