if PLATFORM_WIN32
libmodulesext = -0.dll
libmodulesdir = $(bindir)
else
libmodulesext = .so
libmodulesdir = $(libdir)
endif

libzakformmodulesdir = `pkg-config --variable=modulesdir libzakform`

LIBS = $(ZAKFORMGTK_LIBS)

AM_CPPFLAGS = $(ZAKFORMGTK_CFLAGS) \
              -DLOCALEDIR=\"$(localedir)\" \
              -DG_LOG_DOMAIN=\"ZakFormGtk\"

lib_LTLIBRARIES = libzakformgtk.la

libzakformgtk_la_SOURCES = \
                        form.c \
                        formelement.c \
                        formelementcheck.c \
                        formelementcombo.c \
                        formelemententry.c \
                        formelementlabel.c \
                        formelementradio.c \
                        formelementspin.c \
                        formelementtextview.c

libzakformgtk_la_LDFLAGS = -no-undefined

gir_include = \
                             form.h \
                             formelement.h \
                             formelementcheck.h \
                             formelementcombo.h \
                             formelemententry.h \
                             formelementlabel.h \
                             formelementradio.h \
                             formelementspin.h \
                             formelementtextview.h

libzakformgtk_include_HEADERS = \
                             libzakformgtk.h \
                             $(git_include)

libzakformgtk_includedir = $(includedir)/libzakformgtk

install-exec-hook:
	cd $(libzakformmodulesdir) && \
	ln -s -f $(libmodulesdir)/libzakformgtk$(libmodulesext) .

uninstall-hook:
	rm -f $(libzakformmodulesdir)/libzakformgtk$(libmodulesext)

CLEANFILES =

-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --warn-all
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

if HAVE_INTROSPECTION
introspection_sources = $(libzakformgtk_la_SOURCES) $(gir_include)

ZakFormGtk-1.0.gir: libzakformgtk.la
ZakFormGtk_1_0_gir_INCLUDES = Gtk-3.0 ZakForm-1.0
ZakFormGtk_1_0_gir_CFLAGS = $(AM_CPPFLAGS)
ZakFormGtk_1_0_gir_LIBS = libzakformgtk.la
ZakFormGtk_1_0_gir_FILES = $(introspection_sources)
INTROSPECTION_GIRS += ZakFormGtk-1.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES += $(gir_DATA) $(typelib_DATA)
endif
