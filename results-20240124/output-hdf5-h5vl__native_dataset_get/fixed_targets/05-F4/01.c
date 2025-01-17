#include <H5Cpp.h>

extern "C" {
#include <hdf5.h>
}

int main() {
  try {
    // Open an existing HDF5 file
    H5::H5File file("myfile.h5", H5F_ACC_RDONLY);

    // Open the dataset within the file
    H5::DataSet dataset = file.openDataSet("mydataset");

    // Get the native data type of the dataset
    hid_t native_type = H5VL__native_dataset_get(dataset.getId());

    // Print the native data type
    std::cout << "Native data type: " << native_type << std::endl;

    // Close the dataset and file
    dataset.close();
    file.close();
  }
  catch (H5::Exception &e) {
    std::cerr << "Error: " << e.getDetailMessage() << std::endl;
    return 1;
  }

  return 0;
}