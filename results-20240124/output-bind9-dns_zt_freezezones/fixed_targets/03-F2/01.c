#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include <isc/buffer.h>
#include <isc/commandline.h>
#include <isc/file.h>
#include <isc/mem.h>
#include <isc/result.h>
#include <isc/string.h>
#include <isc/tid.h>
#include <isc/util.h>

#include <dns/fixedname.h>
#include <dns/message.h>
#include <dns/name.h>
#include <dns/rcode.h>
#include <dns/tsig.h>
#include <dns/view.h>
#include <dns/zone.h>

#include "fuzz.h"

bool debug = false;

static isc_mem_t *mctx = NULL;

/*
 *	Packet dumps of validily signed request ./IN/SOA
 *	requests.
 *
 *	TSIG:
 *
 *	0x0000:  600b 0900 006a 1140 0000 0000 0000 0000
 *	0x0010:  0000 0000 0001 0000 0000 0000 0000 0000
 *	0x0020:  0000 0000 0000 0001 cc88 0035 006a 007d
 *	0x0030:  1dfa 0000 0001 0000 0000 0001 0000 0600
 *	0x0040:  0108 7473 6967 2d6b 6579 0000 fa00 ff00
 *	0x0050:  0000 0000 3d0b 686d 6163 2d73 6861 3235
 *	0x0060:  3600 0000 622a cce1 012c 0020 224d 5807
 *	0x0070:  648d 1400 9d8e fc1c d049 55e9 cc90 2187
 *	0x0080:  3b5f af5c 8899 dc27 c8df b34b 1dfa 0000
 *	0x0090:  0000
 *
 *	SIG(0):
 *
 *	0x0000:  6004 0e00 013f 1140 0000 0000 0000 0000
 *	0x0010:  0000 0000 0001 0000 0000 0000 0000 0000
 *	0x0020:  0000 0000 0000 0001 c0a7 0035 013f 0152
 *	0x0030:  0000 0000 0001 0000 0000 0001 0000 0600
 *	0x0040:  0100 0018 00ff 0000 0000 011b 0000 0800
 *	0x0050:  0000 0000 622a ce0d 622a cbb5 da71 0773
 *	0x0060:  6967 306b 6579 0068 988b 27bf 5c89 5270
 *	0x0070:  c5ba ea8b 2e10 0512 9b44 48d3 69de b7ec
 *	0x0080:  7c67 15f3 6bc7 b0dc 277b e8f1 6979 4c89
 *	0x0090:  149a 0203 30a1 c0b7 a711 ee8a 8d90 ebb9
 *	0x00a0:  9e33 dd65 33d5 5d1d 90db cf9c bb6a b346
 *	0x00b0:  568f a399 71d7 c877 616d 2fb7 0f86 963f
 *	0x00c0:  aa00 850d 180a 9f83 cd4b d115 c79f 64c9
 *	0x00d0:  ff05 e751 6810 28b3 2249 c4ba 2d8d 57ba
 *	0x00e0:  9aad f1fc b34e c237 9465 04fd fe4d 19c9
 *	0x00f0:  2368 ec8e 7097 eaea e067 2b9c 06eb c383
 *	0x0100:  e901 a11e 606b 4cce c12a 0e57 8c09 b7cb
 *	0x0110:  23bb ec05 b68b 1852 9288 b665 fe89 cf62
 *	0x0120:  0a41 5e5a acbe 6903 cbb7 e7b6 cab4 e4a2
 *	0x0130:  b98f 884f c09d 5b39 c695 c84c 9a92 f110
 *	0x0140:  ccc3 f2ee 313f a2a1 1cda 5aa2 faec d593
 *	0x0150:  4514 724a 868f 94b9 0547 4dc9 7b73 c85e
 *	0x0160:  544c 73d4 e892 f9
 */

#define HMACSHA256 "\x0bhmac-sha256"

static isc_stdtime_t fuzztime = 0x622acce1;
static isc_loopmgr_t *loopmgr = NULL;
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
Modulus: rbaWAeLW8BtC+7kRN1OubYfyvCBr22/IxrosWJIPJ68u9K/RSjm69+tefFot20Ey2zp7UvLamJIf0lFs4Yw2Js4rgRdaFYCfwwgjhJaBACxsXC2LPgfI+fbBJytRB2jwOhwqJAkFqd6yvu8M7x90DpGDV7TIC1J422J7xq/Hjr8clroIWzcKgTSx/qg4VLEz3ngCAIFNc4Y0G3U23cGF+q3arIBMsWKLkrWMsNNkNWSiLINcvUzvBxPAp/ROCPV5CYfcYaVEz84n+PzGRmIUZsvdyKlZ2IfjzTfWOJXaGVz3aYqfxhrR30A3pzjimLNr8lIXJ1lfCxjfafHOMNuw==\n\
PublicExponent: AQAB\n\
PrivateExponent: GDfclFkR5ToFGH9rMTRMnP73Q5dzjLgkx4vyHcuzKtxcvAans4+hNj+NazckAy2E+mpzV2j95TJ4wZjSM2RvB5xLwBIc4Dg6oyAHL6Ikoae6gw64cHFOaYb808n8CyqWqfX+QWAz9sRSVZXnTuPViX3A+svR7ejVak9Bzr1NTDm0DFlrhaKVCYA++dKVZerfuNiXT/jQvrc4wMCa7WWsfLsFO8aTNkEhqUnmS9c5VYgr7MkCV4ENDBcISpQc9wElI0hl12QPaSj8iSdk9liYp+HTiOxOyp6BGGuecKAoQijMwrZy4qExdOxvowptll8+nZLtwGRn/un/xvIZY5OLAQ==\n\
Prime1: ww3C6jwnrLQik/zxSgC0KuqgHq68cCjiRjwK2/euzs7NkMevFpXvV0cWO8x1/wKC1mszVLsUaKTvH6fzRsXfz5MPihzNzUYFwvobKVLserSxEwHNk+FKUU+q07Kf8WWnCqX5nX9QzVG1q4J8Q44N49I5S480jHLGYbyLZrEYMQE=\n\
Prime2: 4/3Ozq/8vRgcO4bieFs4CbZR7C98HiTi65SiLBIKY09mDfCleZI0uurAYBluZJgHS5AC5cdyHFuJr3uKxvD+Mgdlru40U6cSCEdK7HAhyUGZUndWl28wyMEB6Kke1/owxVn0S4RKLPOgFI2668H6JObaqXf0wyY89RdVQP6VQrs=\n\
Exponent1: Tbr9MyVX1j5PDVSev5P6OKQZvUB7PeM9ESo6VaCl3CqTxx+cic6ke86LcLcxSrewdkxwP1LydiVMWfwvOcP/RhRf+/Uwmp5OC35qNpSiQuAhNObiCw2b9T1fYU/s52FQKTEtgXNMOxZV5IxyguVoaaLMTG08TsAqiKZ/kyP99QE=\n\
Exponent2: Q4qSNKrwLbixzHS2LL+hR0dK17RtiaSV0QKUVIf3qdoAusp6yxwkIOegnBeMm6JqLtl38kh2pq37iRAJWcxVEc8dMYiB2fJZpjgwmwDREYUsfcC611vqUN7UyO8pIwSMZDq045ZKPyzhVJV0NZmemEYHq0LNMO7oCheiewGwiDc=\n\
Coefficient: T2u/J4NgyO+OqoLpXBIpTBzqrvDk8tb0feYgsp5d16hHvbXxNkMUR8cI07RdbI9HnEldtmhAnbQ6SvFiy2YYjpw/1Fz2WwdxRqLaDV7UlhrT+CqltvU9d/N/xThBNKDa23Wf5Vat+HRiLHSgzsY1PseVCWN+g4azuK2D8+DLeHE=\n\
Created: 20220311073606\n\
Publish: 20220311073606\n\
Activate: 20220311073606\n";

static char f3[] = "sig0key.db";
static char c3[] = "sig0key. 0 IN SOA . . 0 0 0 0 0\n\
sig0key. 0 IN NS .\n\
sig0key. 0 IN KEY 512 3 8 AwEAAa22lgHi1vAbQvu5ETdTrm2H8rwga9tvyMa6LFiSDyevLvSv0Uo5 uvfrXnxaLdtBMts6e1Ly2piSH9JRbOGMNibOK4EXWhWAn8MII4SWgQAs bFwtiz4HyPn2wScrUQdo8DocKiQJBanesr7vDO8fdA6Rg1e0yAtSeNti e8avx46/HJa6CFs3CoE0sf6oOFSxM954AgCBTXOGNBt1Nt3Bhfqt2qyA TLFii5K1jLDTZDVkoiyDXL1M7wcTwKf9METgj1eQmH3GGlRM/OJ/j8xk ZiFGbL3cipWdiH48031jiV2hlc92mKn8Ya0d9AN6c44piza/JSFydZXw sY32nxzjDbs=\n";

static bool destroy_dst = false;

extern "C" int
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

	isc_loopmgr_create(mctx, 1, &loopmgr);

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

extern "C" int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	isc_result_t result;
	bool freeze = false;

	/*
	 * The first octet determines whether zones should be frozen.
	 */
	if (size > 65535 || size < 1) {
		return (0);
	}

	freeze = (*data & 0x80) != 0;

	result = dns_zt_freezezones(NULL, view, freeze);
	if (debug) {
		fprintf(stderr, "dns_zt_freezezones => %s\n",
			isc_result_totext(result));
	}
	return (0);
}