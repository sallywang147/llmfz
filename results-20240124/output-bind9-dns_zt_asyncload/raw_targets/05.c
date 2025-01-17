 #include <isc/buffer.h>
#include <isc/file.h>
#include <isc/mem.h>
#include <isc/mutex.h>
#include <isc/random.h>
#include <isc/result.h>
#include <isc/socket.h>
#include <isc/task.h>
#include <isc/thread.h>
#include <isc/util.h>

#include <dns/db.h>
#include <dns/dispatch.h>
#include <dns/dnssec.h>
#include <dns/journal.h>
#include <dns/keytable.h>
#include <dns/rdataset.h>
#include <dns/rdatasetiter.h>
#include <dns/rdatalist.h>
#include <dns/resolver.h>
#include <dns/zt.h>

#include <dst/dst.h>

static isc_mem_t *mctx;
static isc_taskmgr_t *taskmgr;
static isc_socketmgr_t *socketmgr;
static isc_timermgr_t *timermgr;
static isc_log_t *lctx;
static isc_entropy_t *entropy;
static isc_random_t *random;
static isc_bufferlist_t *blist;
static isc_mutex_t *lock;
static unsigned int nthreads;
static unsigned int nrunning;
static int nfiles;
static unsigned int nerrors;
static unsigned int nsuccesses;
static unsigned int nskipped;

static void
task_done(isc_task_t *task, isc_event_t *event) {
	isc_result_t result;
	struct dns_zt *zt = event->ev_arg;

	UNUSED(task);

	result = dns_zt_asyncload(zt, true, NULL, NULL);
	if (result != ISC_R_SUCCESS) {
		isc_log_write(lctx, ISC_LOG_ERROR, "dns_zt_asyncload() failed: %s",
			      isc_result_totext(result));
		nerrors++;
	} else {
		nsuccesses++;
	}

	isc_task_detach(&task);
	isc_event_free(&event);
	dns_zt_detach(&zt);

	isc_mutex_lock(lock);
	nrunning--;
	isc_mutex_unlock(lock);
}

static void
run_task(void *arg) {
	isc_task_t *task;
	isc_event_t *event;
	struct dns_zt *zt;

	UNUSED(arg);

	isc_mutex_lock(lock);
	while (nrunning >= nthreads)
		isc_cond_wait(&taskmgr->cond, lock);
	nrunning++;
	isc_mutex_unlock(lock);

	zt = dns_zt_create(mctx, nfiles);
	if (zt == NULL) {
		isc_log_write(lctx, ISC_LOG_ERROR, "dns_zt_create() failed");
		nerrors++;
		goto cleanup;
	}

	event = isc_event_allocate(mctx, taskmgr, task_done, zt);
	if (event == NULL) {
		isc_log_write(lctx, ISC_LOG_ERROR, "isc_event_allocate() failed");
		nerrors++;
		goto cleanup;
	}

	task = isc_task_create(taskmgr, 0, &run_task, NULL);
	if (task == NULL) {
		isc_log_write(lctx, ISC_LOG_ERROR, "isc_task_create() failed");
		nerrors++;
		goto cleanup;
	}

	isc_task_onshutdown(task, isc_event_free, event);

	isc_event_activate(event, task, ISC_TIME_NOW);
	isc_task_detach(&task);

	return;

 cleanup:
	isc_mutex_lock(lock);
	nrunning--;
	isc_mutex_unlock(lock);
}

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	isc_result_t result;
	isc_task_t *task;
	unsigned int i;

	if (mctx == NULL) {
		mctx = isc_mem_create(0, 0);
		if (mctx == NULL)
			return (0);

		taskmgr = isc_taskmgr_create(mctx, 100, 0);
		if (taskmgr == NULL)
			return (0);

		socketmgr = isc_socketmgr_create(mctx, 100);
		if (socketmgr == NULL)
			return (0);

		timermgr = isc_timermgr_create(mctx, 100);
		if (timermgr == NULL)
			return (0);

		lctx = isc_log_create(mctx, &isc_log_default_category,
				      &isc_log_default_methods);
		if (lctx == NULL)
			return (0);

		entropy = isc_entropy_create(mctx);
		if (entropy == NULL)
			return (0);

		random = isc_random_create(mctx, entropy);
		if (random == NULL)
			return (0);

		blist = isc_bufferlist_create(mctx);
		if (blist == NULL)
			return (0);

		lock = isc_mutex_create(mctx);
		if (lock == NULL)
			return (0);
	}

	nthreads = data[0];
	nfiles = data[1];
	if (nfiles > 10000)
		nfiles = 10000;

	for (i = 0; i < nthreads; i++) {
		task = isc_task_create(taskmgr, 0, &run_task, NULL);
		if (task == NULL) {
			isc_log_write(lctx, ISC_LOG_ERROR,
				      "isc_task_create() failed");
			nerrors++;
			continue;
		}

		isc_task_detach(&task);
	}

	isc_mutex_lock(lock);
	while (nrunning > 0)
		isc_cond_wait(&taskmgr->cond, lock);
	isc_mutex_unlock(lock);

	result = isc_mem_destroy(&mctx);
	if (result != ISC_R_SUCCESS)
		return (0);

	return (0);
}