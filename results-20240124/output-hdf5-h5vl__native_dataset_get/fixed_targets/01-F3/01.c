#include <H5Cpp.h>
#include <iostream>

extern "C" {
#include <H5VL.h>
}

using namespace H5;

int main() {
  try {
    H5File file("test.h5", H5F_ACC_RDONLY);
    DataSet dataset = file.openDataSet("dataset");

    // Get the native dataset handle
    hid_t native_dataset_id = H5VL__native_dataset_get(dataset.getId());

    // Do something with the native dataset handle...

    // Close the dataset and file
    dataset.close();
    file.close();
  } catch (Exception &e) {
    std::cerr << "Error: " << e.getDetailMessage() << std::endl;
    return -1;
  }

  return 0;
}