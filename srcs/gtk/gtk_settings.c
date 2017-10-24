#include "../includes/rt.h"

gboolean	close_settings2(GtkWidget *wid, GdkEvent *ev, t_rt *e)
{
	(void)wid;
	(void)ev;
	gtk_widget_destroy(e->gtk.settings.window);
	if (e->gtk.started == 1)
		ft_start_rt(e);
	gtk_widget_set_sensitive(GTK_WIDGET(e->gtk.menu.window), 1);
	return (TRUE);
}

void		ft_update(GtkButton *btn, t_rt *e)
{
	(void)btn;
	gtk_widget_destroy(e->gtk.settings.window);
	LARGEUR = e->gtk.values.width > 2560 ? 2560 : e->gtk.values.width;
	HAUTEUR = e->gtk.values.height > 1440 ? 1440 : e->gtk.values.height;
	if (e->gtk.values.res != RES)
	{
		RES = e->gtk.values.res > 200 ? 199 : e->gtk.values.res;
		RES_BUFF = RES;
	}
	//else
		//RES = calcul_res(e, 400000);
	CCAM.ratio_x = (LARGEUR > HAUTEUR) ?
		(float)LARGEUR / (float)HAUTEUR : 1;
	CCAM.ratio_y = (HAUTEUR > LARGEUR) ?
		(float)HAUTEUR / (float)LARGEUR : 1;
	if (e->gtk.started == 1)
		ft_start_rt(e);
	else
		gtk_widget_set_sensitive(GTK_WIDGET(e->gtk.menu.window), 1);
}

void		ft_btn_update(t_rt *e)
{
	GtkWidget	*btn;

	btn = new_btn(100, 40, "UPDATE");
	gtk_layout_put(GTK_LAYOUT(e->gtk.settings.layout), btn, 50, 250);
	g_signal_connect(btn, "clicked", G_CALLBACK(ft_update), e);
}

void		ft_settings(t_rt *e)
{
	gtk_layout_put(GTK_LAYOUT(e->gtk.settings.layout),
		new_txt("Screen size"), 20, 20);
	gtk_widget_show_all(e->gtk.settings.window);
	ft_add_win_size(e);
	gtk_layout_put(GTK_LAYOUT(e->gtk.settings.layout),
		new_txt("Resolution"), 20, 90);
	gtk_widget_show_all(e->gtk.settings.window);
	ft_add_resolution(e);
	gtk_layout_put(GTK_LAYOUT(e->gtk.settings.layout),
		new_txt("anti-aliasing"), 20, 160);
	gtk_widget_show_all(e->gtk.settings.window);
	ft_add_antialiasing(e);
	ft_btn_update(e);
	g_signal_connect(e->gtk.settings.window,
		"delete-event", G_CALLBACK(close_settings2), e);
}
