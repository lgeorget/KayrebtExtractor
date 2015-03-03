ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src

if HAVE_DOXYGEN
doxyfile.stamp:
	$(DOXYGEN) Doxyfile
	echo Timestamp > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp
clean-local:
	rm -rf doc/
endif
