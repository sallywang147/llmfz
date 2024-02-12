#include <LLVMFuzzerTestOneInput.h>
#include <gssapi/gssapi.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    // ...
    int minor_status;
    gss_cred_id_t claimant_cred_handle = GSS_C_NO_CREDENTIAL;
    gss_ctx_id_t *context_handle = NULL;
    gss_name_t target_name = GSS_C_NO_NAME;
    gss_OID_desc_t mech_type = GSS_C_NO_OID;
    int req_flags = 0;
    int time_req = 0;
    gss_channel_bindings_t input_chan_bindings = GSS_C_NO_CHANNEL_BINDINGS;
    gss_buffer_desc_t input_token = {0, NULL};
    gss_OID_desc_t *actual_mech_type = NULL;
    gss_buffer_desc_t output_token = {0, NULL};
    int ret_flags = 0;
    int time_rec = 0;

    gss_init_sec_context(&minor_status, claimant_cred_handle, &context_handle, target_name, &mech_type, req_flags, time_req, input_chan_bindings, &input_token, &actual_mech_type, &output_token, &ret_flags, &time_rec);

    // ...
}