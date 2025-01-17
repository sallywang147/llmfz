#include <krb5.h>
#include <gssapi.h>
#include <gssapi/gssapi_krb5.h>
#include <string.h>

extern "C" {
#include <gssapi/gssapi_ext.h>
}

extern int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    OM_uint32 maj_stat, min_stat;
    gss_ctx_id_t context = GSS_C_NO_CONTEXT;
    gss_name_t target_name = GSS_C_NO_NAME;
    gss_cred_id_t claimant_cred_handle;
    gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;
    gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;
    gss_OID_desc mech_type = {0, GSS_C_NULL_OID};
    gss_channel_bindings_struct input_chan_bindings = {0, GSS_C_NO_BUFFER, 0, 0, 0, 0};

    /* The fuzz input is a sequence of tokens, each preceded by a length field.
     * Process them in turn with gss_init_sec_context while
     * GSS_S_CONTINUE_NEEDED is set
     */
    do {
        unsigned short token_length;

        if (size < sizeof(token_length))
            break;

        token_length = *(unsigned short *)data;

        data += sizeof(token_length);
        size -= sizeof(token_length);

        if (token_length == 0 || token_length > size)
            break;

        input_token.length = token_length;
        input_token.value = malloc(token_length);
        memcpy(input_token.value, data, token_length);

        data += token_length;
        size -= token_length;

        maj_stat = gss_init_sec_context(
            &min_stat,
            &claimant_cred_handle, /* claimant_cred_handle */
            &context, /* context_handle */
            target_name, /* target_name */
            &mech_type, /* mech_type */
            0, /* req_flags */
            0, /* time_req */
            &input_chan_bindings, /* input_chan_bindings */
            &input_token, /* input_token */
            NULL, /* actual_mech_type */
            &output_token, /* output_token */
            NULL, /* ret_flags */
            NULL /* time_rec */
        );

        gss_release_buffer(&min_stat, &input_token);
        gss_release_buffer(&min_stat, &output_token);
    } while(maj_stat == GSS_S_CONTINUE_NEEDED);

    gss_delete_sec_context(&min_stat, &context, NULL);
    gss_release_cred(&min_stat, &claimant_cred_handle);
    gss_release_name(&min_stat, &target_name);

    return 0;
}