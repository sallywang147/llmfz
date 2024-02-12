#include <isc/buffer.h>
#include <isc/mem.h>
#include <isc/task.h>
#include <isc/util.h>

#include <dns/db.h>
#include <dns/dispatch.h>
#include <dns/master.h>
#include <dns/message.h>
#include <dns/rdataset.h>
#include <dns/rdataclass.h>
#include <dns/rdatalist.h>
#include <dns/rdatastruct.h>
#include <dns/rdatatype.h>
#include <dns/resolver.h>
#include <dns/zone.h>
#include <dns/zt.h>

#include "fuzz.h"

static isc_mem_t *mctx = NULL;
static dns_zt_t *zt = NULL;
static dns_view_t *view = NULL;
static bool destroy_zt = false;

extern "C" {
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
	destroy_zt = true;

	result = dns_zt_setdb(zt, NULL);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_zt_setdb failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	result = dns_zt_setdispatch(zt, NULL);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_zt_setdispatch failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	result = dns_zt_setresolver(zt, NULL);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_zt_setresolver failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	result = dns_view_create(mctx, dns_rdataclass_in, "view", &view);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_view_create failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	dns_view_freeze(view);

	return (0);
}

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	isc_result_t result;
	bool freeze = (*data & 0x80) != 0;

	result = dns_zt_freezezones(zt, view, freeze);
	if (debug) {
		fprintf(stderr, "dns_zt_freezezones => %s\n",
			isc_result_totext(result));
	}
	if (result != ISC_R_SUCCESS) {
		return (0);
	}

	return (0);
}
}