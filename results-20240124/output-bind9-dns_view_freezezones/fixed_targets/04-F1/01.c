#include <isc/mem.h>
#include <isc/util.h>

#include <dns/fixedname.h>
#include <dns/name.h>
#include <dns/view.h>
#include <dns/zone.h>

#include "fuzz.h"

static isc_mem_t *mctx = NULL;
static dns_view_t *view = NULL;
static dns_zone_t *zone = NULL;
static char wd[] = "/tmp/dns-view-freezezones-XXXXXX";
static char pathbuf[PATH_MAX];

extern "C" {
int
LLVMFuzzerInitialize(int *argc ISC_ATTR_UNUSED, char ***argv ISC_ATTR_UNUSED) {
	isc_result_t result;
	dns_fixedname_t fixed;
	dns_name_t *name = dns_fixedname_initname(&fixed);

	isc_mem_create(&mctx);

	result = dst_lib_init(mctx, NULL);
	if (result != ISC_R_SUCCESS) {
		fprintf(stderr, "dst_lib_init failed: %s\n",
			isc_result_totext(result));
		return (1);
	}

	mkdtemp(wd);

	snprintf(pathbuf, sizeof(pathbuf), "%s/Ksig0key.+008+55921.key", wd);
	FILE *fd = fopen(pathbuf, "w");
	if (fd == NULL) {
		fprintf(stderr, "fopen(%s) failed\n", pathbuf);
		return (1);
	}
	fputs("AwEAAa22lgHi1vAbQvu5ETdTrm2H8rwga9tvyMa6LFiSDyevLvSv0Uo5\n"
	      "uvfrXnxaLdtBMts6e1Ly2piSH9JRbOGMNibOK4EXWhWAn8MII4SWgQAs\n"
	      "bFwtiz4HyPn2wScrUQdo8DocKiQJBanesr7vDO8fdA6Rg1e0yAtSeNti\n"
	      "e8avx46/HJa6CFs3CoE0sf6oOFSxM954AgCBTXOGNBt1Nt3Bhfqt2qyA\n"
	      "TLFii5K1jLDTZDVkoiyDXL1M7wcTwKf9METgj1eQmH3GGlRM/OJ/j8xk\n"
	      "ZiFGbL3cipWdiH48031jiV2hlc92mKn8Ya0d9AN6c44piza/JSFydZXw\n"
	      "sY32nxzjDbs=\n", fd);
	fclose(fd);

	snprintf(pathbuf, sizeof(pathbuf), "%s/Ksig0key.+008+55921.private", wd);
	fd = fopen(pathbuf, "w");
	if (fd == NULL) {
		fprintf(stderr, "fopen(%s) failed\n", pathbuf);
		return (1);
	}
	fputs("Private-key-format: v1.3\n\
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
Activate: 20220311073606\n", fd);
	fclose(fd);

	snprintf(pathbuf, sizeof(pathbuf), "%s/sig0key.db", wd);
	fd = fopen(pathbuf, "w");
	if (fd == NULL) {
		fprintf(stderr, "fopen(%s) failed\n", pathbuf);
		return (1);
	}
	fputs("sig0key. 0 IN SOA . .\n\
sig0key. 0 IN NS .\n\
sig0key. 0 IN KEY 512 3 8 AwEAAa22lgHi1vAbQvu5ETdTrm2H8rwga9tvyMa6LFiSDyevLvSv0Uo5\n\
uvfrXnxaLdtBMts6e1Ly2piSH9JRbOGMNibOK4EXWhWAn8MII4SWgQAs\n\
bFwtiz4HyPn2wScrUQdo8DocKiQJBanesr7vDO8fdA6Rg1e0yAtSeNti\n\
e8avx46/HJa6CFs3CoE0sf6oOFSxM954AgCBTXOGNBt1Nt3Bhfqt2qyA\n\
TLFii5K1jLDTZDVkoiyDXL1M7wcTwKf9METgj1eQmH3GGlRM/OJ/j8xk\n\
ZiFGbL3cipWdiH48031jiV2hlc92mKn8Ya0d9AN6c44piza/JSFydZXw\n\
sY32nxzjDbs=\n", fd);
	fclose(fd);

	dns_view_create(mctx, dns_rdataclass_in, "view", &view);
	dns_zone_create(&zone, mctx, 0);
	dns_zone_setorigin(zone, name);
	dns_zone_setclass(zone, view->rdclass);
	dns_zone_settype(zone, dns_zone_primary);
	dns_zone_setkeydirectory(zone, wd);
	dns_zone_setfile(zone, pathbuf, dns_masterformat_text,
			 &dns_master_style_default);
	dns_zone_load(zone, false);
	dns_view_addzone(view, zone);
	dns_zone_setview(zone, view);
	dns_view_freeze(view);

	return (0);
}

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	dns_view_freezezones(view, *data & 0x1);
	return (0);
}
}