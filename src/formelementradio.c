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

#include "formelementradio.h"

enum
{
	PROP_0,
	PROP_RETURN_VALUE
};

static void zak_form_gtk_form_element_radio_class_init (ZakFormGtkFormElementRadioClass *class);
static void zak_form_gtk_form_element_radio_init (ZakFormGtkFormElementRadio *zak_form_gtk_form_element_radio);

static void zak_form_gtk_form_element_radio_set_property (GObject *object,
                                                          guint property_id,
                                                          const GValue *value,
                                                          GParamSpec *pspec);
static void zak_form_gtk_form_element_radio_get_property (GObject *object,
                                                          guint property_id,
                                                          GValue *value,
                                                          GParamSpec *pspec);

static void zak_form_gtk_form_element_radio_dispose (GObject *gobject);
static void zak_form_gtk_form_element_radio_finalize (GObject *gobject);

static GValue *zak_form_gtk_form_element_radio_get_value (ZakFormGtkFormElementRadio *element);
static gboolean zak_form_gtk_form_element_radio_set_value (ZakFormGtkFormElementRadio *element, GValue *value);

#define ZAK_FORM_GTK_FORM_ELEMENT_RADIO_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), ZAK_FORM_GTK_TYPE_FORM_ELEMENT_RADIO, ZakFormGtkFormElementRadioPrivate))

typedef struct _ZakFormGtkFormElementRadioPrivate ZakFormGtkFormElementRadioPrivate;
struct _ZakFormGtkFormElementRadioPrivate
	{
		gchar *return_value;
	};

G_DEFINE_TYPE (ZakFormGtkFormElementRadio, zak_form_gtk_form_element_radio, ZAK_FORM_GTK_TYPE_FORM_ELEMENT)

static void
zak_form_gtk_form_element_radio_class_init (ZakFormGtkFormElementRadioClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	ZakFormElementClass *elem_class = ZAK_FORM_ELEMENT_CLASS (klass);

	object_class->set_property = zak_form_gtk_form_element_radio_set_property;
	object_class->get_property = zak_form_gtk_form_element_radio_get_property;
	object_class->dispose = zak_form_gtk_form_element_radio_dispose;
	object_class->finalize = zak_form_gtk_form_element_radio_finalize;

	elem_class->get_value = zak_form_gtk_form_element_radio_get_value;
	elem_class->set_value = zak_form_gtk_form_element_radio_set_value;

	g_type_class_add_private (object_class, sizeof (ZakFormGtkFormElementRadioPrivate));

	g_object_class_install_property (object_class, PROP_RETURN_VALUE,
	                                 g_param_spec_string ("return-value",
	                                                      "Return value",
	                                                      "Return value",
	                                                      "",
	                                                      G_PARAM_READWRITE));
}

static void
zak_form_gtk_form_element_radio_init (ZakFormGtkFormElementRadio *zak_form_gtk_form_element_radio)
{
	ZakFormGtkFormElementRadioPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_RADIO_GET_PRIVATE (zak_form_gtk_form_element_radio);

	priv->return_value = g_strdup ("");
}

/**
 * zak_form_gtk_form_element_radio_new:
 *
 * Returns: the newly created #ZakFormGtkFormElementRadio object.
 */
ZakFormGtkFormElement
*zak_form_gtk_form_element_radio_new ()
{
	ZakFormGtkFormElementRadio *zak_form_gtk_form_element_radio;

	zak_form_gtk_form_element_radio = ZAK_FORM_GTK_FORM_ELEMENT_RADIO (g_object_new (zak_form_gtk_form_element_radio_get_type (), NULL));

	return ZAK_FORM_GTK_FORM_ELEMENT (zak_form_gtk_form_element_radio);
}

/**
 * zak_form_gtk_form_element_radio_xml_parsing:
 * @element:
 * @xmlnode:
 *
 */
gboolean
zak_form_gtk_form_element_radio_xml_parsing (ZakFormElement *element, xmlNodePtr xmlnode)
{
	xmlNode *cur;

	ZAK_FORM_GTK_FORM_ELEMENT_CLASS (zak_form_gtk_form_element_radio_parent_class)->xml_parsing (element, xmlnode);

	cur = xmlnode->children;
	while (cur != NULL)
		{
			if (xmlStrcmp (cur->name, (const xmlChar *)"return-value") == 0)
				{
					zak_form_gtk_form_element_radio_set_return_value (ZAK_FORM_GTK_FORM_ELEMENT_RADIO (element), (gchar *)xmlNodeGetContent (cur));
				}

			cur = cur->next;
		}

	return TRUE;
}

/**
 * zak_form_gtk_form_element_radio_set_return_value:
 * @element:
 * @value:
 *
 */
void
zak_form_gtk_form_element_radio_set_return_value (ZakFormGtkFormElementRadio *element, const gchar *value)
{
	GtkWidget *w;

	ZakFormGtkFormElementRadioPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_RADIO_GET_PRIVATE (element);

	if (priv->return_value != NULL)
		{
			g_free (priv->return_value);
		}
	priv->return_value = g_strdup (value);

	w = zak_form_gtk_form_element_get_widget (ZAK_FORM_GTK_FORM_ELEMENT (element));

	g_object_set_data (G_OBJECT (w), "return-value", (gpointer)priv->return_value);
}

/**
 * zak_form_gtk_form_element_radio_get_return_value:
 * @element:
 *
 */
gchar
*zak_form_gtk_form_element_radio_get_return_value (ZakFormGtkFormElementRadio *element)
{
	ZakFormGtkFormElementRadioPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_RADIO_GET_PRIVATE (element);

	return g_strdup (priv->return_value);
}

/* PRIVATE */
static void
zak_form_gtk_form_element_radio_set_property (GObject *object,
                   guint property_id,
                   const GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkFormElementRadio *zak_form_gtk_form_element_radio = (ZakFormGtkFormElementRadio *)object;
	ZakFormGtkFormElementRadioPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_RADIO_GET_PRIVATE (zak_form_gtk_form_element_radio);

	switch (property_id)
		{
		case PROP_RETURN_VALUE:
			zak_form_gtk_form_element_radio_set_return_value (zak_form_gtk_form_element_radio, g_value_get_string (value));
			break;

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
		}
}

static void
zak_form_gtk_form_element_radio_get_property (GObject *object,
                   guint property_id,
                   GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkFormElementRadio *zak_form_gtk_form_element_radio = (ZakFormGtkFormElementRadio *)object;
	ZakFormGtkFormElementRadioPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_RADIO_GET_PRIVATE (zak_form_gtk_form_element_radio);

	switch (property_id)
		{
		case PROP_RETURN_VALUE:
			g_value_set_string (value, zak_form_gtk_form_element_radio_get_return_value (zak_form_gtk_form_element_radio));
			break;

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
		}
}

static void
zak_form_gtk_form_element_radio_dispose (GObject *gobject)
{
	ZakFormGtkFormElementRadio *zak_form_gtk_form_element_radio = (ZakFormGtkFormElementRadio *)gobject;
	ZakFormGtkFormElementRadioPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_RADIO_GET_PRIVATE (zak_form_gtk_form_element_radio);



	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->dispose (gobject);
}

static void
zak_form_gtk_form_element_radio_finalize (GObject *gobject)
{
	ZakFormGtkFormElementRadio *zak_form_gtk_form_element_radio = (ZakFormGtkFormElementRadio *)gobject;
	ZakFormGtkFormElementRadioPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_RADIO_GET_PRIVATE (zak_form_gtk_form_element_radio);



	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->finalize (gobject);
}

static GValue
*zak_form_gtk_form_element_radio_get_value (ZakFormGtkFormElementRadio *element)
{
	GValue *ret;

	GtkWidget *w;

	GSList *group;

	w = zak_form_gtk_form_element_get_widget (ZAK_FORM_GTK_FORM_ELEMENT (element));

	ret = zak_utils_gvalue_new_string ("");
	group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (w));
	while (group != NULL)
		{
			if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (group->data)))
				{
					if ((gchar *)g_object_get_data (G_OBJECT (group->data), "return-value") == NULL)
						{
							g_value_set_string (ret, (gchar *)g_object_get_data (G_OBJECT (group->data), "return-value"));
						}
					else
						{
							g_value_set_string (ret, "");
						}
					break;
				}

			group = g_slist_next (group);
		}

	return ret;
}

static gboolean
zak_form_gtk_form_element_radio_set_value (ZakFormGtkFormElementRadio *element, GValue *value)
{
	GtkWidget *w;

	GSList *group;

	w = zak_form_gtk_form_element_get_widget (ZAK_FORM_GTK_FORM_ELEMENT (element));

	group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (w));
	while (group != NULL)
		{
			if (g_strcmp0 ((gchar *)g_object_get_data (G_OBJECT (group->data), "return-value"), g_value_get_string (value)) == 0)
				{
					gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (group->data), TRUE);
					break;
				}

			group = g_slist_next (group);
		}

	return TRUE;
}
