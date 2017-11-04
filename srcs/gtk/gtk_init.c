/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:08:46 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/04 19:08:46 by bbeldame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

gboolean	hook(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
	(void)widget;
	(void)user_data;
	if (event->keyval == 65307)
		exit(42);
	return (FALSE);
}

void		exit_gtk(void)
{
	gtk_main_quit();
}

void		ft_gtk_start_launcher(t_rt *e)
{
	gtk_init(NULL, NULL);
	e->gtk.menu.window = new_window(300, 200, "RT");
	e->gtk.menu.layout = gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(e->gtk.menu.window), e->gtk.menu.layout);
	g_signal_connect(G_OBJECT(e->gtk.menu.window), "delete-event",
	G_CALLBACK(exit_gtk), NULL);
	ft_gtk_launcher(e);
	gtk_widget_show_all(e->gtk.menu.window);
	g_signal_connect(G_OBJECT(e->gtk.menu.window),
								"key_press_event", G_CALLBACK(hook), NULL);
	gtk_main();
}
