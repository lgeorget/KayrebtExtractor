ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src

EXTRA_DIST = Doxyfile.in custom.css

if HAVE_DOXYGEN
doxyfile.stamp:
	$(DOXYGEN) Doxyfile
	echo Timestamp > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp
clean-local:
	rm Doxyfile
	rm -rf doc/
endif
