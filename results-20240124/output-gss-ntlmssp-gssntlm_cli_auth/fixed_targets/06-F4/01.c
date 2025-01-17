#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gssapi/gssapi.h>

extern "C" {
#include <gssntlmssp/gssapi.h>
}

int main() {
  OM_uint32 major_status, minor_status;
  gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;
  gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;
  gss_OID mech_type = GSS_C_NO_OID;
  gss_name_t server_name = GSS_C_NO_NAME;
  gss_ctx_id_t context = GSS_C_NO_CONTEXT;

  // Initialize the GSSAPI library
  major_status = gss_initialize_library(&minor_status);
  if (major_status != GSS_S_COMPLETE) {
    fprintf(stderr, "Error initializing GSSAPI library: %s\n", gss_error_message(minor_status));
    return EXIT_FAILURE;
  }

  // Create a server name
  major_status = gss_import_name(&minor_status, "HTTP/example.com", GSS_C_NT_HOSTBASED_SERVICE, &server_name);
  if (major_status != GSS_S_COMPLETE) {
    fprintf(stderr, "Error creating server name: %s\n", gss_error_message(minor_status));
    gss_release_buffer(&minor_status, &input_token);
    gss_release_buffer(&minor_status, &output_token);
    gss_delete_name(&minor_status, &server_name);
    gss_release_oid(&minor_status, &mech_type);
    gss_delete_sec_context(&minor_status, &context);
    gss_finalize_library(&minor_status);
    return EXIT_FAILURE;
  }

  // Set the mechanism type to NTLM
  mech_type = gss_ntlmssp_inquire_mech_info(&minor_status);
  if (mech_type == GSS_C_NO_OID) {
    fprintf(stderr, "Error getting NTLM mechanism OID: %s\n", gss_error_message(minor_status));
    gss_release_buffer(&minor_status, &input_token);
    gss_release_buffer(&minor_status, &output_token);
    gss_delete_name(&minor_status, &server_name);
    gss_release_oid(&minor_status, &mech_type);
    gss_delete_sec_context(&minor_status, &context);
    gss_finalize_library(&minor_status);
    return EXIT_FAILURE;
  }

  // Acquire a context
  major_status = gssntlm_cli_auth(&minor_status, mech_type, server_name, &input_token, &output_token, &context);
  if (major_status != GSS_S_COMPLETE) {
    fprintf(stderr, "Error acquiring context: %s\n", gss_error_message(minor_status));
    gss_release_buffer(&minor_status, &input_token);
    gss_release_buffer(&minor_status, &output_token);
    gss_delete_name(&minor_status, &server_name);
    gss_release_oid(&minor_status, &mech_type);
    gss_delete_sec_context(&minor_status, &context);
    gss_finalize_library(&minor_status);
    return EXIT_FAILURE;
  }

  // Display the output token
  printf("Output token:\n");
  for (size_t i = 0; i < output_token.length; i++) {
    printf("%02x", output_token.value[i]);
  }
  printf("\n");

  // Release resources
  gss_release_buffer(&minor_status, &input_token);
  gss_release_buffer(&minor_status, &output_token);
  gss_delete_name(&minor_status, &server_name);
  gss_release_oid(&minor_status, &mech_type);
  gss_delete_sec_context(&minor_status, &context);
  gss_finalize_library(&minor_status);

  return EXIT_SUCCESS;
}