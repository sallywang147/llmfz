#include <stdio.h>
#include <stdlib.h>
#include <libssh/libssh.h>

extern "C" {
#include <libssh/server.h>
}

int main() {
    ssh_session session = ssh_new();
    if (session == NULL) {
        fprintf(stderr, "Error creating session\n");
        return EXIT_FAILURE;
    }

    ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");
    ssh_options_set(session, SSH_OPTIONS_PORT, 22);

    int rc = ssh_connect(session);
    if (rc != SSH_OK) {
        fprintf(stderr, "Error connecting to host: %s\n", ssh_get_error(session));
        ssh_free(session);
        return EXIT_FAILURE;
    }

    ssh_channel channel = ssh_channel_new(session);
    if (channel == NULL) {
        fprintf(stderr, "Error creating channel\n");
        ssh_disconnect(session);
        ssh_free(session);
        return EXIT_FAILURE;
    }

    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK) {
        fprintf(stderr, "Error opening channel: %s\n", ssh_get_error(channel));
        ssh_channel_free(channel);
        ssh_disconnect(session);
        ssh_free(session);
        return EXIT_FAILURE;
    }

    rc = ssh_channel_request_pty(channel, "xterm");
    if (rc != SSH_OK) {
        fprintf(stderr, "Error requesting pty: %s\n", ssh_get_error(channel));
        ssh_channel_close(channel);
        ssh_disconnect(session);
        ssh_free(session);
        return EXIT_FAILURE;
    }

    rc = ssh_channel_request_shell(channel);
    if (rc != SSH_OK) {
        fprintf(stderr, "Error requesting shell: %s\n", ssh_get_error(channel));
        ssh_channel_close(channel);
        ssh_disconnect(session);
        ssh_free(session);
        return EXIT_FAILURE;
    }

    svr_ensure_hostkey(session);

    while (true) {
        char buffer[1024];
        int nread = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
        if (nread < 0) {
            fprintf(stderr, "Error reading from channel: %s\n", ssh_get_error(channel));
            ssh_channel_close(channel);
            ssh_disconnect(session);
            ssh_free(session);
            return EXIT_FAILURE;
        }

        if (nread == 0) {
            break;
        }

        printf("%s", buffer);
    }

    ssh_channel_send_eof(channel);
    ssh_channel_close(channel);
    ssh_disconnect(session);
    ssh_free(session);

    return EXIT_SUCCESS;
}