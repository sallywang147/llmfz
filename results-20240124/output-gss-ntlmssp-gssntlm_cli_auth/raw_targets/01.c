 #include <string.h>

#include <krb5.h>
#include <gssapi.h>
#include "gss_ntlmssp.h"

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    OM_uint32 maj_stat, min_stat;

    struct gss_ctx_id_struct *ctx = GSS_C_NO_CONTEXT;
    struct gss_cred_id_struct *cred = GSS_C_NO_CREDENTIAL;
    struct ntlm_buffer target_info = NTLM_BUFFER_INIT;
    struct gss_channel_bindings_struct *input_chan_bindings = GSS_C_NO_CHANNEL_BINDINGS;

    if (Size < sizeof(unsigned short))
        return 0;

    unsigned short target_info_length = *(unsigned short *)Data;

    Data += sizeof(target_info_length);
    Size -= sizeof(target_info_length);

    if (target_info_length > Size)
        return 0;

    target_info.length = target_info_length;
    target_info.value = malloc(target_info_length);
    memcpy(target_info.value, Data, target_info_length);

    Data += target_info_length;
    Size -= target_info_length;

    maj_stat = gssntlm_cli_auth(
        &min_stat,
        &ctx,
        &cred,
        &target_info,
        0, /* in_flags */
        input_chan_bindings
    );

    gss_release_buffer(&min_stat, &target_info);

    gss_delete_sec_context(&min_stat, &ctx, GSS_C_NO_BUFFER);

    gss_release_cred(&min_stat, &cred);

    return 0;
}