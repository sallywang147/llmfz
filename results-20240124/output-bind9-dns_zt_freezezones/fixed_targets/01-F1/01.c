#include <stdint.h>
#include <stdlib.h>

#include <isc/buffer.h>
#include <isc/mem.h>
#include <isc/result.h>
#include <isc/util.h>

#include <dns/db.h>
#include <dns/fixedname.h>
#include <dns/journal.h>
#include <dns/message.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rdataset.h>
#include <dns/rdatatype.h>
#include <dns/resolver.h>
#include <dns/result.h>
#include <dns/tsig.h>
#include <dns/view.h>
#include <dns/zone.h>
#include <dns/zt.h>

#include "fuzz.h"

static isc_mem_t *mctx = NULL;

static isc_result_t
create_message(dns_message_t **messagep, const uint8_t *data, size_t size,
	       bool addasig, bool addtsig) {
	isc_result_t result;
	dns_message_t *message = NULL;
	isc_buffer_t b;
	static unsigned char buf[65535];

	isc_buffer_init(&b, buf, sizeof(buf));

	/* Message ID */
	isc_buffer_putuint16(&b, 0);

	/* QR, Opcode, other flags = 0, rcode = 0 */
	isc_buffer_putuint16(&b, (*data & 0x1f) << 11);
	/* Counts */
	isc_buffer_putuint16(&b, 1);
	isc_buffer_putuint16(&b, 0);
	isc_buffer_putuint16(&b, 0);
	isc_buffer_putuint16(&b, addasig ? 1 : 0);

	/* Question ./IN/SOA */
	isc_buffer_putuint8(&b, 0);
	isc_buffer_putuint16(&b, 6);
	isc_buffer_putuint16(&b, 1);

	if (addasig) {
		/* Signature */
		if (addtsig) {
			const unsigned char keyname[] = "\x08tsig-key";
			isc_buffer_putmem(&b, keyname, sizeof(keyname));
			isc_buffer_putuint16(&b, dns_rdatatype_tsig);
			isc_buffer_putuint16(&b, dns_rdataclass_any);
		} else {
			isc_buffer_putuint8(&b, 0); /* '.' */
			isc_buffer_putuint16(&b, dns_rdatatype_sig);
			isc_buffer_putuint16(&b, dns_rdataclass_in);
		}
		isc_buffer_putuint32(&b, 0); /* ttl */
		data++;
		size--;
		if (size > isc_buffer_availablelength(&b) - 2) {
			size = isc_buffer_availablelength(&b) - 2;
		}
		isc_buffer_putuint16(&b, size);
		isc_buffer_putmem(&b, data, size);
	}

	dns_message_create(mctx, DNS_MESSAGE_INTENTPARSE, &message);

	result = dns_message_parse(message, &b, 0);
	if (debug) {
		fprintf(stderr, "dns_message_parse => %s\n",
			isc_result_totext(result));
	}
	if (result != ISC_R_SUCCESS) {
		dns_message_detach(&message);
	} else {
		if (debug) {
			char text[200000];
			isc_buffer_init(&b, text, sizeof(text));

			result = dns_message_totext(
				message, &dns_master_style_debug, 0, &b);
			if (result == ISC_R_SUCCESS) {
				fprintf(stderr, "%.*s", (int)b.used, text);
			} else {
				fprintf(stderr, "dns_message_totext => %s\n",
					isc_result_totext(result));
			}
		}
		*messagep = message;
	}
	return (result);
}

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	isc_result_t result;
	dns_message_t *message = NULL;
	bool addasig = false;
	bool addtsig = false;
	bool freeze = false;
	dns_zt_t *zt = NULL;
	dns_view_t *view = NULL;
	dns_db_t *db = NULL;
	dns_zone_t *zone = NULL;
	dns_fixedname_t fixed;
	dns_name_t *name = dns_fixedname_initname(&fixed);

	dns_zt_create(&zt);
	dns_view_create(dns_rdataclass_in, "view", &view);
	dns_db_create("db", dns_rdataclass_in, &db);
	dns_zone_create(&zone, 0);
	dns_name_fromstring(name, "example.com", 0, NULL);
	dns_zone_setorigin(zone, name);
	dns_zone_setclass(zone, view->rdclass);
	dns_zone_settype(zone, dns_zone_master);
	dns_zone_setdb(zone, db);
	dns_zone_add(view, zone);
	dns_zone_detach(&zone);
	dns_db_detach(&db);
	dns_view_freeze(view);

	/*
	 * The first octet affects setup.
	 * It determines whether a signature is added and which type
	 * (addasig, addtsig), and whether the zone should be frozen.
	 *
	 * The second octet defines if the message is a response and the
	 * opcode.
	 */
	if (size > 65535 || size < 2) {
		return (0);
	}

	addasig = (*data & 0x80) != 0;
	addtsig = (*data & 0x40) != 0;
	freeze = (*data & 0x20) != 0;

	data++;
	size--;

	if (debug) {
		fprintf(stderr,
			"addasig=%u addtsig=%u freeze=%u\n",
			addasig, addtsig, freeze);
	}

	result = create_message(&message, data, size, addasig, addtsig);
	if (result != ISC_R_SUCCESS) {
		return (0);
	}

	result = dns_zt_freezezones(zt, view, freeze);
	if (debug) {
		fprintf(stderr, "dns_zt_freezezones => %s\n",
			isc_result_totext(result));
	}

	dns_message_detach(&message);
	dns_zone_detach(&zone);
	dns_db_detach(&db);
	dns_view_detach(&view);
	dns_zt_detach(&zt);

	return (0);
}