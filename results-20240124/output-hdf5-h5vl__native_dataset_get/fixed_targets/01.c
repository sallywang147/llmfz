#include "H5Cpp.h"

using namespace H5;

int main() {
    H5File file("test.h5", H5F_ACC_RDONLY);
    DataSet dataset = file.openDataSet("dataset");

    // Get the native dataset handle
    hid_t native_dataset_id = dataset.getId();

    // Get the native dataset type handle
    hid_t native_datatype_id = dataset.getTypeId();

    // Get the native data space handle
    hid_t native_dataspace_id = dataset.getSpaceId();

    // Get the native file handle
    hid_t native_file_id = file.getId();

    // Close the file
    file.close();

    return 0;
}