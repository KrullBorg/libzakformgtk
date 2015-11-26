/*
 * Copyright (C) 2015 Andrea Zagli <azagli@libero.it>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __ZAK_FORM_GTK_FORM_ELEMENT_H__
#define __ZAK_FORM_GTK_FORM_ELEMENT_H__


#include <glib-object.h>
#include <glib/gi18n-lib.h>

#include <gtk/gtk.h>

#include <libxml/tree.h>

#include <libzakform/libzakform.h>


G_BEGIN_DECLS


#define ZAK_FORM_GTK_TYPE_FORM_ELEMENT zak_form_gtk_form_element_get_type ()
G_DECLARE_DERIVABLE_TYPE (ZakFormGtkFormElement, zak_form_gtk_form_element, ZAK_FORM_GTK, FORM_ELEMENT, ZakFormElement)

struct _ZakFormGtkFormElementClass
	{
		ZakFormElementClass parent_class;

		void (*xml_parsing) (ZakFormElement *element, xmlNode *xmlnode);
	};


void zak_form_gtk_form_element_set_gtkbuilder (ZakFormGtkFormElement *element, GtkBuilder *gtkbuilder);
GtkBuilder *zak_form_gtk_form_element_get_gtkbuilder (ZakFormGtkFormElement *element);

gboolean zak_form_gtk_form_element_set_widget_from_gtkbuilder (ZakFormGtkFormElement *element,
															   GtkBuilder *gtkbuilder,
															   const gchar *widget_name);

GtkWidget *zak_form_gtk_form_element_get_widget (ZakFormGtkFormElement *element);
void zak_form_gtk_form_element_set_widget (ZakFormGtkFormElement *element, GtkWidget *widget, const gchar *widget_name);

gchar *zak_form_gtk_form_element_get_widget_name (ZakFormGtkFormElement *element);

GtkWidget *zak_gtk_form_element_get_label (ZakFormGtkFormElement *element);
void zak_form_gtk_form_element_set_label (ZakFormGtkFormElement *element, GtkWidget *label);


G_END_DECLS


#endif /* __ZAK_FORM_GTK_FORM_ELEMENT_H__ */
