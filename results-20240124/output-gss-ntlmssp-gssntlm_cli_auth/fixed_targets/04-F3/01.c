#include <string.h>

#include <krb5.h>
#include <gssapi.h>
#include "gss_ntlmssp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    OM_uint32 maj_stat, min_stat;

    gssntlm_ctx ctx;
    gssntlm_cred cred;
    struct ntlm_buffer target_info;
    struct gss_channel_bindings_struct input_chan_bindings;

    memset(&ctx, 0, sizeof(ctx));
    memset(&cred, 0, sizeof(cred));
    memset(&target_info, 0, sizeof(target_info));
    memset(&input_chan_bindings, 0, sizeof(input_chan_bindings));

    /* Each fuzz input contains multiple tokens preceded by a length field.
     * Process them in turn with gssntlm_cli_auth while
     * GSS_S_CONTINUE_NEEDED is set
     */
    do {
        unsigned short token_length;

        gss_buffer_desc input_token, output_token = GSS_C_EMPTY_BUFFER;

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

        maj_stat = gssntlm_cli_auth(
            &min_stat,
            &ctx,
            &cred,
            &target_info,
            0, /* in_flags */
            &input_chan_bindings,
            &input_token,
            &output_token
        );

        gss_release_buffer(&min_stat, &input_token);
        gss_release_buffer(&min_stat, &output_token);
    } while(maj_stat == GSS_S_CONTINUE_NEEDED);

    return 0;
}