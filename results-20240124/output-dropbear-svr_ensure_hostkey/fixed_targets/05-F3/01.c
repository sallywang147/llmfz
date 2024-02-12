#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

extern "C" {
#include <libssh/libssh.h>
}

extern void svr_ensure_hostkey(void);

int main(int argc, char **argv)
{
    ssh_session session = ssh_new();
    if (session == NULL)
    {
        fprintf(stderr, "Error creating SSH session\n");
        return EXIT_FAILURE;
    }

    ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");
    ssh_options_set(session, SSH_OPTIONS_USER, "username");

    if (ssh_connect(session))
    {
        fprintf(stderr, "Error connecting to SSH server\n");
        ssh_free(session);
        return EXIT_FAILURE;
    }

    svr_ensure_hostkey();

    ssh_disconnect(session);
    ssh_free(session);

    return EXIT_SUCCESS;
}