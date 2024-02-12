#include "civetweb.h"

extern "C" {
void mg_send_mime_file(struct mg_connection *conn, char *path, char *mime_type) {
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        mg_printf(conn, "HTTP/1.0 500 Internal Server Error\r\n"
                       "Content-Length: 0\r\n\r\n");
    } else {
        mg_printf(conn,
                  "HTTP/1.0 200 OK\r\n"
                  "Content-Type: %s\r\n"
                  "Content-Length: %lu\r\n\r\n",
                  mime_type, (unsigned long)mg_file_size(file));

        /* Send file data */
        char buf[BUFSIZ];
        int n;
        while ((n = fread(buf, 1, sizeof(buf), file)) > 0) {
            mg_write(conn, buf, n);
        }

        fclose(file);
    }
}
}