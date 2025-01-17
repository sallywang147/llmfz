#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "futils.h"
extern "C" {
#include "git2.h"
#include "git2/sys/transport.h"
}

#include "standalone_driver.h"

#define UNUSED(x) (void)(x)

struct fuzzer_buffer {
  const unsigned char *data;
  size_t size;
};

struct fuzzer_stream {
  git_smart_subtransport_stream base;
  const unsigned char *readp;
  const unsigned char *endp;
};

struct fuzzer_subtransport {
  git_smart_subtransport base;
  git_transport *owner;
  struct fuzzer_buffer data;
};

static git_repository *repo;

static int fuzzer_stream_read(git_smart_subtransport_stream *stream, char *buffer, size_t buf_size, size_t *bytes_read) {
  struct fuzzer_stream *fs = (struct fuzzer_stream *)stream;
  size_t avail = fs->endp - fs->readp;

  *bytes_read = (buf_size > avail) ? avail : buf_size;
  memcpy(buffer, fs->readp, *bytes_read);
  fs->readp += *bytes_read;

  return 0;
}

static int fuzzer_stream_write(git_smart_subtransport_stream *stream, const char *buffer, size_t len) {
  UNUSED(stream);
  UNUSED(buffer);
  UNUSED(len);
  return 0;
}

static void fuzzer_stream_free(git_smart_subtransport_stream *stream) { free(stream); }

static int fuzzer_stream_new(struct fuzzer_stream **out, const struct fuzzer_buffer *data) {
  struct fuzzer_stream *stream = malloc(sizeof(*stream));
  if (!stream)
    return -1;

  stream->readp = data->data;
  stream->endp = data->data + data->size;
  stream->base.read = fuzzer_stream_read;
  stream->base.write = fuzzer_stream_write;
  stream->base.free = fuzzer_stream_free;

  *out = stream;

  return 0;
}

static int fuzzer_subtransport_action(git_smart_subtransport_stream **out, git_smart_subtransport *transport, const char *url, git_smart_service_t action) {
  struct fuzzer_subtransport *ft = (struct fuzzer_subtransport *)transport;

  UNUSED(url);
  UNUSED(action);

  return fuzzer_stream_new((struct fuzzer_stream **)out, &ft->data);
}

static int fuzzer_subtransport_close(git_smart_subtransport *transport) {
  UNUSED(transport);
  return 0;
}

static void fuzzer_subtransport_free(git_smart_subtransport *transport) { free(transport); }

static int fuzzer_subtransport_new(struct fuzzer_subtransport **out, git_transport *owner, const struct fuzzer_buffer *data) {
  struct fuzzer_subtransport *sub = malloc(sizeof(*sub));
  if (!sub)
    return -1;

  sub->owner = owner;
  sub->data.data = data->data;
  sub->data.size = data->size;
  sub->base.action = fuzzer_subtransport_action;
  sub->base.close = fuzzer_subtransport_close;
  sub->base.free = fuzzer_subtransport_free;

  *out = sub;

  return 0;
}

static int fuzzer_subtransport_cb(git_smart_subtransport **out, git_transport *owner, void *payload) {
  struct fuzzer_buffer *buf = (struct fuzzer_buffer *)payload;
  struct fuzzer_subtransport *sub;

  if (fuzzer_subtransport_new(&sub, owner, buf) < 0)
    return -1;

  *out = &sub->base;
  return 0;
}

static int fuzzer_transport_cb(git_transport **out, git_remote *owner, void *param) {
  git_smart_subtransport_definition def = {fuzzer_subtransport_cb, 1, param};
  return git_transport_smart(out, owner, &def);
}

static void fuzzer_git_abort(const char *op) {
  const git_error *err = git_error_last();
  fprintf(stderr, "unexpected libgit error: %s: %s\n", op, err ? err->message : "<none>");
  abort();
}

int LLVMFuzzerInitialize(int *argc, char ***argv) {
#if defined(_WIN32)
  char tmpdir[MAX_PATH], path[MAX_PATH];

  if (GetTempPath((DWORD)sizeof(tmpdir), tmpdir) == 0)
    abort();

  if (GetTempFileName(tmpdir, "lg2", 1, path) == 0)
    abort();

  if (git_futils_mkdir(path, 0700, 0) < 0)
    abort();
#else
  char path[] = "/tmp/git2.XXXXXX";

  if (mkdtemp(path) != path)
    abort();
#endif

  if (git_libgit2_init() < 0)
    abort();

  if (git_libgit2_opts(GIT_OPT_SET_PACK_MAX_OBJECTS, 10000000) < 0)
    abort();

  UNUSED(argc);
  UNUSED(argv);

  if (git_repository_init(&repo, path, 1) < 0)
    fuzzer_git_abort("git_repository_init");

  return 0;
}

int LLVMFuzzerTestOneInput(const unsigned char *data, size_t size) {
  struct fuzzer_buffer buffer = {data, size};
  git_submodule *sm;
  git_submodule_update_options update_options = GIT_SUBMODULE_UPDATE_OPTIONS_INIT;

  if (git_submodule_lookup(&sm, repo, "fuzzer-submodule") < 0)
    fuzzer_git_abort("git_submodule_lookup");

  git_submodule_update(sm, 1, &update_options);

  git_submodule_free(sm);

  return 0;
}