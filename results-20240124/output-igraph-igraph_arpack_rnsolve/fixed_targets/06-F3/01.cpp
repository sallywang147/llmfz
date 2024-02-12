#include <cstdlib>
#include <igraph.h>

typedef int func_type(igraph_arpack_options_t * options,
                      igraph_arpack_storage_t * storage,
                      igraph_matrix_t * values,
                      igraph_matrix_t * vectors);

extern "C" {
  int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    igraph_t graph;
    igraph_vector_int_t edges;
    igraph_matrix_t values;
    igraph_matrix_t vectors;

    igraph_set_error_handler(igraph_error_handler_ignore);
    igraph_set_warning_handler(igraph_warning_handler_ignore);

    if (Size % 2 == 1 || Size > 512) {
      return 0;
    }

    igraph_vector_int_init(&edges, Size);
    for (size_t i = 0; i < Size; ++i) {
      VECTOR(edges)[i] = Data[i];
    }

    /* Undirected */
    if (igraph_create(&graph, &edges, 0, IGRAPH_UNDIRECTED) == IGRAPH_SUCCESS) {
      igraph_bool_t multi;

      igraph_has_multiple(&graph, &multi);

      /* ARPACK does not support multigraphs and the input is currently not checked */
      if (!multi) {
        igraph_arpack_options_t options;
        igraph_arpack_storage_t storage;
        igraph_arpack_options_init(&options, nullptr, nullptr);
        igraph_arpack_storage_init(&storage, 0, nullptr, nullptr);
        igraph_matrix_init(&values, 0, 0);
        igraph_matrix_init(&vectors, 0, 0);
        igraph_arpack_rnsolve(nullptr, nullptr, &options, &storage, &values, &vectors);
        igraph_matrix_destroy(&values);
        igraph_matrix_destroy(&vectors);
        igraph_arpack_storage_destroy(&storage);
        igraph_arpack_options_destroy(&options);
      }

      igraph_destroy(&graph);
    }

    /* Directed */
    if (igraph_create(&graph, &edges, 0, IGRAPH_DIRECTED) == IGRAPH_SUCCESS) {
      igraph_bool_t multi;

      igraph_has_multiple(&graph, &multi);

      /* ARPACK does not support multigraphs and the input is currently not checked */
      if (!multi) {
        igraph_arpack_options_t options;
        igraph_arpack_storage_t storage;
        igraph_arpack_options_init(&options, nullptr, nullptr);
        igraph_arpack_storage_init(&storage, 0, nullptr, nullptr);
        igraph_matrix_init(&values, 0, 0);
        igraph_matrix_init(&vectors, 0, 0);
        igraph_arpack_rnsolve(nullptr, nullptr, &options, &storage, &values, &vectors);
        igraph_matrix_destroy(&values);
        igraph_matrix_destroy(&vectors);
        igraph_arpack_storage_destroy(&storage);
        igraph_arpack_options_destroy(&options);
      }

      igraph_destroy(&graph);
    }

    igraph_vector_int_destroy(&edges);

    IGRAPH_ASSERT(IGRAPH_FINALLY_STACK_EMPTY);

    return 0; // Non-zero return values are reserved for future use.
  }
}