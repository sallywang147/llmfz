#include <cstdlib>
#include <igraph.h>

extern "C" {
  #include <igraph_arpack.h>
  #include <igraph_sparsemat.h>
}

inline void check_err(igraph_error_t err) {
  if (err != IGRAPH_SUCCESS)
    abort();
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  igraph_sparsemat_t A;
  igraph_arpack_options_t options;
  igraph_arpack_storage_t storage;
  igraph_matrix_t values;
  igraph_matrix_t vectors;

  igraph_set_error_handler(igraph_error_handler_ignore);
  igraph_set_warning_handler(igraph_warning_handler_ignore);

  if (Size % 2 == 1 || Size > 512) {
    return 0;
  }

  check_err(igraph_sparsemat_init(&A, Size, Size, IGRAPH_SPARSEMAT_CSR));
  for (size_t i = 0; i < Size; ++i) {
    A.rowptr[i] = Data[i];
  }

  check_err(igraph_arpack_options_init(&options, IGRAPH_ARPACK_OPTIONS_DEFAULT));
  check_err(igraph_arpack_storage_init(&storage, Size, Size, 0, 0));
  check_err(igraph_matrix_init(&values, 0, 0));
  check_err(igraph_matrix_init(&vectors, 0, 0));

  igraph_sparsemat_arpack_rnsolve(&A, &options, &storage, &values, &vectors);

  igraph_sparsemat_destroy(&A);
  igraph_arpack_options_destroy(&options);
  igraph_arpack_storage_destroy(&storage);
  igraph_matrix_destroy(&values);
  igraph_matrix_destroy(&vectors);

  IGRAPH_ASSERT(IGRAPH_FINALLY_STACK_EMPTY);

  return 0; // Non-zero return values are reserved for future use.
}