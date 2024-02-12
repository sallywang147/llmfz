#include <stdio.h>
#include <gdbm.h>

int main() {
    GDBM_FILE gdbm_file;
    gdbm_file = gdbm_open("test.gdbm", 0, GDBM_WRCREAT, 0644, NULL);
    if (gdbm_file == NULL) {
        perror("gdbm_open");
        return 1;
    }

    gdbm_store(gdbm_file, "key1", 5, "value1", 6, GDBM_INSERT);
    gdbm_store(gdbm_file, "key2", 5, "value2", 6, GDBM_INSERT);

    gdbm_close(gdbm_file);

    return 0;
}