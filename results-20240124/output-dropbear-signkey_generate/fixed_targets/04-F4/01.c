/usr/bin/ld: fuzz-wrapfd.o: in function `fuzz_wrapfd_read':
fuzz-wrapfd.c:(.text+0x13): undefined reference to `read'
/usr/bin/ld: fuzz-wrapfd.o: in function `fuzz_wrapfd_write':
fuzz-wrapfd.c:(.text+0x27): undefined reference to `write'
/usr/bin/ld: fuzz-wrapfd.o: in function `fuzz_wrapfd_close':
fuzz-wrapfd.c:(.text+0x3b): undefined reference to `close'