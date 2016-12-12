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

libzakformgtk_include_HEADERS = \
                             libzakformgtk.h \
                             form.h \
                             formelement.h \
                             formelementcheck.h \
                             formelementcombo.h \
                             formelemententry.h \
                             formelementlabel.h \
                             formelementradio.h \
                             formelementspin.h \
                             formelementtextview.h

libzakformgtk_includedir = $(includedir)/libzakformgtk

install-exec-hook:
	cd $(libzakformmodulesdir) && \
	ln -s -f $(libmodulesdir)/libzakformgtk$(libmodulesext) .

uninstall-hook:
	rm -f $(libzakformmodulesdir)/libzakformgtk$(libmodulesext)
