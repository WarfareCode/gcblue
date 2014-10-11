
SUBDIRS =       src include tests

EXTRA_DIST =    diff_ignore autogen.sh openalpp.pc.in VisualStudio

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = openalpp.pc

$(pkgconfig_DATA): config.status

ALL:
	cd $(top_builddir); make -j4

ALL-install:
	cd $(top_builddir); make -j4 install

