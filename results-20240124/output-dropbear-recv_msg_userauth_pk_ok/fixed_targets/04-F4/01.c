#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

extern "C" {
#include <libssh/libssh.h>
}

int main(int argc, char **argv)
{
    ssh_session my_ssh_session;
    int rc;
    int sock = 0;
    struct sockaddr_in serv_addr;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Failed to create socket");
        return EXIT_FAILURE;
    }

    // Set server address
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Failed to connect to server");
        return EXIT_FAILURE;
    }

    // Initialize a SSH session
    my_ssh_session = ssh_new();
    if (my_ssh_session == NULL) {
        fprintf(stderr, "Failed to initialize SSH session\n");
        return EXIT_FAILURE;
    }

    // Set options
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, argv[1]);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, "username");
    ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &argv[2]);

    // Connect to the server
    rc = ssh_connect(my_ssh_session);
    if (rc != SSH_OK) {
        fprintf(stderr, "Failed to connect to SSH server: %s\n", ssh_get_error(my_ssh_session));
        return EXIT_FAILURE;
    }

    // Authenticate using password
    rc = ssh_userauth_password(my_ssh_session, "username", "password");
    if (rc != SSH_AUTH_SUCCESS) {
        fprintf(stderr, "Authentication failed: %s\n", ssh_get_error(my_ssh_session));
        return EXIT_FAILURE;
    }

    // Start a shell session
    rc = ssh_channel_open_session(my_ssh_session);
    if (rc != SSH_OK) {
        fprintf(stderr, "Failed to open SSH channel: %s\n", ssh_get_error(my_ssh_session));
        return EXIT_FAILURE;
    }

    // Execute a command
    rc = ssh_channel_request_exec(my_ssh_session, "ls -l");
    if (rc != SSH_OK) {
        fprintf(stderr, "Failed to execute command: %s\n", ssh_get_error(my_ssh_session));
        return EXIT_FAILURE;
    }

    // Read the output of the command
    char buffer[1024];
    int nbytes;
    while ((nbytes = ssh_channel_read(my_ssh_session, buffer, sizeof(buffer), 0)) > 0) {
        write(STDOUT_FILENO, buffer, nbytes);
    }

    // Close the channel
    ssh_channel_close(my_ssh_session);

    // Disconnect from the server
    ssh_disconnect(my_ssh_session);

    // Free the SSH session
    ssh_free(my_ssh_session);

    // Close the socket
    close(sock);

    return EXIT_SUCCESS;
}