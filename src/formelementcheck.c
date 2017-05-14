/*
 * Copyright (C) 2015-2017 Andrea Zagli <azagli@libero.it>
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

#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif

#include <libzakutils/libzakutils.h>

#include "formelementcheck.h"

static void zak_form_gtk_form_element_check_class_init (ZakFormGtkFormElementCheckClass *class);
static void zak_form_gtk_form_element_check_init (ZakFormGtkFormElementCheck *zak_form_gtk_form_element_check);

static void zak_form_gtk_form_element_check_set_property (GObject *object,
                                                          guint property_id,
                                                          const GValue *value,
                                                          GParamSpec *pspec);
static void zak_form_gtk_form_element_check_get_property (GObject *object,
                                                          guint property_id,
                                                          GValue *value,
                                                          GParamSpec *pspec);

static void zak_form_gtk_form_element_check_dispose (GObject *gobject);
static void zak_form_gtk_form_element_check_finalize (GObject *gobject);

static GValue *zak_form_gtk_form_element_check_get_value (ZakFormGtkFormElementCheck *element);
static gboolean zak_form_gtk_form_element_check_set_value (ZakFormGtkFormElementCheck *element, GValue *value);

#define ZAK_FORM_GTK_FORM_ELEMENT_CHECK_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), ZAK_FORM_GTK_TYPE_FORM_ELEMENT_CHECK, ZakFormGtkFormElementCheckPrivate))

typedef struct _ZakFormGtkFormElementCheckPrivate ZakFormGtkFormElementCheckPrivate;
struct _ZakFormGtkFormElementCheckPrivate
	{
		gpointer empty;
	};

G_DEFINE_TYPE (ZakFormGtkFormElementCheck, zak_form_gtk_form_element_check, ZAK_FORM_GTK_TYPE_FORM_ELEMENT)

static void
zak_form_gtk_form_element_check_class_init (ZakFormGtkFormElementCheckClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	ZakFormElementClass *elem_class = ZAK_FORM_ELEMENT_CLASS (klass);

	object_class->set_property = zak_form_gtk_form_element_check_set_property;
	object_class->get_property = zak_form_gtk_form_element_check_get_property;
	object_class->dispose = zak_form_gtk_form_element_check_dispose;
	object_class->finalize = zak_form_gtk_form_element_check_finalize;

	elem_class->get_value = zak_form_gtk_form_element_check_get_value;
	elem_class->set_value = zak_form_gtk_form_element_check_set_value;

	g_type_class_add_private (object_class, sizeof (ZakFormGtkFormElementCheckPrivate));
}

static void
zak_form_gtk_form_element_check_init (ZakFormGtkFormElementCheck *zak_form_gtk_form_element_check)
{
	ZakFormGtkFormElementCheckPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_CHECK_GET_PRIVATE (zak_form_gtk_form_element_check);

}

/**
 * zak_form_gtk_form_element_check_new:
 *
 * Returns: the newly created #ZakFormGtkFormElementCheck object.
 */
ZakFormGtkFormElement
*zak_form_gtk_form_element_check_new ()
{
	ZakFormGtkFormElementCheck *zak_form_gtk_form_element_check;

	zak_form_gtk_form_element_check = ZAK_FORM_GTK_FORM_ELEMENT_CHECK (g_object_new (zak_form_gtk_form_element_check_get_type (), NULL));

	return ZAK_FORM_GTK_FORM_ELEMENT (zak_form_gtk_form_element_check);
}

/**
 * zak_form_gtk_form_element_check_xml_parsing:
 * @element:
 * @xmlnode:
 *
 */
gboolean
zak_form_gtk_form_element_check_xml_parsing (ZakFormElement *element, xmlNodePtr xmlnode)
{
	ZAK_FORM_GTK_FORM_ELEMENT_CLASS (zak_form_gtk_form_element_check_parent_class)->xml_parsing (element, xmlnode);

	return TRUE;
}

/* PRIVATE */
static void
zak_form_gtk_form_element_check_set_property (GObject *object,
                   guint property_id,
                   const GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkFormElementCheck *zak_form_gtk_form_element_check = (ZakFormGtkFormElementCheck *)object;
	ZakFormGtkFormElementCheckPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_CHECK_GET_PRIVATE (zak_form_gtk_form_element_check);

	switch (property_id)
		{
			default:
				G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
				break;
		}
}

static void
zak_form_gtk_form_element_check_get_property (GObject *object,
                   guint property_id,
                   GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkFormElementCheck *zak_form_gtk_form_element_check = (ZakFormGtkFormElementCheck *)object;
	ZakFormGtkFormElementCheckPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_CHECK_GET_PRIVATE (zak_form_gtk_form_element_check);

	switch (property_id)
		{
			default:
				G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
				break;
		}
}

static void
zak_form_gtk_form_element_check_dispose (GObject *gobject)
{
	ZakFormGtkFormElementCheck *zak_form_gtk_form_element_check = (ZakFormGtkFormElementCheck *)gobject;
	ZakFormGtkFormElementCheckPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_CHECK_GET_PRIVATE (zak_form_gtk_form_element_check);



	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->dispose (gobject);
}

static void
zak_form_gtk_form_element_check_finalize (GObject *gobject)
{
	ZakFormGtkFormElementCheck *zak_form_gtk_form_element_check = (ZakFormGtkFormElementCheck *)gobject;
	ZakFormGtkFormElementCheckPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_CHECK_GET_PRIVATE (zak_form_gtk_form_element_check);



	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->finalize (gobject);
}

static GValue
*zak_form_gtk_form_element_check_get_value (ZakFormGtkFormElementCheck *element)
{
	GValue *ret;

	GtkWidget *w;

	ret = zak_utils_gvalue_new_string ("FALSE");

	w = zak_form_gtk_form_element_get_widget (ZAK_FORM_GTK_FORM_ELEMENT (element));

	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (w)))
		{
			g_value_set_string (ret, "TRUE");
		}
	else if (gtk_toggle_button_get_inconsistent (GTK_TOGGLE_BUTTON (w)))
		{
			g_value_set_string (ret, "");
		}

	return ret;
}

static gboolean
zak_form_gtk_form_element_check_set_value (ZakFormGtkFormElementCheck *element, GValue *value)
{
	GtkWidget *w;

	gboolean active;
	gchar *str_value;

	w = zak_form_gtk_form_element_get_widget (ZAK_FORM_GTK_FORM_ELEMENT (element));

	str_value = g_strstrip (g_strdup (g_value_get_string (value)));

	if (strcmp (str_value, "0") == 0
	    || strcasecmp (str_value, "f") == 0
	    || strcasecmp (str_value, "false") == 0
	    || strcasecmp (str_value, "n") == 0
	    || strcasecmp (str_value, "no") == 0)
		{
			active = FALSE;
		}
	else if (strcmp (str_value, "1") == 0
	    || strcasecmp (str_value, "t") == 0
	    || strcasecmp (str_value, "true") == 0
	    || strcasecmp (str_value, "y") == 0
	    || strcasecmp (str_value, "yes") == 0)
		{
			active = TRUE;
		}

	g_free (str_value);

	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (w), active);

	return TRUE;
}
