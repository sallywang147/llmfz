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
  igraph_t graph;
  igraph_vector_int_t edges;
  igraph_sparsemat_t A;
  igraph_arpack_options_t options;
  igraph_arpack_storage_t storage;
  igraph_matrix_t values, vectors;

  igraph_set_error_handler(igraph_error_handler_ignore);
  igraph_set_warning_handler(igraph_warning_handler_ignore);

  if (Size % 2 == 1 || Size > 512) {
    return 0;
  }

  check_err(igraph_vector_int_init(&edges, Size));
  for (size_t i = 0; i < Size; ++i) {
    VECTOR(edges)[i] = Data[i];
  }

  /* Undirected */
  if (igraph_create(&graph, &edges, 0, IGRAPH_UNDIRECTED) == IGRAPH_SUCCESS) {
    igraph_bool_t multi;

    check_err(igraph_has_multiple(&graph, &multi));

    /* Bliss does not support multigraphs and the input is currently not checked */
    if (!multi) {
      check_err(igraph_sparsemat_get(&A, &graph, IGRAPH_SPARSE_ROW_CSR, IGRAPH_SPARSE_SYM, 0, 0));
      check_err(igraph_arpack_options_init(&options, A.ncol));
      check_err(igraph_arpack_storage_init(&storage, A.ncol));
      check_err(igraph_matrix_init(&values, 0, 0));
      check_err(igraph_matrix_init(&vectors, 0, 0));

      check_err(igraph_sparsemat_arpack_rnsolve(&A, &options, &storage, &values, &vectors));

      igraph_matrix_destroy(&values);
      igraph_matrix_destroy(&vectors);
      igraph_arpack_storage_destroy(&storage);
      igraph_arpack_options_destroy(&options);
      igraph_sparsemat_destroy(&A);
    }

    igraph_destroy(&graph);
  }

  /* Directed */
  if (igraph_create(&graph, &edges, 0, IGRAPH_DIRECTED) == IGRAPH_SUCCESS) {
    igraph_bool_t multi;

    check_err(igraph_has_multiple(&graph, &multi));

    /* Bliss does not support multigraphs and the input is currently not checked */
    if (!multi) {
      check_err(igraph_sparsemat_get(&A, &graph, IGRAPH_SPARSE_ROW_CSR, IGRAPH_SPARSE_SYM, 0, 0));
      check_err(igraph_arpack_options_init(&options, A.ncol));
      check_err(igraph_arpack_storage_init(&storage, A.ncol));
      check_err(igraph_matrix_init(&values, 0, 0));
      check_err(igraph_matrix_init(&vectors, 0, 0));

      check_err(igraph_sparsemat_arpack_rnsolve(&A, &options, &storage, &values, &vectors));

      igraph_matrix_destroy(&values);
      igraph_matrix_destroy(&vectors);
      igraph_arpack_storage_destroy(&storage);
      igraph_arpack_options_destroy(&options);
      igraph_sparsemat_destroy(&A);
    }

    igraph_destroy(&graph);
  }

  igraph_vector_int_destroy(&edges);

  IGRAPH_ASSERT(IGRAPH_FINALLY_STACK_EMPTY);

  return 0; // Non-zero return values are reserved for future use.
}