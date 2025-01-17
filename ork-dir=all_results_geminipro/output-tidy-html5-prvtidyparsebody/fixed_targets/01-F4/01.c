#include "tidy.h"
#include "tidybuffio.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

extern "C" {
#include <tidy.h>
#include <tidybuffio.h>
}

int prvTidyParseBody(struct _TidyDocImpl *doc, struct _Node *body, int mode) {
  struct _Lexer *lexer = doc->lexer;
  int rc = 0;

  while (lexer->token != END) {
    if (lexer->token == START_TAG) {
      struct _Node *node = tidyParseElement(doc, body, mode);
      if (node)
        body = node;
      else
        rc = -1;
    } else if (lexer->token == TEXT_NODE) {
      struct _Node *node = tidyParseText(doc, body);
      if (node)
        body = node;
      else
        rc = -1;
    } else if (lexer->token == COMMENT) {
      tidyParseComment(doc, body);
    } else if (lexer->token == PROC_INSTR) {
      tidyParsePI(doc, body);
    } else if (lexer->token == CDATA) {
      tidyParseCDATA(doc, body);
    } else if (lexer->token == ASP) {
      tidyParseASP(doc, body);
    } else if (lexer->token == JSP) {
      tidyParseJSP(doc, body);
    } else if (lexer->token == PHP) {
      tidyParsePHP(doc, body);
    } else if (lexer->token == START) {
      tidyParseStart(doc, body);
    } else if (lexer->token == END) {
      break;
    } else {
      tidyError(doc, NULL, NULL, TidyWarning, NULL, "unexpected token %d\n",
                lexer->token);
      rc = -1;
    }

    if (rc < 0)
      break;

    tidyNext(lexer);
  }

  return rc;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  uint8_t decider;

  // We need enough data for picking all of the options. One byte per option.
  if (size < 5) {
    return 0;
  }

  TidyDoc tdoc = tidyCreate();

  // Decide output format
  decider = *data;
  data++;
  size--;
  if (decider % 3 == 0)
    tidyOptSetBool(tdoc, TidyXhtmlOut, yes);
  else {
    tidyOptSetBool(tdoc, TidyXhtmlOut, no);
  }

  if (decider % 3 == 1)
    tidyOptSetBool(tdoc, TidyHtmlOut, yes);
  else {
    tidyOptSetBool(tdoc, TidyHtmlOut, no);
  }

  if (decider % 3 == 2)
    tidyOptSetBool(tdoc, TidyXmlOut, yes);
  else {
    tidyOptSetBool(tdoc, TidyXmlOut, no);
  }

  // Set an error buffer.
  tidySetErrorBuffer(tdoc, NULL);

  // Parse the data
  decider = *data;
  data++;
  size--;
  switch (decider % 2) {
  case 0: {
    char filename[256];
    sprintf(filename, "/tmp/libfuzzer.%d", getpid());

    FILE *fp = fopen(filename, "wb");
    if (!fp) {
      return 0;
    }
    fwrite(data, size, 1, fp);
    fclose(fp);

    tidyParseFile(tdoc, filename);
    unlink(filename);
  } break;
  case 1: {
    char *inp = malloc(size + 1);
    inp[size] = '\0';
    memcpy(inp, data, size);
    tidyParseString(tdoc, inp);
    free(inp);
  }
  }

  // Cleanup
  tidyRelease(tdoc);

  return 0;
}