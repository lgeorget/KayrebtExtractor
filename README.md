cgrapher4gcc
============

`cgrapher4gcc` is a simple gcc plugin aiming at dumping the AST of every
function in a C file in a human-readable form. As its name suggests, it's
supposed to print graphs, and more specifically UML2-like activity diagrams.
However, as it's still a preversion, it justs outputs lines of text describing
more or less precisely what happens in the code.

Compiling
---------

First of all, make sure you use GCC 4.8. The API for plugins and GCC ABI 
change a lot from major version to major version so it's highly probable that
this code won't compile either on GCC 4.7 or GCC 4.9.

Next, change the path to the GCC plugins headers in the Makefile (in the CFLAGS
definition). (You could also use pkg-config, as proper developpers do...
I'll change it for version 1.0.)

The last version pushed to repo is not guaranteed to compile. You should
checkout tag "compilable" if it exists for an almost-stable version.
Then, running `make` should leave you with a plugin, by the name of 
`myplugin.so` or whatever the value of `EXEC` in the Makefile is. This .so file
is the GCC plugin, handle with care.

Running
-------

`grapher4gcc` is shipped with a C source file example, namely `test.c`. Don't
try to understand the code written in this file, it's merely a torture tool for
the plugin. `make run` runs GCC with the plugin on `test.c`. Of course, you can
use other source files but the plugin currently doesn't handle anything else 
than C, not even C++. You can try any language supported by GCC as the AST are 
all written in the same language, GENERIC. However, some syntactic constructs
will not be supported. Even in C, you may find some lacking stuff.

In short, change the `run` target to suit your needs, or just make your own 
Makefile based on the shipped-in one and it should do the job.
