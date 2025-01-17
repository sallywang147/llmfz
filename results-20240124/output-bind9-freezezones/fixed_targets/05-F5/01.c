#include <isc/mem.h>
#include <isc/stdtime.h>
#include <isc/util.h>

#include <dns/db.h>
#include <dns/dispatch.h>
#include <dns/events.h>
#include <dns/masterdump.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataset.h>
#include <dns/rdatatype.h>
#include <dns/rdclass.h>
#include <dns/request.h>
#include <dns/soa.h>
#include <dns/tsig.h>
#include <dns/view.h>
#include <dns/zone.h>

#include "fuzz.h"

static isc_mem_t *mctx = NULL;
static dns_view_t *view = NULL;
static dns_tsigkey_t *tsigkey = NULL;
static dns_tsigkeyring_t *ring = NULL;
static dns_tsigkeyring_t *emptyring = NULL;
static char *wd = NULL;
static char template[] = "/tmp/dns-message-checksig-XXXXXX";

static char f1[] = "Ksig0key.+008+55921.key";
static char c1[] = "sig0key. IN KEY 512 3 8 "
		   "AwEAAa22lgHi1vAbQvu5ETdTrm2H8rwga9tvyMa6LFiSDyevLvSv0Uo5 "
		   "uvfrXnxaLdtBMts6e1Ly2piSH9JRbOGMNibOK4EXWhWAn8MII4SWgQAs "
		   "bFwtiz4HyPn2wScrUQdo8DocKiQJBanesr7vDO8fdA6Rg1e0yAtSeNti "
		   "e8avx46/HJa6CFs3CoE0sf6oOFSxM954AgCBTXOGNBt1Nt3Bhfqt2qyA "
		   "TLFii5K1jLDTZDVkoiyDXL1M7wcTwKf9METgj1eQmH3GGlRM/OJ/j8xk "
		   "ZiFGbL3cipWdiH48031jiV2hlc92mKn8Ya0d9AN6c44piza/JSFydZXw "
		   "sY32nxzjDbs=\n";

static char f2[] = "Ksig0key.+008+55921.private";
static char c2[] = "Private-key-format: v1.3\n\
Algorithm: 8 (RSASHA256)\n\
Modulus: rbaWAeLW8BtC+7kRN1OubYfyvCBr22/IxrosWJIPJ68u9K/RSjm69+tefFot20Ey2zp7UvLamJIf0lFs4Yw2Js4rgRdaFYCfwwgjhJaBACxsXC2LPgfI+fbBJytRB2jwOhwqJAkFqd6yvu8M7x90DpGDV7TIC1J422J7xq/Hjr8clroIWzcKgTSx/qg4VLEz3ngCAIFNc4Y0G3U23cGF+q3arIBMsWKLkrWMsNNkNWSiLINcvUzvBxPAp/0wROCPV5CYfcYaVEz84n+PzGRmIUZsvdyKlZ2IfjzTfWOJXaGVz3aYqfxhrR30A3pzjimLNr8lIXJ1lfCxjfafHOMNuw==\n\
PublicExponent: AQAB\n\
PrivateExponent: GDfclFkR5ToFGH9rMTRMnP73Q5dzjLgkx4vyHcuzKtxcvAans4+hNj+NazckAy2E+mpzV2j95TJ4wZjSM2RvB5xLwBIc4Dg6oyAHL6Ikoae6gw64cHFOaYb808n8CyqWqfX+QWAz9sRSVZXnTuPViX3A+svR7ejVak9Bzr1NTDm0DFlrhaKVCYA++dKVZerfuNiXT/jQvrc4wMCa7WWsfLsFO8aTNkEhqUnmS9c5VYgr7MkCV4ENDBcISpQc9wElI0hl12QPaSj8iSdk9liYp+HTiOxOyp6BGGuecKAoQijMwrZy4qExdOxvowptll8+nZLtwGRn/un/xvIZY5OLAQ==\n\
Prime1: ww3C6jwnrLQik/zxSgC0KuqgHq68cCjiRjwK2/euzs7NkMevFpXvV0cWO8x1/wKC1mszVLsUaKTvH6fzRsXfz5MPihzNzUYFwvobKVLserSxEwHNk+FKUU+q07Kf8WWnCqX5nX9QzVG1q4J8Q44N49I5S480jHLGYbyLZrEYMQE=\n\
Prime2: 4/3Ozq/8vRgcO4bieFs4CbZR7C98HiTi65SiLBIKY09mDfCleZI0uurAYBluZJgHS5AC5cdyHFuJr3uKxvD+Mgdlru40U6cSCEdK7HAhyUGZUndWl28wyMEB6Kke1/owxVn0S4RKLPOgFI2668H6JObaqXf0wyY89RdVQP6VQrs=\n\
Exponent1: Tbr9MyVX1j5PDVSev5P6OKQZvUB7PeM9ESo6VaCl3CqTxx+cic6ke86LcLcxSrewdkxwP1LydiVMWfwvOcP/RhRf+/Uwmp5OC35qNpSiQuAhNObiCw2b9T1fYU/s52FQKTEtgXNMOxZV5IxyguVoaaLMTG08TsAqiKZ/kyP99QE=\n\
Exponent2: Q4qSNKrwLbixzHS2LL+hR0dK17RtiaSV0QKUVIf3qdoAusp6yxwkIOegnBeMm6JqLtl38kh2pq37iRAJWcxVEc8dMYiB2fJZpjgwmwDREYUsfcC611vqUN7UyO8pIwSMZDq045ZKPyzhVJV0NZmemEYHq0LNMO7oCheiewGwiDc=\n\
Coefficient: T2u/J4NgyO+OqoLpXBIpTBzqrvDk8tb0feYgsp5d16hHvbXxNkMUR8cI07RdbI9HnEldtmhAnbQ6SvFiy2YYjpw/Fz2WwdxRqLaDV7UlhrT+CqltvU9d/N/xThBNKDa23Wf5Vat+HRiLHSgzsY1PseVCWN+g4azuK2D8+DLeHE=\n\
Created: 20220311073606\n\
Publish: 20220311073606\n\
Activate: 20220311073606\n";

static char f3[] = "sig0key.db";
static char c3[] = "sig0key. 0 IN SOA . . 0 0 0 0 0\n\
sig0key. 0 IN NS .\n\
sig0key. 0 IN KEY 512 3 8 AwEAAa22lgHi1vAbQvu5ETdTrm2H8rwga9tvyMa6LFiSDyevLvSv0Uo5 uvfrXnxaLdtBMts6e1Ly2piSH9JRbOGMNibOK4EXWhWAn8MII4SWgQAs bFwtiz4HyPn2wScrUQdo8DocKiQJBanesr7vDO8fdA6Rg1e0yAtSeNti e8avx46/HJa6CFs3CoE0sf6oOFSxM954AgCBTXOGNBt1Nt3Bhfqt2qyA TLFii5K1jLDTZDVkoiyDXL1M7wcTwKf9METgj1eQmH3GGlRM/OJ/j8xk ZiFGbL3cipWdiH48031jiV2hlc92mKn8Ya0d9AN6c44piza/JSFydZXw sY32nxzjDbs=\n";

static bool destroy_dst = false;

extern "C" {
int
LLVMFuzzerInitialize(int *argc ISC_ATTR_UNUSED, char ***argv ISC_ATTR_UNUSED) {
	isc_result_t result;
	dns_fixedname_t fixed;
	dns_name_t *name = dns_fixedname_initname(&fixed);
	unsigned char secret[16] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
				     0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
				     0xff, 0xff, 0xff, 0xff };
	dns_zone_t *zone = NULL;
	char pathbuf[PATH_MAX];
	FILE *fd;

	wd = mkdtemp(template);
	if (wd == NULL) {
		fprintf(stderr, "mkdtemp failed\n");
		return (1);
	}

	snprintf(pathbuf, sizeof(pathbuf), "%s/%s", wd, f1);
	fd = fopen(pathbuf, "w");
	if (fd == NULL) {
		fprintf(stderr, "fopen(%s) failed\n", pathbuf);
		return (1);
	}
	fputs(c1, fd);
	fclose(fd);

	snprintf(pathbuf, sizeof(pathbuf), "%s/%s", wd, f2);
	fd = fopen(pathbuf, "w");
	if (fd == NULL) {
		fprintf(stderr, "fopen(%s) failed\n", pathbuf);
		return (1);
	}
	fputs(c2, fd);
	fclose(fd);

	snprintf(pathbuf, sizeof(pathbuf), "%s/%s", wd, f3);
	fd = fopen(pathbuf, "w");
	if (fd == NULL) {
		fprintf(stderr, "fopen(%s) failed\n", pathbuf);
		return (1);
	}
	fputs(c3, fd);
	fclose(fd);

	isc_mem_create(&mctx);

	result = dst_lib_init(mctx, NULL);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dst_lib_init failed: %s\n",
			isc_result_totext(result));
		return (1);
	}
	destroy_dst = true;

	result = dns_view_create(mctx, dns_rdataclass_in, "view", &view);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_view_create failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	dns_tsigkeyring_create(mctx, &ring);
	dns_tsigkeyring_create(mctx, &emptyring);

	result = dns_name_fromstring(name, "tsig-key", 0, NULL);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_name_fromstring failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	result = dns_tsigkey_create(name, DST_ALG_HMACSHA256, secret,
				    sizeof(secret), mctx, &tsigkey);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_tsigkey_create failed: %s\n",
			isc_result_totext(result));
		return (1);
	}
	result = dns_tsigkeyring_add(ring, tsigkey);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_tsigkeyring_add failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	result = dns_name_fromstring(name, "sig0key", 0, NULL);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_name_fromstring failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	dns_zone_create(&zone, mctx, 0);

	result = dns_zone_setorigin(zone, name);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_zone_setorigin failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	dns_zone_setclass(zone, view->rdclass);
	dns_zone_settype(zone, dns_zone_primary);

	result = dns_zone_setkeydirectory(zone, wd);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_zone_setkeydirectory failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	result = dns_zone_setfile(zone, pathbuf, dns_masterformat_text,
				  &dns_master_style_default);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_zone_setfile failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	result = dns_zone_load(zone, false);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_zone_load failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	result = dns_view_addzone(view, zone);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dns_view_addzone failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	dns_zone_setview(zone, view);
	dns_view_freeze(view);

	dns_zone_detach(&zone);

	return (0);
}

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	isc_result_t result;
	char uap[256];

	/*
	 * The first octet affects setup.
	 * Octet 1 determines whether a TSIG key is added and which type
	 * (addasig, addtsig), whether time should be adjusted (addtime,
	 * subtime), whether dns_message_setquerytsig and dns_message_settsigkey
	 * have been called, whether there is a keyring available with the
	 * TSIG key or a view is defined.
	 *
	 * The second octet defines if the message is a response and the
	 * opcode.
	 */
	if (size > 65535 || size < 2) {
		return (0);
	}

	if ((*data & 0x80) != 0) {
		snprintf(uap, sizeof(uap), "update-uap-zone");
	} else {
		snprintf(uap, sizeof(uap), "freeze");
	}

	result = freezezones(NULL, uap);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "freezezones failed: %s\n",
			isc_result_totext(result));
	}

	return (0);
}
}