extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  // ...
  llvm::MCInst inst;
  if (!inst.parse(stream.ConsumeRemainingBytesAsString(), context)) {
    printer.printInst(&inst, &streamer.getCommentOS(), nullptr);
    Alpha_printInst(&inst, &streamer.getCommentOS(), nullptr); // Call Alpha_printInst here
  }
  // ...
}