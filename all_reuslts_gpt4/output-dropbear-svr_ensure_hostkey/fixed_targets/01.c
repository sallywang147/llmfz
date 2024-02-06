#include "fuzz.h"
#include "session.h"
#include "fuzz-wrapfd.h"
#include "fuzz-common.h"
#include "ssh.h"
#include "dbutil.h"
#include "svr-auth.h"
#include "svr-authpasswd.h"
#include "svr-authpubkey.h"
#include "svr-chansession.h"
#include "svr-session.h"
#include "svr-service.h"
#include "svr-tcpfwd.h"
#include "svr-x11fwd.h"
#include "runopts.h"

static void setup_fuzzer(void) {
    fuzz_common_setup();
    svr_opts.nopty = 1;
    svr_opts.norootpass = 1;
    svr_opts.noagentfwd = 1;
    svr_opts.nox11fwd = 1;
    svr_opts.notcpfwd = 1;
    svr_opts.norootlogin = 1;
    svr_opts.nopassword = 1;
    svr_opts.noportfwd = 1;
    svr_opts.noscp = 1;
    svr_opts.nosftp = 1;
    svr_opts.noshell = 1;
    svr_opts.hostkey = "fuzz-hk";
    _dropbear_exit = fuzz_exit;
    _dropbear_log = fuzz_log;
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    static int once = 0;
    if (!once) {
        setup_fuzzer();
        once = 1;
    }

    if (fuzz_set_input(Data, Size) == DROPBEAR_FAILURE) {
        return 0;
    }

    m_malloc_set_epoch(1);

    if (setjmp(fuzz.jmp) == 0) {
        svr_ensure_hostkey();
    }

    m_malloc_free_epoch(1, 1);

    return 0;
}