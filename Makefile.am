ACLOCAL_AMFLAGS = -I m4
SUBDIRS = activity_diagram src

if HAVE_DOXYGEN
doxyfile.stamp:
	$(DOXYGEN) Doxyfile
	echo Timestamp > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp
clean-local:
	rm Doxyfile
	rm -rf doc
endif
