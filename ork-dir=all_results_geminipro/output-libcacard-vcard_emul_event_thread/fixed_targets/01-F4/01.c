#include <libcacard.h>
#include <stdlib.h>

#include "fuzzer.h"

#define ARGS "db=\"sql:%s\" use_hw=no soft=(,Test,CAC,,cert1,cert2,cert3)"
#define APDUBufSize 270

static GMainLoop *loop;
static GThread *thread;
static guint nreaders;
static GMutex mutex;
static GCond cond;

extern "C" {
static gpointer events_thread(gpointer arg) {
  unsigned int reader_id;
  VEvent *event;

  (void)arg;

  while (1) {
    event = vevent_wait_next_vevent();
    if (event->type == VEVENT_LAST) {
      vevent_delete(event);
      break;
    }
    reader_id = vreader_get_id(event->reader);
    if (reader_id == VSCARD_UNDEFINED_READER_ID) {
      g_mutex_lock(&mutex);
      vreader_set_id(event->reader, nreaders++);
      g_cond_signal(&cond);
      g_mutex_unlock(&mutex);
      reader_id = vreader_get_id(event->reader);
    }
    switch (event->type) {
    case VEVENT_READER_INSERT:
    case VEVENT_READER_REMOVE:
    case VEVENT_CARD_INSERT:
    case VEVENT_CARD_REMOVE:
      break;
    case VEVENT_LAST:
    default:
      g_warn_if_reached();
      break;
    }
    vevent_delete(event);
  }

  return NULL;
}

static void libcacard_init(void) {
  VCardEmulOptions *command_line_options = NULL;
  gchar *dbdir = NULL;
  gchar *args = NULL;
  VReader *r;
  VCardEmulError ret;

  /* This will use the test directory when running as test and
   * and dirname part of argv[0] when running from oss-fuzz */
  dbdir = g_test_build_filename(G_TEST_DIST, "db", NULL);
  args = g_strdup_printf(ARGS, dbdir);

  thread = g_thread_new("fuzz/events", events_thread, NULL);

  command_line_options = vcard_emul_options(args);
  ret = vcard_emul_init(command_line_options);
  g_assert_cmpint(ret, ==, VCARD_EMUL_OK);

  r = vreader_get_reader_by_name("Test");
  g_assert_nonnull(r);
  vreader_free(r); /* get by name ref */

  g_mutex_lock(&mutex);
  while (nreaders == 0)
    g_cond_wait(&cond, &mutex);
  g_mutex_unlock(&mutex);

  g_free(args);
  g_free(dbdir);
}

static void libcacard_finalize(void) {
  VReader *reader = vreader_get_reader_by_id(0);

  /* This actually still generates events ?? */
  if (reader) /*if /remove didn't run */
    vreader_remove_reader(reader);

  /* This probably supposed to be a event that terminates the loop */
  vevent_queue_vevent(vevent_new(VEVENT_LAST, reader, NULL));

  /* join */
  g_thread_join(thread);

  vreader_free(reader);

  vcard_emul_finalize();
}
}

int LLVMFuzzerInitialize(int *argc, char ***argv) {
  VReader *reader;

  (void)argc;

  g_test_init(argc, argv, NULL);

  loop = g_main_loop_new(NULL, TRUE);

  g_debug("Initializing ...");
  libcacard_init();

  reader = vreader_get_reader_by_id(0);
  if (vreader_card_is_present(reader) != VREADER_OK) {
    g_error("Card inserted but not still not present");
    return -1;
  }

  atexit(libcacard_finalize);

  vreader_free(reader);
  return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  size_t left = Size;
  uint8_t *data = (uint8_t *)Data;
  char *arg = NULL;

  if (left < 1) {
    g_debug("Too short input for argument");
    return 0;
  }

  arg = (char *)g_malloc(left + 1);
  memcpy(arg, data, left);
  arg[left] = '\0';

  g_debug("Calling vcard_emul_event_thread with '%s'", arg);
  vcard_emul_event_thread(arg);

  g_free(arg);

  g_debug("Cleaning up");

  return 0;
}

/* vim: set ts=4 sw=4 tw=0 noet expandtab: */