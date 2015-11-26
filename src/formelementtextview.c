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

#include "formelementtextview.h"

static void zak_form_gtk_form_element_textview_class_init (ZakFormGtkFormElementTextviewClass *class);
static void zak_form_gtk_form_element_textview_init (ZakFormGtkFormElementTextview *zak_form_gtk_form_element_textview);

static void zak_form_gtk_form_element_textview_set_property (GObject *object,
                               guint property_id,
                               const GValue *value,
                               GParamSpec *pspec);
static void zak_form_gtk_form_element_textview_get_property (GObject *object,
                               guint property_id,
                               GValue *value,
                               GParamSpec *pspec);

static void zak_form_gtk_form_element_textview_dispose (GObject *gobject);
static void zak_form_gtk_form_element_textview_finalize (GObject *gobject);

static gchar *zak_form_gtk_form_element_textview_get_value (ZakFormGtkFormElementTextview *element);
static gboolean zak_form_gtk_form_element_textview_set_value (ZakFormGtkFormElementTextview *element, const gchar *value);

#define ZAK_FORM_GTK_FORM_ELEMENT_TEXTVIEW_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), ZAK_FORM_GTK_TYPE_FORM_ELEMENT_TEXTVIEW, ZakFormGtkFormElementTextviewPrivate))

typedef struct _ZakFormGtkFormElementTextviewPrivate ZakFormGtkFormElementTextviewPrivate;
struct _ZakFormGtkFormElementTextviewPrivate
	{
		gpointer empty;
	};

G_DEFINE_TYPE (ZakFormGtkFormElementTextview, zak_form_gtk_form_element_textview, ZAK_FORM_GTK_TYPE_FORM_ELEMENT)

static void
zak_form_gtk_form_element_textview_class_init (ZakFormGtkFormElementTextviewClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	ZakFormElementClass *elem_class = ZAK_FORM_ELEMENT_CLASS (klass);

	object_class->set_property = zak_form_gtk_form_element_textview_set_property;
	object_class->get_property = zak_form_gtk_form_element_textview_get_property;
	object_class->dispose = zak_form_gtk_form_element_textview_dispose;
	object_class->finalize = zak_form_gtk_form_element_textview_finalize;

	elem_class->get_value = zak_form_gtk_form_element_textview_get_value;
	elem_class->set_value = zak_form_gtk_form_element_textview_set_value;

	g_type_class_add_private (object_class, sizeof (ZakFormGtkFormElementTextviewPrivate));
}

static void
zak_form_gtk_form_element_textview_init (ZakFormGtkFormElementTextview *zak_form_gtk_form_element_textview)
{
	ZakFormGtkFormElementTextviewPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_TEXTVIEW_GET_PRIVATE (zak_form_gtk_form_element_textview);

}

/**
 * zak_form_gtk_form_element_textview_new:
 *
 * Returns: the newly created #ZakFormGtkFormElementTextview object.
 */
ZakFormGtkFormElement
*zak_form_gtk_form_element_textview_new ()
{
	ZakFormGtkFormElementTextview *zak_form_gtk_form_element_textview;

	zak_form_gtk_form_element_textview = ZAK_FORM_GTK_FORM_ELEMENT_TEXTVIEW (g_object_new (zak_form_gtk_form_element_textview_get_type (), NULL));

	return ZAK_FORM_GTK_FORM_ELEMENT (zak_form_gtk_form_element_textview);
}

/**
 * zak_form_gtk_form_element_textview_xml_parsing:
 * @element:
 * @xmlnode:
 *
 */
gboolean
zak_form_gtk_form_element_textview_xml_parsing (ZakFormElement *element, xmlNodePtr xmlnode)
{
	ZAK_FORM_GTK_FORM_ELEMENT_CLASS (zak_form_gtk_form_element_textview_parent_class)->xml_parsing (element, xmlnode);

	return TRUE;
}

/* PRIVATE */
static void
zak_form_gtk_form_element_textview_set_property (GObject *object,
                   guint property_id,
                   const GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkFormElementTextview *zak_form_gtk_form_element_textview = (ZakFormGtkFormElementTextview *)object;
	ZakFormGtkFormElementTextviewPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_TEXTVIEW_GET_PRIVATE (zak_form_gtk_form_element_textview);

	switch (property_id)
		{
			default:
				G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
				break;
		}
}

static void
zak_form_gtk_form_element_textview_get_property (GObject *object,
                   guint property_id,
                   GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkFormElementTextview *zak_form_gtk_form_element_textview = (ZakFormGtkFormElementTextview *)object;
	ZakFormGtkFormElementTextviewPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_TEXTVIEW_GET_PRIVATE (zak_form_gtk_form_element_textview);

	switch (property_id)
		{
			default:
				G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
				break;
		}
}

static void
zak_form_gtk_form_element_textview_dispose (GObject *gobject)
{
	ZakFormGtkFormElementTextview *zak_form_gtk_form_element_textview = (ZakFormGtkFormElementTextview *)gobject;
	ZakFormGtkFormElementTextviewPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_TEXTVIEW_GET_PRIVATE (zak_form_gtk_form_element_textview);



	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->dispose (gobject);
}

static void
zak_form_gtk_form_element_textview_finalize (GObject *gobject)
{
	ZakFormGtkFormElementTextview *zak_form_gtk_form_element_textview = (ZakFormGtkFormElementTextview *)gobject;
	ZakFormGtkFormElementTextviewPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_TEXTVIEW_GET_PRIVATE (zak_form_gtk_form_element_textview);



	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->finalize (gobject);
}

static gchar
*zak_form_gtk_form_element_textview_get_value (ZakFormGtkFormElementTextview *element)
{
	gchar *ret;

	GtkWidget *w;

	GtkTextBuffer *buf;
	GtkTextIter start;
	GtkTextIter end;

	w = zak_form_gtk_form_element_get_widget (ZAK_FORM_GTK_FORM_ELEMENT (element));

	buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (w));
	gtk_text_buffer_get_bounds (buf, &start, &end);
	ret = gtk_text_buffer_get_text (buf, &start, &end, FALSE);

	return ret;
}

static gboolean
zak_form_gtk_form_element_textview_set_value (ZakFormGtkFormElementTextview *element, const gchar *value)
{
	GtkWidget *w;

	GtkTextBuffer *buf;

	w = zak_form_gtk_form_element_get_widget (ZAK_FORM_GTK_FORM_ELEMENT (element));

	buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (w));
	gtk_text_buffer_set_text (buf, value, -1);

	return TRUE;
}
