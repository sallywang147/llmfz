#include <iostream>
#include <h5cpp/hdf5.h>

extern "C" {
#include <H5VLnative.h>
}

int H5VL__native_dataset_get(char *buf, struct H5VL_dataset_get_args_t *args, size_t buf_size, char **buf_ptr);

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