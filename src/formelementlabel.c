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

#include "formelementlabel.h"

static void zak_form_gtk_form_element_label_class_init (ZakFormGtkFormElementLabelClass *class);
static void zak_form_gtk_form_element_label_init (ZakFormGtkFormElementLabel *zak_form_gtk_form_element_label);

static void zak_form_gtk_form_element_label_set_property (GObject *object,
                                                          guint property_id,
                                                          const GValue *value,
                                                          GParamSpec *pspec);
static void zak_form_gtk_form_element_label_get_property (GObject *object,
                                                          guint property_id,
                                                          GValue *value,
                                                          GParamSpec *pspec);

static void zak_form_gtk_form_element_label_dispose (GObject *gobject);
static void zak_form_gtk_form_element_label_finalize (GObject *gobject);

static GValue *zak_form_gtk_form_element_label_get_value (ZakFormGtkFormElementLabel *element);
static gboolean zak_form_gtk_form_element_label_set_value (ZakFormGtkFormElementLabel *element, GValue *value);

#define ZAK_FORM_GTK_FORM_ELEMENT_LABEL_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), ZAK_FORM_GTK_TYPE_FORM_ELEMENT_LABEL, ZakFormGtkFormElementLabelPrivate))

typedef struct _ZakFormGtkFormElementLabelPrivate ZakFormGtkFormElementLabelPrivate;
struct _ZakFormGtkFormElementLabelPrivate
	{
		gpointer empty;
	};

G_DEFINE_TYPE (ZakFormGtkFormElementLabel, zak_form_gtk_form_element_label, ZAK_FORM_GTK_TYPE_FORM_ELEMENT)

static void
zak_form_gtk_form_element_label_class_init (ZakFormGtkFormElementLabelClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	ZakFormElementClass *elem_class = ZAK_FORM_ELEMENT_CLASS (klass);

	object_class->set_property = zak_form_gtk_form_element_label_set_property;
	object_class->get_property = zak_form_gtk_form_element_label_get_property;
	object_class->dispose = zak_form_gtk_form_element_label_dispose;
	object_class->finalize = zak_form_gtk_form_element_label_finalize;

	elem_class->get_value = zak_form_gtk_form_element_label_get_value;
	elem_class->set_value = zak_form_gtk_form_element_label_set_value;

	g_type_class_add_private (object_class, sizeof (ZakFormGtkFormElementLabelPrivate));
}

static void
zak_form_gtk_form_element_label_init (ZakFormGtkFormElementLabel *zak_form_gtk_form_element_label)
{
	ZakFormGtkFormElementLabelPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_LABEL_GET_PRIVATE (zak_form_gtk_form_element_label);

}

/**
 * zak_form_gtk_form_element_label_new:
 *
 * Returns: the newly created #ZakFormGtkFormElementLabel object.
 */
ZakFormGtkFormElement
*zak_form_gtk_form_element_label_new ()
{
	ZakFormGtkFormElementLabel *zak_form_gtk_form_element_label;

	zak_form_gtk_form_element_label = ZAK_FORM_GTK_FORM_ELEMENT_LABEL (g_object_new (zak_form_gtk_form_element_label_get_type (), NULL));

	return ZAK_FORM_GTK_FORM_ELEMENT (zak_form_gtk_form_element_label);
}

/**
 * zak_form_gtk_form_element_label_xml_parsing:
 * @element:
 * @xmlnode:
 *
 */
gboolean
zak_form_gtk_form_element_label_xml_parsing (ZakFormElement *element, xmlNodePtr xmlnode)
{
	ZAK_FORM_GTK_FORM_ELEMENT_CLASS (zak_form_gtk_form_element_label_parent_class)->xml_parsing (element, xmlnode);

	return TRUE;
}

/* PRIVATE */
static void
zak_form_gtk_form_element_label_set_property (GObject *object,
                   guint property_id,
                   const GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkFormElementLabel *zak_form_gtk_form_element_label = (ZakFormGtkFormElementLabel *)object;
	ZakFormGtkFormElementLabelPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_LABEL_GET_PRIVATE (zak_form_gtk_form_element_label);

	switch (property_id)
		{
			default:
				G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
				break;
		}
}

static void
zak_form_gtk_form_element_label_get_property (GObject *object,
                   guint property_id,
                   GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkFormElementLabel *zak_form_gtk_form_element_label = (ZakFormGtkFormElementLabel *)object;
	ZakFormGtkFormElementLabelPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_LABEL_GET_PRIVATE (zak_form_gtk_form_element_label);

	switch (property_id)
		{
			default:
				G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
				break;
		}
}

static void
zak_form_gtk_form_element_label_dispose (GObject *gobject)
{
	ZakFormGtkFormElementLabel *zak_form_gtk_form_element_label = (ZakFormGtkFormElementLabel *)gobject;
	ZakFormGtkFormElementLabelPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_LABEL_GET_PRIVATE (zak_form_gtk_form_element_label);



	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->dispose (gobject);
}

static void
zak_form_gtk_form_element_label_finalize (GObject *gobject)
{
	ZakFormGtkFormElementLabel *zak_form_gtk_form_element_label = (ZakFormGtkFormElementLabel *)gobject;
	ZakFormGtkFormElementLabelPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_LABEL_GET_PRIVATE (zak_form_gtk_form_element_label);



	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->finalize (gobject);
}

static GValue
*zak_form_gtk_form_element_label_get_value (ZakFormGtkFormElementLabel *element)
{
	GtkWidget *w;

	w = zak_form_gtk_form_element_get_widget (ZAK_FORM_GTK_FORM_ELEMENT (element));

	return zak_utils_gvalue_new_string ((gchar *)gtk_label_get_text (GTK_LABEL (w)));
}

static gboolean
zak_form_gtk_form_element_label_set_value (ZakFormGtkFormElementLabel *element, GValue *value)
{
	GtkWidget *w;

	w = zak_form_gtk_form_element_get_widget (ZAK_FORM_GTK_FORM_ELEMENT (element));

	gtk_label_set_text (GTK_LABEL (w), g_value_get_string (value));

	return TRUE;
}
