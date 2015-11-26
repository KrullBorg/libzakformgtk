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

#ifndef __ZAK_FORM_GTK_FORM_ELEMENT_SPIN_H__
#define __ZAK_FORM_GTK_FORM_ELEMENT_SPIN_H__


#include <glib-object.h>

#include "formelement.h"


G_BEGIN_DECLS


#define ZAK_FORM_GTK_TYPE_FORM_ELEMENT_SPIN                 (zak_form_gtk_form_element_spin_get_type ())
#define ZAK_FORM_GTK_FORM_ELEMENT_SPIN(obj)                 (G_TYPE_CHECK_INSTANCE_CAST ((obj), ZAK_FORM_GTK_TYPE_FORM_ELEMENT_SPIN, ZakFormGtkFormElementSpin))
#define ZAK_FORM_GTK_FORM_ELEMENT_SPIN_CLASS(klass)         (G_TYPE_CHECK_CLASS_CAST ((klass), ZAK_FORM_GTK_TYPE_FORM_ELEMENT_SPIN, ZakFormGtkFormElementSpinClass))
#define ZAK_FORM_GTK_IS_FORM_ELEMENT_SPIN(obj)              (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ZAK_FORM_GTK_TYPE_FORM_ELEMENT_SPIN))
#define ZAK_FORM_GTK_IS_FORM_ELEMENT_SPIN_CLASS(klass)      (G_TYPE_CHECK_CLASS_TYPE ((klass), ZAK_FORM_GTK_TYPE_FORM_ELEMENT_SPIN))
#define ZAK_FORM_GTK_FORM_ELEMENT_SPIN_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS ((obj), ZAK_FORM_GTK_TYPE_FORM_ELEMENT_SPIN, ZakFormGtkFormElementSpinClass))

typedef struct _ZakFormGtkFormElementSpin ZakFormGtkFormElementSpin;
typedef struct _ZakFormGtkFormElementSpinClass ZakFormGtkFormElementSpinClass;

struct _ZakFormGtkFormElementSpin
	{
		ZakFormGtkFormElement parent_instance;
	};

struct _ZakFormGtkFormElementSpinClass
	{
		ZakFormGtkFormElementClass parent_class;
	};


GType zak_form_gtk_form_element_spin_get_type (void);

ZakFormGtkFormElement *zak_form_gtk_form_element_spin_new (void);


G_END_DECLS


#endif /* __ZAK_FORM_GTK_FORM_ELEMENT_SPIN_H__ */
