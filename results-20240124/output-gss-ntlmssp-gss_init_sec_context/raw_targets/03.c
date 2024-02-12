 #include <string.h>

#include <krb5.h>
#include <gssapi.h>

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    OM_uint32 maj_stat, min_stat;

    gss_ctx_id_t ctx = GSS_C_NO_CONTEXT;
    gss_name_t target_name = GSS_C_NO_NAME;
    gss_cred_id_t cred_handle = GSS_C_NO_CREDENTIAL;
    gss_buffer_desc input_token, output_token = GSS_C_EMPTY_BUFFER;
    gss_OID_desc_struct mech_type = {0, NULL};

    /* Each fuzz input contains multiple tokens preceded by a length field.
     * Process them in turn with gss_init_sec_context while
     * GSS_S_CONTINUE_NEEDED is set
     */
    do {
        unsigned short token_length;

        if (Size < sizeof(token_length))
            break;

        token_length = *(unsigned short *)Data;

        Data += sizeof(token_length);
        Size -= sizeof(token_length);

        if (token_length == 0 || token_length > Size)
            break;

        input_token.length = token_length;
        input_token.value = malloc(token_length);
        memcpy(input_token.value, Data, token_length);

        Data += token_length;
        Size -= token_length;

        maj_stat = gss_init_sec_context(
            &min_stat,
            &cred_handle, /* claimant_cred_handle */
            &ctx,
            target_name, /* target_name */
            &mech_type, /* mech_type */
            0, /* req_flags */
            0, /* time_req */
            NULL, /* input_chan_bindings */
            &input_token, /* input_token */
            NULL, /* actual_mech_type */
            &output_token, /* output_token */
            NULL, /* ret_flags */
            NULL /* time_rec */
        );

        gss_release_buffer(&min_stat, &input_token);
        gss_release_buffer(&min_stat, &output_token);
    } while(maj_stat == GSS_S_CONTINUE_NEEDED);

    gss_release_name(&min_stat, &target_name);
    gss_release_cred(&min_stat, &cred_handle);

    gss_delete_sec_context(&min_stat, &ctx, GSS_C_NO_BUFFER);

    return 0;
}