#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cJSON.h"
#include "loader.h"

/*
 * Create config files for given path and data.
 */
int create_config_file(const char *config_path, const char *config_filename, const uint8_t *data, size_t size) {
  char filename[512];
  char path[256];
  char command[256];

  sprintf(path, "%s/%s", getenv("HOME"), config_path);
  sprintf(command, "mkdir -p %s", path);

  system(command);

  sprintf(filename, "%s/%s", path, config_filename);

  FILE *fp = fopen(filename, "wb");
  if (!fp) {
    return 1;
  }
  fwrite(data, size, 1, fp);
  fclose(fp);

  return 0;
}

/*
 * Remove config file
 */
void remove_config_file(const char *config_path, const char *config_filename) {
  char filename[512];
  sprintf(filename, "%s/%s/%s", getenv("HOME"), config_path, config_filename);
  unlink(filename);
}

/*
 * Targets the instance creation.
 */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  setenv("HOME", "/tmp", 1);

  // Create implicit layer configuration file
  int result = create_config_file(".local/share/vulkan/implicit_layer.d", "complex_layer.json", data, size);
  if (result) {
    return 0;
  }

  // Create loader configuration file
  result = create_config_file(".local/share/vulkan/loader_settings.d", "vk_loader_settings.json", data, size);
  if (result) {
    return 0;
  }

  // Create icd configuration file
  result = create_config_file(".local/share/vulkan/icd.d", "icd_test.json", data, size);
  if (result) {
    return 0;
  }

  setenv("VK_LOADER_LAYERS_ENABLE", "all", 1);

  VkLayerDispatchTable_ dispatch_table;
  char *device_name = "device_name";
  char *instance_name = "instance_name";

  loader_lookup_device_dispatch_table(&dispatch_table, device_name, instance_name);

  // Clean up config files
  remove_config_file(".local/share/vulkan/implicit_layer.d", "complex_layer.json");
  remove_config_file(".local/share/vulkan/loader_settings.d", "vk_loader_settings.json");
  remove_config_file(".local/share/vulkan/icd.d", "icd_test.json");

  return 0;
}