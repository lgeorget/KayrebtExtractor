Kayrebt::Extractor
==================

`Kayrebt::Extractor` is a simple gcc plugin aiming at dumping the CFG of any
function in a C file in a human-readable form. It
outputs graphs, and more specifically UML2-like activity diagrams.

Compiling
---------

First of all, make sure you use GCC 4.8. The API for plugins and GCC ABI
change a lot from major version to major version so it's highly probable that
this code won't compile either on GCC 4.7 or GCC 4.9.

The plugin is packaged with autotools so:

  ./configure
  make
  make install

You may want to make a symlink from your library `libgrapher4gcc.so` to the
GCC plugin installation directory.

Running
-------

`Kayrebt::Extractor` is shipped with a C source file example, namely `test.c`. Don't
try to understand the code written in this file, it's merely a torture tool for
the plugin. `make run` runs GCC with the plugin on `test.c`. Of course, you can
use other source files but the plugin currently doesn't handle anything else
than C, not even C++. You can try any language supported by GCC as the CFG are
all written in the same language, GIMPLE. However, the output is likely to be
mangled enough to be unusable.

In short, change the `run` target to suit your needs, or just make your own
Makefile based on the shipped-in one and it should do the job.
