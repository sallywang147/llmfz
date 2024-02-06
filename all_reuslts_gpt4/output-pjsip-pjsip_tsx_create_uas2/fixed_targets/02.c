#include <fuzzer/FuzzedDataProvider.h>
#include <pjlib.h>
#include <pjlib-util.h>
#include <pjnath.h>
#include <pjsip.h>
#include <pjsip-simple.h>
#include <pjsip-ua.h>
#include <pjsua-lib/pjsua.h>
#include <pjsua-lib/pjsua_internal.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Initialize pjsip
    pj_status_t status;
    status = pj_init();
    if (status != PJ_SUCCESS) {
        return 0;
    }

    // Create a pjsip module
    struct pjsip_module *tsx_user = (struct pjsip_module *) pj_pool_alloc(pj_pool_create(&pj_caching_pool.factory, "tsx_user", 4000, 4000, NULL), sizeof(struct pjsip_module));
    tsx_user->id = stream.ConsumeRandomLengthString().c_str();

    // Create a pjsip_rx_data
    struct pjsip_rx_data *rdata = (struct pjsip_rx_data *) pj_pool_alloc(pj_pool_create(&pj_caching_pool.factory, "rdata", 4000, 4000, NULL), sizeof(struct pjsip_rx_data));
    rdata->tp_info.transport = pjsip_transport_create(PJSIP_TRANSPORT_UDP, &stream.ConsumeIntegral<pj_sockaddr>());

    // Create a pj_grp_lock_t
    struct pj_grp_lock_t *grp_lock = (struct pj_grp_lock_t *) pj_pool_alloc(pj_pool_create(&pj_caching_pool.factory, "grp_lock", 4000, 4000, NULL), sizeof(struct pj_grp_lock_t));

    // Create a pjsip_transaction
    struct pjsip_transaction *p_tsx = (struct pjsip_transaction *) pj_pool_alloc(pj_pool_create(&pj_caching_pool.factory, "p_tsx", 4000, 4000, NULL), sizeof(struct pjsip_transaction));

    // Call the function to fuzz
    pjsip_tsx_create_uas2(tsx_user, rdata, grp_lock, &p_tsx);

    return 0;
}