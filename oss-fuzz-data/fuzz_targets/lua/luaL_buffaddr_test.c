/*
 * SPDX-License-Identifier: ISC
 *
 * Copyright 2023, Sergey Bronnikov.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  lua_State *L = luaL_newstate();
  if (L == NULL)
    return 0;

  luaL_Buffer buf;
  char *s = luaL_buffinitsize(L, &buf, size);
  memcpy(s, data, size);
  luaL_pushresultsize(&buf, size);
  if (luaL_buffaddr(&buf) == NULL)
    return 0;

  lua_settop(L, 0);
  lua_close(L);

  return 0;
}