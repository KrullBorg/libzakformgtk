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

#include <syslog.h>

#include "form.h"

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

#define ZAK_FORM_GTK_FORM_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), ZAK_FORM_GTK_TYPE_FORM, ZakFormGtkFormPrivate))

typedef struct _ZakFormGtkFormPrivate ZakFormGtkFormPrivate;
struct _ZakFormGtkFormPrivate
	{
		gpointer nothing;
	};

G_DEFINE_TYPE (ZakFormGtkForm, zak_form_gtk_form, ZAK_FORM_TYPE_FORM)

static void
zak_form_gtk_form_class_init (ZakFormGtkFormClass *class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (class);

	object_class->set_property = zak_form_gtk_form_set_property;
	object_class->get_property = zak_form_gtk_form_get_property;
	object_class->dispose = zak_form_gtk_form_dispose;
	object_class->finalize = zak_form_gtk_form_finalize;

	g_type_class_add_private (object_class, sizeof (ZakFormGtkFormPrivate));
}

static void
zak_form_gtk_form_init (ZakFormGtkForm *zak_form_gtk_form)
{
	ZakFormGtkFormPrivate *priv = ZAK_FORM_GTK_FORM_GET_PRIVATE (zak_form_gtk_form);
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
