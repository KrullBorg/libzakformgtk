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

#ifndef __ZAK_FORM_GTK_FORM_H__
#define __ZAK_FORM_GTK_FORM_H__


#include <glib-object.h>

#include <gtk/gtk.h>

#include <libzakform/libzakform.h>


G_BEGIN_DECLS


#define ZAK_FORM_GTK_TYPE_FORM zak_form_gtk_form_get_type ()
G_DECLARE_DERIVABLE_TYPE (ZakFormGtkForm, zak_form_gtk_form, ZAK_FORM_GTK, FORM, ZakFormForm)

struct _ZakFormGtkFormClass
{
	ZakFormFormClass parent_class;
};


ZakFormGtkForm *zak_form_gtk_form_new (void);

void zak_form_gtk_form_set_gtkbuilder (ZakFormGtkForm *form, GtkBuilder *builder);

gboolean zak_form_gtk_form_is_valid (ZakFormGtkForm *form, GtkWidget *parent_window);


G_END_DECLS


#endif /* __ZAK_FORM_GTK_FORM_H__ */
