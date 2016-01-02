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

#include "form.h"
#include "formelement.h"

static void zak_form_gtk_form_class_init (ZakFormGtkFormClass *class);
static void zak_form_gtk_form_init (ZakFormGtkForm *zak_form_gtk_form);

static void zak_form_gtk_form_set_property (GObject *object,
                               guint property_id,
                               const GValue *value,
                               GParamSpec *pspec);
static void zak_form_gtk_form_get_property (GObject *object,
                               guint property_id,
                               GValue *value,
                               GParamSpec *pspec);

static void zak_form_gtk_form_dispose (GObject *gobject);
static void zak_form_gtk_form_finalize (GObject *gobject);

static void zak_form_gtk_form_element_added (ZakFormGtkForm *form, ZakFormGtkFormElement *element);

#define ZAK_FORM_GTK_FORM_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), ZAK_FORM_GTK_TYPE_FORM, ZakFormGtkFormPrivate))

typedef struct _ZakFormGtkFormPrivate ZakFormGtkFormPrivate;
struct _ZakFormGtkFormPrivate
	{
		GPtrArray *ar_elements;
		GtkBuilder *builder;;
	};

G_DEFINE_TYPE (ZakFormGtkForm, zak_form_gtk_form, ZAK_FORM_TYPE_FORM)

static void
zak_form_gtk_form_class_init (ZakFormGtkFormClass *class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (class);
	ZakFormFormClass *parent_class = ZAK_FORM_FORM_CLASS (class);

	object_class->set_property = zak_form_gtk_form_set_property;
	object_class->get_property = zak_form_gtk_form_get_property;
	object_class->dispose = zak_form_gtk_form_dispose;
	object_class->finalize = zak_form_gtk_form_finalize;

	parent_class->element_added = zak_form_gtk_form_element_added;

	g_type_class_add_private (object_class, sizeof (ZakFormGtkFormPrivate));
}

static void
zak_form_gtk_form_init (ZakFormGtkForm *zak_form_gtk_form)
{
	ZakFormGtkFormPrivate *priv = ZAK_FORM_GTK_FORM_GET_PRIVATE (zak_form_gtk_form);

	priv->ar_elements = ZAK_FORM_FORM_CLASS (zak_form_gtk_form_parent_class)->get_elements (ZAK_FORM_FORM (zak_form_gtk_form));
	priv->builder = NULL;
}

/**
 * zak_form_gtk_form_new:
 *
 * Returns: the newly created #ZakFormGtkForm object.
 */
ZakFormGtkForm
*zak_form_gtk_form_new ()
{
	ZakFormGtkForm *zak_form_gtk_form;
	ZakFormGtkFormPrivate *priv;

	zak_form_gtk_form = ZAK_FORM_GTK_FORM (g_object_new (zak_form_gtk_form_get_type (), NULL));

	priv = ZAK_FORM_GTK_FORM_GET_PRIVATE (zak_form_gtk_form);

	return zak_form_gtk_form;
}

/**
 * zak_form_gtk_form_set_gtkbuilder:
 * @form:
 * @builder:
 *
 */
void
zak_form_gtk_form_set_gtkbuilder (ZakFormGtkForm *form, GtkBuilder *builder)
{
	ZakFormGtkFormPrivate *priv;

	priv = ZAK_FORM_GTK_FORM_GET_PRIVATE (form);

	priv->builder = builder;
}

/**
 * zak_form_gtk_form_is_valid:
 * @form:
 * @parent_window:
 *
 */
gboolean
zak_form_gtk_form_is_valid (ZakFormGtkForm *form, GtkWidget *parent_window)
{
	gboolean ret;

	guint i;
	GString *str;
	guint m;

	GtkWidget *w_to_focus;

	GPtrArray *ar_messages;

	g_return_val_if_fail (parent_window != NULL ? GTK_IS_WINDOW (parent_window) : TRUE, FALSE);

	ZakFormGtkFormPrivate *priv = ZAK_FORM_GTK_FORM_GET_PRIVATE (form);

	ret = zak_form_form_is_valid (ZAK_FORM_FORM (form));

	if (!ret)
		{
			w_to_focus = NULL;
			str = g_string_new ("");

			/* collect error messages */
			for (i = 0; i < priv->ar_elements->len; i++)
				{
					ar_messages = zak_form_element_get_messages ((ZakFormElement *)g_ptr_array_index (priv->ar_elements, i));
					if (ar_messages != NULL)
						{
							if (w_to_focus == NULL)
								{
									w_to_focus = zak_form_gtk_form_element_get_widget (ZAK_FORM_GTK_FORM_ELEMENT ((ZakFormElement *)g_ptr_array_index (priv->ar_elements, i)));
								}

							for (m = 0; m < ar_messages->len; m++)
								{
									g_string_append_printf (str, "\n - %s", (gchar *)g_ptr_array_index (ar_messages, m));
								}
						}
				}

			ar_messages = zak_form_form_get_messages (ZAK_FORM_FORM (form));
			if (ar_messages != NULL)
				{
					for (m = 0; m < ar_messages->len; m++)
						{
							g_string_append_printf (str, "\n - %s", (gchar *)g_ptr_array_index (ar_messages, m));
						}
				}

			if (g_strcmp0 (str->str, "") != 0)
				{
					GtkWidget *dialog;

					dialog = gtk_message_dialog_new (GTK_WINDOW (parent_window),
													 GTK_DIALOG_DESTROY_WITH_PARENT,
													 GTK_MESSAGE_WARNING,
													 GTK_BUTTONS_OK,
													 str->str);
					gtk_dialog_run (GTK_DIALOG (dialog));
					gtk_widget_destroy (dialog);

					if (w_to_focus != NULL)
						{
							gtk_widget_grab_focus (w_to_focus);
						}
				}
		}

	return ret;
}

/* PRIVATE */
static void
zak_form_gtk_form_set_property (GObject *object,
                   guint property_id,
                   const GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkForm *zak_form_gtk_form = (ZakFormGtkForm *)object;
	ZakFormGtkFormPrivate *priv = ZAK_FORM_GTK_FORM_GET_PRIVATE (zak_form_gtk_form);

	switch (property_id)
		{
			default:
				G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
				break;
		}
}

static void
zak_form_gtk_form_get_property (GObject *object,
                   guint property_id,
                   GValue *value,
                   GParamSpec *pspec)
{
	ZakFormGtkForm *zak_form_gtk_form = (ZakFormGtkForm *)object;
	ZakFormGtkFormPrivate *priv = ZAK_FORM_GTK_FORM_GET_PRIVATE (zak_form_gtk_form);

	switch (property_id)
		{
			default:
				G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
				break;
		}
}

static void
zak_form_gtk_form_dispose (GObject *gobject)
{
	ZakFormGtkForm *zak_form_gtk_form = (ZakFormGtkForm *)gobject;
	ZakFormGtkFormPrivate *priv = ZAK_FORM_GTK_FORM_GET_PRIVATE (zak_form_gtk_form);


	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->dispose (gobject);
}

static void
zak_form_gtk_form_finalize (GObject *gobject)
{
	ZakFormGtkForm *zak_form_gtk_form = (ZakFormGtkForm *)gobject;
	ZakFormGtkFormPrivate *priv = ZAK_FORM_GTK_FORM_GET_PRIVATE (zak_form_gtk_form);


	GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (gobject));
	parent_class->finalize (gobject);
}

static void
zak_form_gtk_form_element_added (ZakFormGtkForm *form, ZakFormGtkFormElement *element)
{
	ZakFormGtkFormPrivate *priv = ZAK_FORM_GTK_FORM_GET_PRIVATE (form);

	zak_form_gtk_form_element_set_gtkbuilder (element, priv->builder);
}
