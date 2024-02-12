 #include "fuzz.h"
#include "session.h"
#include "fuzz-wrapfd.h"
#include "debug.h"
#include "dss.h"
#include "ed25519.h"

static void setup_fuzzer(void) {
	fuzz_common_setup();
}

static buffer *verifydata;

/* Tests reading a public key and verifying a signature */
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
	static int once = 0;
	if (!once) {
		setup_fuzzer();
		verifydata = buf_new(30);
		buf_putstring(verifydata, "x", 1);
		once = 1;
	}

	if (fuzz_set_input(Data, Size) == DROPBEAR_FAILURE) {
		return 0;
	}

	m_malloc_set_epoch(1);

	if (setjmp(fuzz.jmp) == 0) {
		signkey_generate(DROPBEAR_SIGNKEY_DSS, 2048, "fuzz.key", 1);
		signkey_generate(DROPBEAR_SIGNKEY_RSA, 2048, "fuzz.key", 1);
		signkey_generate(DROPBEAR_SIGNKEY_SK_ED25519, 256, "fuzz.key", 1);
		signkey_generate(DROPBEAR_SIGNKEY_ED25519, 256, "fuzz.key", 1);
		m_malloc_free_epoch(1, 0);
	} else {
		m_malloc_free_epoch(1, 1);
		TRACE(("dropbear_exit longjmped"))
		/* dropbear_exit jumped here */
	}

	return 0;
}