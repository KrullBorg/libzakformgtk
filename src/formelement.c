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

#include "formelement.h"

enum
{
	PROP_0,
	PROP_GTKBUILDER,
	PROP_WIDGET,
	PROP_NAME,
	PROP_LABEL
};

static void zak_form_gtk_form_element_class_init (ZakFormGtkFormElementClass *class);
static void zak_form_gtk_form_element_init (ZakFormGtkFormElement *zak_form_gtk_form_element);

static void zak_form_gtk_form_element_set_property (GObject *object,
                               guint property_id,
                               const GValue *value,
                               GParamSpec *pspec);
static void zak_form_gtk_form_element_get_property (GObject *object,
                               guint property_id,
                               GValue *value,
                               GParamSpec *pspec);

static void zak_form_gtk_form_element_dispose (GObject *gobject);
static void zak_form_gtk_form_element_finalize (GObject *gobject);

static gboolean zak_form_gtk_form_element_get_visible (ZakFormGtkFormElement *element);
static void zak_form_gtk_form_element_set_visible (ZakFormGtkFormElement *element, gboolean visible);

static gboolean zak_form_gtk_form_element_get_editable (ZakFormGtkFormElement *element);
static void zak_form_gtk_form_element_set_editable (ZakFormGtkFormElement *element, gboolean visible);

static void zak_form_gtk_form_element_xml_parsing (ZakFormElement *element, xmlNode *xmlnode);

#define ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), ZAK_FORM_GTK_TYPE_FORM_ELEMENT, ZakFormGtkFormElementPrivate))

typedef struct _ZakFormGtkFormElementPrivate ZakFormGtkFormElementPrivate;
struct _ZakFormGtkFormElementPrivate
	{
		GtkBuilder *builder;
		GtkWidget *widget;
		gchar *name;

		GtkWidget *label;
	};

G_DEFINE_ABSTRACT_TYPE (ZakFormGtkFormElement, zak_form_gtk_form_element, ZAK_FORM_TYPE_ELEMENT)

static void
zak_form_gtk_form_element_class_init (ZakFormGtkFormElementClass *class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (class);
	ZakFormElementClass *parent_class = ZAK_FORM_ELEMENT_CLASS (class);

	object_class->set_property = zak_form_gtk_form_element_set_property;
	object_class->get_property = zak_form_gtk_form_element_get_property;
	object_class->dispose = zak_form_gtk_form_element_dispose;
	object_class->finalize = zak_form_gtk_form_element_finalize;

	class->xml_parsing = zak_form_gtk_form_element_xml_parsing;

	parent_class->get_visible = zak_form_gtk_form_element_get_visible;
	parent_class->set_visible = zak_form_gtk_form_element_set_visible;
	parent_class->get_editable = zak_form_gtk_form_element_get_editable;
	parent_class->set_editable = zak_form_gtk_form_element_set_editable;

	g_type_class_add_private (object_class, sizeof (ZakFormGtkFormElementPrivate));

	g_object_class_install_property (object_class, PROP_GTKBUILDER,
									 g_param_spec_object ("gtkbuilder",
														  "GtkBuilder",
														  "GtkBuilder",
														  G_TYPE_OBJECT,
														  G_PARAM_READWRITE));

	g_object_class_install_property (object_class, PROP_WIDGET,
									 g_param_spec_object ("widget",
														  "Widget",
														  "Widget",
														  GTK_TYPE_WIDGET,
														  G_PARAM_READABLE));

	g_object_class_install_property (object_class, PROP_NAME,
	                                 g_param_spec_string ("name",
	                                                      "Name",
	                                                      "Name",
	                                                      NULL,
	                                                      G_PARAM_READABLE));

	g_object_class_install_property (object_class, PROP_LABEL,
									 g_param_spec_object ("label",
														  "Label",
														  "Label",
														  GTK_TYPE_WIDGET,
														  G_PARAM_READWRITE));
}

static void
zak_form_gtk_form_element_init (ZakFormGtkFormElement *zak_form_gtk_form_element)
{
	ZakFormGtkFormElementPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE (zak_form_gtk_form_element);

	priv->builder = NULL;
	priv->widget = NULL;
	priv->name = NULL;
	priv->label = NULL;
}

/**
 * zak_form_gtk_form_element_set_gtkbuilder:
 * @element:
 * @gtkbuilder:
 *
 */
void
zak_form_gtk_form_element_set_gtkbuilder (ZakFormGtkFormElement *element, GtkBuilder *gtkbuilder)
{
	ZakFormGtkFormElementPrivate *priv;

	priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE (element);

	priv->builder = gtkbuilder;
}

/**
 * zak_form_gtk_form_element_get_gtkbuilder:
 * @element:
 *
 */
GtkBuilder
*zak_form_gtk_form_element_get_gtkbuilder (ZakFormGtkFormElement *element)
{
	ZakFormGtkFormElementPrivate *priv;

	priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE (element);

	return priv->builder;
}

/**
 * zak_form_gtk_form_element_set_widget_from_gtkbuilder:
 * @element:
 * @gtkbuilder:
 * @widget_name:
 *
 */
gboolean
zak_form_gtk_form_element_set_widget_from_gtkbuilder (ZakFormGtkFormElement *element,
													  GtkBuilder *gtkbuilder,
													  const gchar *widget_name)
{
	ZakFormGtkFormElementPrivate *priv;

	gboolean ret;
	GtkWidget *w;

	g_return_val_if_fail (GTK_IS_BUILDER (gtkbuilder), FALSE);
	g_return_val_if_fail (widget_name != NULL, FALSE);
	g_return_val_if_fail (g_strcmp0 (widget_name, "") != 0, FALSE);

	priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE (element);

	priv->builder = gtkbuilder;

	ret = FALSE;
	w = GTK_WIDGET (gtk_builder_get_object (gtkbuilder, widget_name));
	if (w != NULL
		&& GTK_IS_WIDGET (w))
		{
			zak_form_gtk_form_element_set_widget (element, w, widget_name);
			ret = TRUE;
		}
	else
		{
			g_warning (_("Widget «%s» not found."), widget_name);
		}

	return TRUE;
}

/**
 * zak_form_gtk_form_element_get_widget:
 * @element:
 *
 */
GtkWidget
*zak_form_gtk_form_element_get_widget (ZakFormGtkFormElement *element)
{
	ZakFormGtkFormElementPrivate *priv;

	priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE (element);

	return priv->widget;
}

/**
 * zak_form_get_form_element_set_widget:
 * @element:
 * @widget:
 * @widget_name:
 *
 */
void
zak_form_gtk_form_element_set_widget (ZakFormGtkFormElement *element, GtkWidget *widget, const gchar *widget_name)
{
	ZakFormGtkFormElementPrivate *priv;

	g_return_if_fail (GTK_IS_WIDGET (widget));
	g_return_if_fail (widget_name != NULL);
	g_return_if_fail (g_strcmp0 (widget_name, "") != 0);

	priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE (element);

	priv->widget = g_object_ref (widget);
	priv->name = g_strdup (widget_name);
}

/**
 * zak_form_gtk_form_element_get_widget_name:
 * @element:
 *
 */
gchar
*zak_form_gtk_form_element_get_widget_name (ZakFormGtkFormElement *element)
{
	ZakFormGtkFormElementPrivate *priv;

	priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE (element);

	return g_strdup (priv->name);
}

/**
 * zak_form_gtk_form_element_get_label:
 * @element:
 *
 */
GtkWidget
*zak_form_gtk_form_element_get_label (ZakFormGtkFormElement *element)
{
	ZakFormGtkFormElementPrivate *priv;

	priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE (element);

	return priv->label;
}

/**
 * zak_form_gtk_form_element_set_label:
 * @element:
 * @label:
 *
 */
void
zak_form_gtk_form_element_set_label (ZakFormGtkFormElement *element, GtkWidget *label)
{
	ZakFormGtkFormElementPrivate *priv;

	priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE (element);

	if (priv->label != NULL)
		{
			g_object_unref (priv->label);
		}
	priv->label = g_object_ref (label);

	zak_form_element_set_long_name (ZAK_FORM_ELEMENT (element),
									gtk_label_get_text (GTK_LABEL (priv->label)));
}

/* PRIVATE */
static void
zak_form_gtk_form_element_set_property (GObject *object,
                   guint property_id,
                   const GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkFormElement *zak_form_gtk_form_element = (ZakFormGtkFormElement *)object;
	ZakFormGtkFormElementPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE (zak_form_gtk_form_element);

	switch (property_id)
		{
		case PROP_GTKBUILDER:
			zak_form_gtk_form_element_set_gtkbuilder (zak_form_gtk_form_element, (GtkBuilder *)g_value_get_object (value));
			break;

		case PROP_LABEL:
			zak_form_gtk_form_element_set_label (zak_form_gtk_form_element, (GtkWidget *)g_value_get_object (value));
			break;

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
		}
}

static void
zak_form_gtk_form_element_get_property (GObject *object,
                   guint property_id,
                   GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkFormElement *zak_form_gtk_form_element = (ZakFormGtkFormElement *)object;
	ZakFormGtkFormElementPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE (zak_form_gtk_form_element);

	switch (property_id)
		{
		case PROP_GTKBUILDER:
			g_value_set_object (value, (gpointer)zak_form_gtk_form_element_get_gtkbuilder (zak_form_gtk_form_element));
			break;

		case PROP_LABEL:
			g_value_set_object (value, (gpointer)zak_form_gtk_form_element_get_label (zak_form_gtk_form_element));
			break;

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
		}
}

static void
zak_form_gtk_form_element_dispose (GObject *gobject)
{
	ZakFormGtkFormElement *zak_form_gtk_form_element = (ZakFormGtkFormElement *)gobject;
	ZakFormGtkFormElementPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE (zak_form_gtk_form_element);



	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->dispose (gobject);
}

static void
zak_form_gtk_form_element_finalize (GObject *gobject)
{
	ZakFormGtkFormElement *zak_form_gtk_form_element = (ZakFormGtkFormElement *)gobject;
	ZakFormGtkFormElementPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE (zak_form_gtk_form_element);



	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->finalize (gobject);
}

static gboolean
zak_form_gtk_form_element_get_visible (ZakFormGtkFormElement *element)
{
	ZakFormGtkFormElementPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE (element);

	return gtk_widget_get_visible (priv->widget);
}

static void
zak_form_gtk_form_element_set_visible (ZakFormGtkFormElement *element, gboolean visible)
{
	ZakFormGtkFormElementPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE (element);

	gtk_widget_set_visible (priv->widget, visible);

	if (GTK_IS_WIDGET (priv->label))
		{
			gtk_widget_set_visible (priv->label, visible);
		}
}

static gboolean
zak_form_gtk_form_element_get_editable (ZakFormGtkFormElement *element)
{
	ZakFormGtkFormElementPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE (element);

	return gtk_widget_get_sensitive (priv->widget);
}

static void
zak_form_gtk_form_element_set_editable (ZakFormGtkFormElement *element, gboolean editable)
{
	ZakFormGtkFormElementPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE (element);

	gtk_widget_set_sensitive (priv->widget, editable);
}

static void
zak_form_gtk_form_element_xml_parsing (ZakFormElement *element, xmlNode *xmlnode)
{
	xmlNode *cur;

	ZakFormGtkFormElementPrivate *priv = ZAK_FORM_GTK_FORM_ELEMENT_GET_PRIVATE ((ZakFormGtkFormElement *)element);

	ZAK_FORM_ELEMENT_GET_CLASS (element)->xml_parsing (element, xmlnode);

	cur = xmlnode->children;
	while (cur != NULL)
		{
			if (xmlStrcmp (cur->name, (const xmlChar *)"widget") == 0)
				{
					zak_form_gtk_form_element_set_widget_from_gtkbuilder (ZAK_FORM_GTK_FORM_ELEMENT (element), priv->builder, (gchar *)xmlNodeGetContent (cur));
				}
			else if (xmlStrcmp (cur->name, (const xmlChar *)"label") == 0)
				{
					zak_form_gtk_form_element_set_label (ZAK_FORM_GTK_FORM_ELEMENT (element),
														 GTK_WIDGET (gtk_builder_get_object (priv->builder, (gchar *)xmlNodeGetContent (cur))));
				}

			cur = cur->next;
		}
}
