/*
 * Copyright (C) 2015 Andrea Zagli <azagli@libero.it>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <gtk/gtk.h>

#include "form.h"

int
main (int argc, char *argv[])
{
	GtkBuilder *builder;
	GtkWidget *w;

	ZakFormGtkForm *form;

	gtk_init (&argc, &argv);

	builder = gtk_builder_new ();
	gtk_builder_add_objects_from_file (builder, GUIDIR "/test.ui", g_strsplit ("w_main", "|", -1), NULL);

	w = GTK_WIDGET (gtk_builder_get_object (builder, "w_main"));

	g_signal_connect (w, "delete-event",
					  gtk_main_quit, NULL);

	form = zak_form_gtk_form_new ();
	zak_form_gtk_form_set_gtkbuilder (form, builder);
	zak_form_form_load_from_file (ZAK_FORM_FORM (form), GUIDIR "/test.xml");

	gtk_widget_show_all (w);

	gtk_main ();

	return 0;
}
