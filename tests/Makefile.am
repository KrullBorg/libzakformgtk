AM_CPPFLAGS = $(WARN_CFLAGS) \
              $(DISABLE_DEPRECATED_CFLAGS) \
              $(ZAKFORMGTK_CFLAGS) \
              -I$(top_srcdir)/src \
              -DGUIDIR="\"@abs_builddir@\""

LIBS = $(ZAKFORMGTK_LIBS) \
       -export-dynamic

LDADD = $(top_builddir)/src/libzakformgtk.la

noinst_PROGRAMS = \
                  test

EXTRA_DIST = \
             test.xml
