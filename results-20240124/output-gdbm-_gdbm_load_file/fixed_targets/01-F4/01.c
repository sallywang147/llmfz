#include <gdbm-ndbm.h>
#include <gdbm.h>
#include <iostream>
#include <string>

using namespace std;

extern "C" {
#include <gdbm-ndbm.h>
#include <gdbm.h>
}

int main() {
  GDBM_FILE file;
  datum key, value;

  file = gdbm_open("test.gdbm", 0, GDBM_WRCREAT, 0644, 0);
  if (file == NULL) {
    cerr << "Error opening database" << endl;
    return 1;
  }

  key.dptr = (char *)"key1";
  key.dsize = strlen(key.dptr);
  value.dptr = (char *)"value1";
  value.dsize = strlen(value.dptr);
  if (gdbm_store(file, key, value, GDBM_INSERT) != 0) {
    cerr << "Error storing data" << endl;
    return 1;
  }

  key.dptr = (char *)"key2";
  key.dsize = strlen(key.dptr);
  if (gdbm_exists(file, key)) {
    cout << "Key exists" << endl;
  } else {
    cout << "Key does not exist" << endl;
  }

  gdbm_close(file);
  return 0;
}