static void run_tests_with_level_2_interface(char filename[], bool ogg, bool use_padding, const uint8_t *data, size_t size) {
    FLAC::Metadata::Chain chain;
    FLAC::Metadata::Iterator iterator;
    FLAC::Metadata::Prototype *metadata_block_get = nullptr;
    FLAC::Metadata::Prototype *metadata_block_transfer = nullptr;
    FLAC::Metadata::Prototype *metadata_block_put = nullptr;

    if (!chain.is_valid())
        return;

    // Add the call to chain_read_with_callbacks_ here
    if (!chain.read_with_callbacks_(filename, ogg))
        return;

    iterator.init(chain);

    for (size_t i = 0; i < size; i++) {
        // Rest of the code remains the same
    }

    if (metadata_block_transfer != 0) {
        delete metadata_block_transfer;
        metadata_block_transfer = nullptr;
    }

    chain.status();
    chain.sort_padding();
    chain.merge_padding();

    chain.check_if_tempfile_needed(!use_padding);
    chain.write(use_padding);
}