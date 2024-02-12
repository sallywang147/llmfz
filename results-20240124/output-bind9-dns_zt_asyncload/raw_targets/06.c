 #include <isc/mem.h>
#include <isc/task.h>
#include <isc/thread.h>
#include <isc/util.h>

#include <dns/db.h>
#include <dns/dbiterator.h>
#include <dns/zt.h>

#include "fuzz.h"

static isc_mem_t *mctx = NULL;
static isc_taskmgr_t *taskmgr = NULL;
static isc_threadmgr_t *threadmgr = NULL;
static isc_task_t *task = NULL;

static dns_zt_t *zt = NULL;
static dns_db_t *db = NULL;
static dns_dbiterator_t *dbiterator = NULL;

static isc_result_t
db_load(dns_zt_t *zt, bool newonly, void *arg) {
	return (ISC_R_SUCCESS);
}

static void
db_load_done(void *arg, isc_result_t result) {
	return;
}

int
LLVMFuzzerInitialize(int *argc ISC_ATTR_UNUSED, char ***argv ISC_ATTR_UNUSED) {
	isc_result_t result;

	isc_mem_create(&mctx);
	isc_taskmgr_create(mctx, 1, 0, &taskmgr);
	isc_threadmgr_create(mctx, 1, &threadmgr);

	result = dns_zt_create(mctx, &zt);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_zt_create failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	result = dns_db_create(mctx, "rbt", dns_rdataclass_in, &db);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_db_create failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	result = dns_dbiterator_create(mctx, db, 0, &dbiterator);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_dbiterator_create failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	return (0);
}

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	isc_result_t result;

	result = dns_zt_asyncload(zt, false, db_load, (char *)data);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_zt_asyncload failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	db_load_done(NULL, result);

	return (0);
}