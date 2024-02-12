#include <isc/mem.h>
#include <isc/result.h>
#include <isc/util.h>

#include <dns/db.h>
#include <dns/dbiterator.h>
#include <dns/masterdump.h>
#include <dns/zt.h>

extern "C" {
#include <isc/siphash.h>
}

static isc_mem_t *mctx = NULL;
static dns_zt_t *zt = NULL;

int
LLVMFuzzerInitialize(int *argc ISC_ATTR_UNUSED, char ***argv ISC_ATTR_UNUSED) {
	isc_result_t result;

	isc__mem_create(&mctx, 0);

	result = dns_zt_create(mctx, &zt);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_zt_create failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	result = dns_zt_load(zt, "fuzz.db");
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_zt_load failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	return (0);
}

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	isc_result_t result;
	dns_view_t *view = NULL;
	bool freeze;

	if (size < 1) {
		return (0);
	}

	freeze = (*data & 0x80) != 0;

	result = dns_zt_view_create(zt, "view", &view);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_zt_view_create failed: %s\n",
			isc_result_totext(result));
		return (0);
	}

	result = dns_zt_freezezones(zt, view, freeze);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_zt_freezezones failed: %s\n",
			isc_result_totext(result));
		return (0);
	}

	dns_view_detach(&view);

	return (0);
}