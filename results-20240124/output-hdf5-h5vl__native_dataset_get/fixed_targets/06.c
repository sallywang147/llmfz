#include <H5Cpp.h>

extern "C" {
#include <H5VL__native_dataset.h>
}

int main() {
  H5::H5File file("test.h5", H5F_ACC_RDONLY);
  H5::DataSet dataset = file.openDataSet("dataset");

  // Get the native dataset handle
  H5VL__native_dataset_get(dataset.getId(), &native_dataset);

  // Use the native dataset handle to access the data
  ...

  return 0;
}