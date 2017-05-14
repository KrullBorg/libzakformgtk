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

#include "formelemententry.h"

static void zak_form_gtk_form_element_entry_class_init (ZakFormGtkFormElementEntryClass *class);
static void zak_form_gtk_form_element_entry_init (ZakFormGtkFormElementEntry *zak_form_gtk_form_element_entry);

static void zak_form_gtk_form_element_entry_set_property (GObject *object,
                                                          guint property_id,
                                                          const GValue *value,
                                                          GParamSpec *pspec);
static void zak_form_gtk_form_element_entry_get_property (GObject *object,
                                                          guint property_id,
                                                          GValue *value,
                                                          GParamSpec *pspec);

static void zak_form_gtk_form_element_entry_dispose (GObject *gobject);
static void zak_form_gtk_form_element_entry_finalize (GObject *gobject);

static GValue *zak_form_gtk_form_element_entry_get_value (ZakFormGtkFormElementEntry *element);
static gboolean zak_form_gtk_form_element_entry_set_value (ZakFormGtkFormElementEntry *element, GValue *value);

#define ZAK_FORM_GTK_FORM_ELEMENT_ENTRY_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), ZAK_FORM_GTK_TYPE_FORM_ELEMENT_ENTRY, ZakFormGtkFormElementEntryPrivate))

typedef struct _ZakFormGtkFormElementEntryPrivate ZakFormGtkFormElementEntryPrivate;
struct _ZakFormGtkFormElementEntryPrivate
	{
		gpointer empty;
	};

G_DEFINE_TYPE (ZakFormGtkFormElementEntry, zak_form_gtk_form_element_entry, ZAK_FORM_GTK_TYPE_FORM_ELEMENT)

static void
zak_form_gtk_form_element_entry_class_init (ZakFormGtkFormElementEntryClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	ZakFormElementClass *elem_class = ZAK_FORM_ELEMENT_CLASS (klass);

	object_class->set_property = zak_form_gtk_form_element_entry_set_property;
	object_class->get_property = zak_form_gtk_form_element_entry_get_property;
	object_class->dispose = zak_form_gtk_form_element_entry_dispose;
	object_class->finalize = zak_form_gtk_form_element_entry_finalize;

	elem_class->get_value = zak_form_gtk_form_element_entry_get_value;
	elem_class->set_value = zak_form_gtk_form_element_entry_set_value;

	g_type_class_add_private (object_class, sizeof (ZakFormGtkFormElementEntryPrivate));
}

static void
zak_form_gtk_form_element_entry_init (ZakFormGtkFormElementEntry *zak_form_gtk_form_element_entry)
{
	ZakFormGtkFormElementEntryPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_ENTRY_GET_PRIVATE (zak_form_gtk_form_element_entry);

}

/**
 * zak_form_gtk_form_element_entry_new:
 *
 * Returns: the newly created #ZakFormGtkFormElementEntry object.
 */
ZakFormGtkFormElement
*zak_form_gtk_form_element_entry_new ()
{
	ZakFormGtkFormElementEntry *zak_form_gtk_form_element_entry;

	zak_form_gtk_form_element_entry = ZAK_FORM_GTK_FORM_ELEMENT_ENTRY (g_object_new (zak_form_gtk_form_element_entry_get_type (), NULL));

	return ZAK_FORM_GTK_FORM_ELEMENT (zak_form_gtk_form_element_entry);
}

/**
 * zak_form_gtk_form_element_entry_xml_parsing:
 * @element:
 * @xmlnode:
 *
 */
gboolean
zak_form_gtk_form_element_entry_xml_parsing (ZakFormElement *element, xmlNodePtr xmlnode)
{
	ZAK_FORM_GTK_FORM_ELEMENT_CLASS (zak_form_gtk_form_element_entry_parent_class)->xml_parsing (element, xmlnode);

	return TRUE;
}

/* PRIVATE */
static void
zak_form_gtk_form_element_entry_set_property (GObject *object,
                   guint property_id,
                   const GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkFormElementEntry *zak_form_gtk_form_element_entry = (ZakFormGtkFormElementEntry *)object;
	ZakFormGtkFormElementEntryPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_ENTRY_GET_PRIVATE (zak_form_gtk_form_element_entry);

	switch (property_id)
		{
			default:
				G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
				break;
		}
}

static void
zak_form_gtk_form_element_entry_get_property (GObject *object,
                   guint property_id,
                   GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkFormElementEntry *zak_form_gtk_form_element_entry = (ZakFormGtkFormElementEntry *)object;
	ZakFormGtkFormElementEntryPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_ENTRY_GET_PRIVATE (zak_form_gtk_form_element_entry);

	switch (property_id)
		{
			default:
				G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
				break;
		}
}

static void
zak_form_gtk_form_element_entry_dispose (GObject *gobject)
{
	ZakFormGtkFormElementEntry *zak_form_gtk_form_element_entry = (ZakFormGtkFormElementEntry *)gobject;
	ZakFormGtkFormElementEntryPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_ENTRY_GET_PRIVATE (zak_form_gtk_form_element_entry);



	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->dispose (gobject);
}

static void
zak_form_gtk_form_element_entry_finalize (GObject *gobject)
{
	ZakFormGtkFormElementEntry *zak_form_gtk_form_element_entry = (ZakFormGtkFormElementEntry *)gobject;
	ZakFormGtkFormElementEntryPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_ENTRY_GET_PRIVATE (zak_form_gtk_form_element_entry);



	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->finalize (gobject);
}

static GValue
*zak_form_gtk_form_element_entry_get_value (ZakFormGtkFormElementEntry *element)
{
	GValue *ret;

	GtkWidget *w;

	w = zak_form_gtk_form_element_get_widget (ZAK_FORM_GTK_FORM_ELEMENT (element));

	ret = zak_utils_gvalue_new_string ((gchar *)gtk_entry_get_text (GTK_ENTRY (w)));

	return ret;
}

static gboolean
zak_form_gtk_form_element_entry_set_value (ZakFormGtkFormElementEntry *element, GValue *value)
{
	GtkWidget *w;

	w = zak_form_gtk_form_element_get_widget (ZAK_FORM_GTK_FORM_ELEMENT (element));

	gtk_entry_set_text (GTK_ENTRY (w), g_value_get_string (value));

	return TRUE;
}
