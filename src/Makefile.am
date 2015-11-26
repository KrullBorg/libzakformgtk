LIBS = $(ZAKFORMGTK_LIBS)

AM_CPPFLAGS = $(ZAKFORMGTK_CFLAGS) \
              -DLOCALEDIR=\"$(localedir)\" \
              -DG_LOG_DOMAIN=\"ZakFormGtk\"

lib_LTLIBRARIES = libzakformgtk.la

libzakformgtk_la_SOURCES = \
                        form.c \
                        formelement.c \
                        formelementcheck.c \
                        formelemententry.c

libzakformgtk_la_LDFLAGS = -no-undefined

libzakformgtk_include_HEADERS = \
                             libzakformgtk.h \
                             form.h \
                             formelement.h \
                             formelementcheck.h \
                             formelemententry.h

libzakformgtk_includedir = $(includedir)/libzakformgtk
