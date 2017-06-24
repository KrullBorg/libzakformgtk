/*
 * Copyright (C) 2016-2017 Andrea Zagli <azagli@libero.it>
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

#include "formelementcombo.h"

enum
{
	PROP_0,
	PROP_COLUMN_FIELD
};

static void zak_form_gtk_form_element_combo_class_init (ZakFormGtkFormElementComboClass *class);
static void zak_form_gtk_form_element_combo_init (ZakFormGtkFormElementCombo *zak_form_gtk_form_element_combo);

static void zak_form_gtk_form_element_combo_set_property (GObject *object,
                                                          guint property_id,
                                                          const GValue *value,
                                                          GParamSpec *pspec);
static void zak_form_gtk_form_element_combo_get_property (GObject *object,
                                                          guint property_id,
                                                          GValue *value,
                                                          GParamSpec *pspec);

static void zak_form_gtk_form_element_combo_dispose (GObject *gobject);
static void zak_form_gtk_form_element_combo_finalize (GObject *gobject);

static GValue *zak_form_gtk_form_element_combo_get_value (ZakFormGtkFormElementCombo *element);
static gboolean zak_form_gtk_form_element_combo_set_value (ZakFormGtkFormElementCombo *element, GValue *value);

#define ZAK_FORM_GTK_FORM_ELEMENT_COMBO_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), ZAK_FORM_GTK_TYPE_FORM_ELEMENT_COMBO, ZakFormGtkFormElementComboPrivate))

typedef struct _ZakFormGtkFormElementComboPrivate ZakFormGtkFormElementComboPrivate;
struct _ZakFormGtkFormElementComboPrivate
	{
		guint column_field;
	};

G_DEFINE_TYPE (ZakFormGtkFormElementCombo, zak_form_gtk_form_element_combo, ZAK_FORM_GTK_TYPE_FORM_ELEMENT)

static void
zak_form_gtk_form_element_combo_class_init (ZakFormGtkFormElementComboClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	ZakFormElementClass *elem_class = ZAK_FORM_ELEMENT_CLASS (klass);

	object_class->set_property = zak_form_gtk_form_element_combo_set_property;
	object_class->get_property = zak_form_gtk_form_element_combo_get_property;
	object_class->dispose = zak_form_gtk_form_element_combo_dispose;
	object_class->finalize = zak_form_gtk_form_element_combo_finalize;

	elem_class->get_value = zak_form_gtk_form_element_combo_get_value;
	elem_class->set_value = zak_form_gtk_form_element_combo_set_value;

	elem_class->xml_parsing = zak_form_gtk_form_element_combo_xml_parsing;

	g_type_class_add_private (object_class, sizeof (ZakFormGtkFormElementComboPrivate));

	g_object_class_install_property (object_class, PROP_COLUMN_FIELD,
	                                 g_param_spec_int ("column-field",
	                                                   "Column Field",
	                                                   "Column's Field",
	                                                   G_MININT,
	                                                   G_MAXINT,
	                                                   0,
	                                                   G_PARAM_READWRITE));
}

static void
zak_form_gtk_form_element_combo_init (ZakFormGtkFormElementCombo *zak_form_gtk_form_element_combo)
{
	ZakFormGtkFormElementComboPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_COMBO_GET_PRIVATE (zak_form_gtk_form_element_combo);

	priv->column_field = 0;
}

/**
 * zak_form_gtk_form_element_combo_new:
 *
 * Returns: the newly created #ZakFormGtkFormElementCombo object.
 */
ZakFormGtkFormElement
*zak_form_gtk_form_element_combo_new ()
{
	ZakFormGtkFormElementCombo *zak_form_gtk_form_element_combo;

	zak_form_gtk_form_element_combo = ZAK_FORM_GTK_FORM_ELEMENT_COMBO (g_object_new (zak_form_gtk_form_element_combo_get_type (), NULL));

	return ZAK_FORM_GTK_FORM_ELEMENT (zak_form_gtk_form_element_combo);
}

/**
 * zak_form_gtk_form_element_combo_xml_parsing:
 * @element:
 * @xmlnode:
 *
 */
void
zak_form_gtk_form_element_combo_xml_parsing (ZakFormElement *element, xmlNodePtr xmlnode)
{
	xmlNode *cur;

	ZAK_FORM_GTK_FORM_ELEMENT_CLASS (zak_form_gtk_form_element_combo_parent_class)->xml_parsing (element, xmlnode);

	cur = xmlnode->children;
	while (cur != NULL)
		{
			if (xmlStrcmp (cur->name, (const xmlChar *)"column-field") == 0)
				{
					zak_form_gtk_form_element_combo_set_column_field (ZAK_FORM_GTK_FORM_ELEMENT_COMBO (element), strtol ((gchar *)xmlNodeGetContent (cur), NULL, 10));
				}

			cur = cur->next;
		}
}

/**
 * zak_form_gtk_form_element_combo_set_column_field:
 * @element:
 * @column_field:
 *
 */
void
zak_form_gtk_form_element_combo_set_column_field (ZakFormGtkFormElementCombo *element, guint column_field)
{
	ZakFormGtkFormElementComboPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_COMBO_GET_PRIVATE (element);

	priv->column_field = column_field;
}

/**
 * zak_form_gtk_form_element_combo_get_column_field:
 * @element:
 *
 */
guint
zak_form_gtk_form_element_combo_get_column_field (ZakFormGtkFormElementCombo *element)
{
	ZakFormGtkFormElementComboPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_COMBO_GET_PRIVATE (element);

	return priv->column_field;
}

/* PRIVATE */
static void
zak_form_gtk_form_element_combo_set_property (GObject *object,
                   guint property_id,
                   const GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkFormElementCombo *zak_form_gtk_form_element_combo = (ZakFormGtkFormElementCombo *)object;
	ZakFormGtkFormElementComboPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_COMBO_GET_PRIVATE (zak_form_gtk_form_element_combo);

	switch (property_id)
		{
		case PROP_COLUMN_FIELD:
			zak_form_gtk_form_element_combo_set_column_field (zak_form_gtk_form_element_combo, g_value_get_uint (value));
			break;

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
		}
}

static void
zak_form_gtk_form_element_combo_get_property (GObject *object,
                   guint property_id,
                   GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkFormElementCombo *zak_form_gtk_form_element_combo = (ZakFormGtkFormElementCombo *)object;
	ZakFormGtkFormElementComboPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_COMBO_GET_PRIVATE (zak_form_gtk_form_element_combo);

	switch (property_id)
		{
		case PROP_COLUMN_FIELD:
			g_value_set_uint (value, zak_form_gtk_form_element_combo_get_column_field (zak_form_gtk_form_element_combo));
			break;

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
		}
}

static void
zak_form_gtk_form_element_combo_dispose (GObject *gobject)
{
	ZakFormGtkFormElementCombo *zak_form_gtk_form_element_combo = (ZakFormGtkFormElementCombo *)gobject;
	ZakFormGtkFormElementComboPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_COMBO_GET_PRIVATE (zak_form_gtk_form_element_combo);



	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->dispose (gobject);
}

static void
zak_form_gtk_form_element_combo_finalize (GObject *gobject)
{
	ZakFormGtkFormElementCombo *zak_form_gtk_form_element_combo = (ZakFormGtkFormElementCombo *)gobject;
	ZakFormGtkFormElementComboPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_COMBO_GET_PRIVATE (zak_form_gtk_form_element_combo);



	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->finalize (gobject);
}

static GValue
*zak_form_gtk_form_element_combo_get_value (ZakFormGtkFormElementCombo *element)
{
	GValue *ret;

	GtkWidget *w;
	GtkTreeModel *tmodel;

	GtkTreeIter iter;

	GValue *gvalue;
	GValue *gvstr;

	ZakFormGtkFormElementComboPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_COMBO_GET_PRIVATE (element);

	w = zak_form_gtk_form_element_get_widget (ZAK_FORM_GTK_FORM_ELEMENT (element));

	ret = zak_utils_gvalue_new_string ("");

	tmodel = gtk_combo_box_get_model (GTK_COMBO_BOX (w));
	if (tmodel != NULL)
		{
			if (gtk_combo_box_get_active_iter (GTK_COMBO_BOX (w), &iter))
				{
					gvalue = g_new0 (GValue, 1);
					gvstr = g_new0 (GValue, 1);

					gtk_tree_model_get_value (tmodel, &iter, priv->column_field, gvalue);

					g_value_init (gvstr, G_TYPE_STRING);
					g_value_transform (gvalue, gvstr);

					g_free (ret);
					g_value_set_string (ret, g_strdup (g_value_get_string (gvstr)));

					g_value_unset (gvstr);
					g_value_unset (gvalue);
				}
		}

	return ret;
}

static gboolean
zak_form_gtk_form_element_combo_set_value (ZakFormGtkFormElementCombo *element, GValue *value)
{
	GtkWidget *w;

	GtkTreeModel *tmodel;
	GtkTreeIter iter;

	GValue *gvalue;
	GValue *gvstr;

	ZakFormGtkFormElementComboPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_COMBO_GET_PRIVATE (element);

	w = zak_form_gtk_form_element_get_widget (ZAK_FORM_GTK_FORM_ELEMENT (element));

	gtk_combo_box_set_active (GTK_COMBO_BOX (w), -1);

	tmodel = gtk_combo_box_get_model (GTK_COMBO_BOX (w));
	if (tmodel != NULL)
		{
			if (gtk_tree_model_get_iter_first (tmodel, &iter))
				{
					do
						{
							gvalue = g_new0 (GValue, 1);
							gvstr = g_new0 (GValue, 1);

							gtk_tree_model_get_value (tmodel, &iter, priv->column_field, gvalue);

							g_value_init (gvstr, G_TYPE_STRING);
							g_value_transform (gvalue, gvstr);
							if (g_strcmp0 (g_value_get_string (gvstr), g_value_get_string (value)) == 0)
								{
									gtk_combo_box_set_active_iter (GTK_COMBO_BOX (w), &iter);

									g_value_unset (gvstr);
									g_value_unset (gvalue);

									break;
								}

							g_value_unset (gvstr);
							g_value_unset (gvalue);
						} while (gtk_tree_model_iter_next (tmodel, &iter));
				}
		}

	return TRUE;
}
