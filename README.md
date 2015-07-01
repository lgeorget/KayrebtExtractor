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

You may want to make a symlink from your library `kayrebt_extractor.so` to the
GCC plugin installation directory.

Running
-------

`Kayrebt::Extractor` works best with C. You can try any language supported by
GCC as the CFG are all written in the same language, GIMPLE. However, the
output is likely to be mangled enough to be unusable.

To compile a project, add a configuration file and run with

    make CC=gcc CFLAGS=-fplugin=kayrebt_extractor
