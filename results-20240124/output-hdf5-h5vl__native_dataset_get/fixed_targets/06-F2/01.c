#include <iostream>
#include <h5cpp/hdf5.h>

extern "C" {
#include <H5VLnative.h>
}

int main() {
  H5::H5File file("test.h5", H5F_ACC_RDONLY);
  H5::DataSet dataset = file.openDataSet("dataset");

  std::vector<int> data(dataset.getSpace().getSimpleExtentNdims());
  dataset.read(data.data(), H5::PredType::NATIVE_INT);

  for (auto& value : data) {
    std::cout << value << std::endl;
  }

  return 0;
}