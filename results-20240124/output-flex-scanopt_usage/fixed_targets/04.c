#include <scanopt/scanopt.h>

int main(int argc, char **argv) {
  scanopt_init(argc, argv);
  scanopt_usage();
  scanopt_destroy();
  return 0;
}