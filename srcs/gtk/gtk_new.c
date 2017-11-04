/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:08:40 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 19:08:41 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

GtkWidget	*new_btn(int x, int y, char *name)
{
	GtkWidget *btn;

	btn = gtk_button_new_with_label(name);
	gtk_widget_set_size_request(btn, x, y);
	return (btn);
}

GtkWidget	*new_window(gint w, gint h, gchar *name)
{
	GtkWidget *win;

	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(win), w, h);
	gtk_window_set_resizable(GTK_WINDOW(win), FALSE);
	gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(win), name);
	return (win);
}
