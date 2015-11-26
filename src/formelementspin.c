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

#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif

#include "formelementspin.h"

static void zak_form_gtk_form_element_spin_class_init (ZakFormGtkFormElementSpinClass *class);
static void zak_form_gtk_form_element_spin_init (ZakFormGtkFormElementSpin *zak_form_gtk_form_element_spin);

static void zak_form_gtk_form_element_spin_set_property (GObject *object,
                               guint property_id,
                               const GValue *value,
                               GParamSpec *pspec);
static void zak_form_gtk_form_element_spin_get_property (GObject *object,
                               guint property_id,
                               GValue *value,
                               GParamSpec *pspec);

static void zak_form_gtk_form_element_spin_dispose (GObject *gobject);
static void zak_form_gtk_form_element_spin_finalize (GObject *gobject);

static gchar *zak_form_gtk_form_element_spin_get_value (ZakFormGtkFormElementSpin *element);
static gboolean zak_form_gtk_form_element_spin_set_value (ZakFormGtkFormElementSpin *element, const gchar *value);

#define ZAK_FORM_GTK_FORM_ELEMENT_SPIN_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), ZAK_FORM_GTK_TYPE_FORM_ELEMENT_SPIN, ZakFormGtkFormElementSpinPrivate))

typedef struct _ZakFormGtkFormElementSpinPrivate ZakFormGtkFormElementSpinPrivate;
struct _ZakFormGtkFormElementSpinPrivate
	{
		gpointer empty;
	};

G_DEFINE_TYPE (ZakFormGtkFormElementSpin, zak_form_gtk_form_element_spin, ZAK_FORM_GTK_TYPE_FORM_ELEMENT)

static void
zak_form_gtk_form_element_spin_class_init (ZakFormGtkFormElementSpinClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	ZakFormElementClass *elem_class = ZAK_FORM_ELEMENT_CLASS (klass);

	object_class->set_property = zak_form_gtk_form_element_spin_set_property;
	object_class->get_property = zak_form_gtk_form_element_spin_get_property;
	object_class->dispose = zak_form_gtk_form_element_spin_dispose;
	object_class->finalize = zak_form_gtk_form_element_spin_finalize;

	elem_class->get_value = zak_form_gtk_form_element_spin_get_value;
	elem_class->set_value = zak_form_gtk_form_element_spin_set_value;

	g_type_class_add_private (object_class, sizeof (ZakFormGtkFormElementSpinPrivate));
}

static void
zak_form_gtk_form_element_spin_init (ZakFormGtkFormElementSpin *zak_form_gtk_form_element_spin)
{
	ZakFormGtkFormElementSpinPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_SPIN_GET_PRIVATE (zak_form_gtk_form_element_spin);

}

/**
 * zak_form_gtk_form_element_spin_new:
 *
 * Returns: the newly created #ZakFormGtkFormElementSpin object.
 */
ZakFormGtkFormElement
*zak_form_gtk_form_element_spin_new ()
{
	ZakFormGtkFormElementSpin *zak_form_gtk_form_element_spin;

	zak_form_gtk_form_element_spin = ZAK_FORM_GTK_FORM_ELEMENT_SPIN (g_object_new (zak_form_gtk_form_element_spin_get_type (), NULL));

	return ZAK_FORM_GTK_FORM_ELEMENT (zak_form_gtk_form_element_spin);
}

/**
 * zak_form_gtk_form_element_spin_xml_parsing:
 * @element:
 * @xmlnode:
 *
 */
gboolean
zak_form_gtk_form_element_spin_xml_parsing (ZakFormElement *element, xmlNodePtr xmlnode)
{
	ZAK_FORM_GTK_FORM_ELEMENT_CLASS (zak_form_gtk_form_element_spin_parent_class)->xml_parsing (element, xmlnode);

	return TRUE;
}

/* PRIVATE */
static void
zak_form_gtk_form_element_spin_set_property (GObject *object,
                   guint property_id,
                   const GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkFormElementSpin *zak_form_gtk_form_element_spin = (ZakFormGtkFormElementSpin *)object;
	ZakFormGtkFormElementSpinPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_SPIN_GET_PRIVATE (zak_form_gtk_form_element_spin);

	switch (property_id)
		{
			default:
				G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
				break;
		}
}

static void
zak_form_gtk_form_element_spin_get_property (GObject *object,
                   guint property_id,
                   GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkFormElementSpin *zak_form_gtk_form_element_spin = (ZakFormGtkFormElementSpin *)object;
	ZakFormGtkFormElementSpinPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_SPIN_GET_PRIVATE (zak_form_gtk_form_element_spin);

	switch (property_id)
		{
			default:
				G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
				break;
		}
}

static void
zak_form_gtk_form_element_spin_dispose (GObject *gobject)
{
	ZakFormGtkFormElementSpin *zak_form_gtk_form_element_spin = (ZakFormGtkFormElementSpin *)gobject;
	ZakFormGtkFormElementSpinPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_SPIN_GET_PRIVATE (zak_form_gtk_form_element_spin);



	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->dispose (gobject);
}

static void
zak_form_gtk_form_element_spin_finalize (GObject *gobject)
{
	ZakFormGtkFormElementSpin *zak_form_gtk_form_element_spin = (ZakFormGtkFormElementSpin *)gobject;
	ZakFormGtkFormElementSpinPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_SPIN_GET_PRIVATE (zak_form_gtk_form_element_spin);



	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->finalize (gobject);
}

static gchar
*zak_form_gtk_form_element_spin_get_value (ZakFormGtkFormElementSpin *element)
{
	gchar *ret;

	GtkWidget *w;

	w = zak_form_gtk_form_element_get_widget (ZAK_FORM_GTK_FORM_ELEMENT (element));

	ret = g_strdup_printf ("%f", gtk_spin_button_get_value (GTK_SPIN_BUTTON (w)));

	return ret;
}

static gboolean
zak_form_gtk_form_element_spin_set_value (ZakFormGtkFormElementSpin *element, const gchar *value)
{
	GtkWidget *w;

	w = zak_form_gtk_form_element_get_widget (ZAK_FORM_GTK_FORM_ELEMENT (element));

	gtk_spin_button_set_value (GTK_SPIN_BUTTON (w), g_strtod (value, NULL));

	return TRUE;
}
