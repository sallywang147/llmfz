#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "aspell.h"
#include "posib_err.hpp"
#include "config.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Aspell
  AspellConfig* spell_config = new_aspell_config();
  AspellSpeller* spell_checker = nullptr;
  AspellCanHaveError* possible_err = nullptr;

  possible_err = new_aspell_speller(spell_config);
  if (aspell_error_number(possible_err) != 0) {
    delete_aspell_config(spell_config);
    return 0;
  } else {
    spell_checker = to_aspell_speller(possible_err);
  }

  // Create PosibErr
  acommon::PosibErrBase els;

  // Create AspellStringEnumeration
  AspellStringEnumeration* config = aspell_speller_suggest(spell_checker, stream.ConsumeRandomLengthString().c_str(), -1);

  // Call the function to fuzz
  aspeller::create_default_readonly_dict(&els, config, spell_config);

  // Cleanup
  delete_aspell_string_enumeration(config);
  delete_aspell_speller(spell_checker);
  delete_aspell_config(spell_config);

  return 0;
}