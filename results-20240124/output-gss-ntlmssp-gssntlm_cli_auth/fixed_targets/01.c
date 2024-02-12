#include <stdio.h>
#include <stdlib.h>
#include <gssapi/gssapi.h>
#include <gssapi/gssapi_ntlm.h>

extern "C" {
#include <gssntlm.h>
}

int main() {
    gss_buffer_desc input_token = {0};
    gss_buffer_desc output_token = {0};
    gss_OID mech_type = GSS_NTLM_MECHANISM;
    gss_ctx_id_t context = GSS_C_NO_CONTEXT;
    gss_name_t server_name = GSS_C_NO_NAME;
    OM_uint32 major_status, minor_status;

    // Initialize the GSSAPI library
    major_status = gss_initialize_library(&minor_status);
    if (major_status != GSS_S_COMPLETE) {
        fprintf(stderr, "Error initializing GSSAPI library: %s\n", gss_mech_error(minor_status));
        return EXIT_FAILURE;
    }

    // Create a server name
    major_status = gss_import_name(&minor_status, "HTTP/server.example.com", GSS_C_NO_OID, &server_name);
    if (major_status != GSS_S_COMPLETE) {
        fprintf(stderr, "Error creating server name: %s\n", gss_mech_error(minor_status));
        return EXIT_FAILURE;
    }

    // Acquire a context
    major_status = gss_acquire_cred(&minor_status, GSS_C_NO_NAME, GSS_C_INDEFINITE, &mech_type, GSS_C_BOTH, &context, NULL, NULL);
    if (major_status != GSS_S_COMPLETE) {
        fprintf(stderr, "Error acquiring context: %s\n", gss_mech_error(minor_status));
        return EXIT_FAILURE;
    }

    // Generate an NTLM token
    major_status = gssntlm_cli_auth(&minor_status, context, server_name, &input_token, &output_token);
    if (major_status != GSS_S_COMPLETE) {
        fprintf(stderr, "Error generating NTLM token: %s\n", gss_mech_error(minor_status));
        return EXIT_FAILURE;
    }

    // Display the NTLM token
    printf("NTLM token: %.*s\n", (int)output_token.length, (char *)output_token.value);

    // Clean up
    gss_release_buffer(&minor_status, &input_token);
    gss_release_buffer(&minor_status, &output_token);
    gss_delete_name(&minor_status, &server_name);
    gss_release_cred(&minor_status, &context);
    gss_finalize_library(&minor_status);

    return EXIT_SUCCESS;
}