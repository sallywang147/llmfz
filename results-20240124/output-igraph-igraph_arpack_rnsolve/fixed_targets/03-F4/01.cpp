/*
   IGraph library.
   Copyright (C) 2021-2022  The igraph development team

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301 USA
*/

#include <cstdlib>
#include <igraph.h>

inline void check_err(igraph_error_t err) {
  if (err != IGRAPH_SUCCESS)
    abort();
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  igraph_t graph;
  igraph_vector_int_t edges;

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
      igraph_arpack_options_t options;
      igraph_arpack_storage_t storage;
      igraph_matrix_t values;
      igraph_matrix_t vectors;

      igraph_arpack_options_init(&options);
      igraph_arpack_storage_init(&storage);
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

    check_err(igraph_has_multiple(&graph, &multi));

    /* Bliss does not support multigraphs and the input is currently not checked */
    if (!multi) {
      igraph_arpack_options_t options;
      igraph_arpack_storage_t storage;
      igraph_matrix_t values;
      igraph_matrix_t vectors;

      igraph_arpack_options_init(&options);
      igraph_arpack_storage_init(&storage);
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