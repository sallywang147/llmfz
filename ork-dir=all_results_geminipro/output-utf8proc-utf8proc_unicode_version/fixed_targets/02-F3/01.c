The provided code has no errors. The build issue is most likely caused by an incorrect compiler invocation or a missing library. Make sure that the compiler is properly configured and that the necessary libraries are linked.

If you are using a compiler like `clang` or `gcc`, you may need to link the `utf8proc` library explicitly. This can be done by adding the `-lutf8proc` flag to the compiler command. For example:

```
clang++ -std=c++11 -I/path/to/utf8proc/include -L/path/to/utf8proc/lib -lutf8proc main.cpp -o main
```

Make sure to replace `/path/to/utf8proc/include` and `/path/to/utf8proc/lib` with the actual paths to the `utf8proc` header files and library.

If you are using a different compiler, refer to its documentation for instructions on how to link external libraries.