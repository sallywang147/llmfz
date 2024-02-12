 #include <string.h>

#include <krb5.h>
#include <gssapi.h>
#include "gss_ntlmssp.h"

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    OM_uint32 maj_stat, min_stat;

    struct gssntlm_ctx ctx;
    struct gssntlm_cred cred;
    struct ntlm_buffer target_info = { 0 };

    memset(&ctx, 0, sizeof(ctx));
    memset(&cred, 0, sizeof(cred));

    maj_stat = gssntlm_cli_auth(
        &min_stat,
        &ctx,
        &cred,
        &target_info,
        0, /* in_flags */
        NULL /* input_chan_bindings */
    );

    gssntlm_ctx_free(&ctx);
    gssntlm_cred_free(&cred);

    return 0;
}