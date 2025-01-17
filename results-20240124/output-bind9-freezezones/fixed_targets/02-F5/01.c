#include <isc/mem.h>
#include <isc/mutex.h>
#include <isc/string.h>
#include <isc/timer.h>
#include <isc/util.h>

#include <dns/db.h>
#include <dns/dispatch.h>
#include <dns/events.h>
#include <dns/journal.h>
#include <dns/master.h>
#include <dns/message.h>
#include <dns/rdata.h>
#include <dns/rdataset.h>
#include <dns/rdataclass.h>
#include <dns/rdatatype.h>
#include <dns/result.h>
#include <dns/tsig.h>
#include <dns/view.h>
#include <dns/zone.h>

#include "fuzz.h"

static isc_mem_t *mctx = NULL;
static dns_view_t *view = NULL;
static dns_zone_t *zone = NULL;

static isc_result_t
create_message(dns_message_t **messagep, const uint8_t *data, size_t size) {
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
	isc_buffer_putuint16(&b, 0);

	/* Question ./IN/SOA */
	isc_buffer_putuint8(&b, 0);
	isc_buffer_putuint16(&b, 6);
	isc_buffer_putuint16(&b, 1);

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

extern "C" {
int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	isc_result_t result;
	dns_message_t *message = NULL;

	if (size > 65535 || size < 2) {
		return (0);
	}

	result = create_message(&message, data, size);
	if (result != ISC_R_SUCCESS) {
		return (0);
	}

	result = freezezones(zone, NULL);
	if (debug) {
		fprintf(stderr, "freezezones => %s\n",
			isc_result_totext(result));
	}

	dns_message_detach(&message);

	return (0);
}
}

extern "C" {
isc_result_t
freezezones(dns_zone_t *zone, isc_task_t *task) {
	return (ISC_R_SUCCESS);
}
}

extern "C" {
#include <dns/events.h>
}