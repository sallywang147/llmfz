#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libssh/libssh.h>

int main()
{
    ssh_session session = ssh_new();
    if (session == NULL)
        exit(-1);

    ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");
    ssh_options_set(session, SSH_OPTIONS_USER, "username");

    if (ssh_connect(session))
    {
        fprintf(stderr, "Error connecting to localhost: %s\n", ssh_get_error(session));
        ssh_free(session);
        exit(-1);
    }

    ssh_userauth_password(session, NULL, "password");
    if (ssh_is_connected(session) == 0)
    {
        fprintf(stderr, "Error authenticating with password: %s\n", ssh_get_error(session));
        ssh_disconnect(session);
        ssh_free(session);
        exit(-1);
    }

    ssh_channel channel = ssh_channel_new(session);
    if (channel == NULL)
    {
        fprintf(stderr, "Error creating channel: %s\n", ssh_get_error(session));
        ssh_disconnect(session);
        ssh_free(session);
        exit(-1);
    }

    if (ssh_channel_open_session(channel) != SSH_OK)
    {
        fprintf(stderr, "Error opening channel: %s\n", ssh_get_error(session));
        ssh_channel_free(channel);
        ssh_disconnect(session);
        ssh_free(session);
        exit(-1);
    }

    ssh_channel_request_exec(channel, "ls -l");

    char buffer[1024];
    int nbytes;
    while ((nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0)) > 0)
    {
        fwrite(buffer, 1, nbytes, stdout);
    }

    if (nbytes < 0)
    {
        fprintf(stderr, "Error reading from channel: %s\n", ssh_get_error(session));
        ssh_channel_close(channel);
        ssh_disconnect(session);
        ssh_free(session);
        exit(-1);
    }

    ssh_channel_close(channel);
    ssh_disconnect(session);
    ssh_free(session);

    return 0;
}