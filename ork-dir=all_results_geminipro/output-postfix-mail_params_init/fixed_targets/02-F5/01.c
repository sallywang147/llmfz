#include <fuzzer/FuzzedDataProvider.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mail_params.h"

void mail_params_init() {
  // Initialize mail_params.
  mail_params_t *params = mail_params_new();
  mail_params_free(params);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Initialize mail_params.
  mail_params_init();

  // Read input data.
  FuzzedDataProvider provider(data, size);
  size_t num_params = provider.ConsumeIntegralInRange<size_t>(0, 100);
  for (size_t i = 0; i < num_params; i++) {
    size_t param_name_length = provider.ConsumeIntegralInRange<size_t>(0, 100);
    std::string param_name = provider.ConsumeRandomLengthString(param_name_length);
    size_t param_value_length = provider.ConsumeIntegralInRange<size_t>(0, 100);
    std::string param_value = provider.ConsumeRandomLengthString(param_value_length);

    // Set mail parameter.
    mail_params_set(param_name.c_str(), param_value.c_str());
  }

  // Get mail parameters.
  const char *param_names[100];
  const char *param_values[100];
  size_t num_params_returned;
  mail_params_get_all(param_names, param_values, &num_params_returned);

  // Print mail parameters.
  for (size_t i = 0; i < num_params_returned; i++) {
    printf("%s = %s\n", param_names[i], param_values[i]);
  }

  return 0;
}