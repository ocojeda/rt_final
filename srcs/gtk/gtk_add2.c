#include "../includes/rt.h"

void	ft_add_win_size(t_rt *e)
{
	t_gtk_input	input;
	GtkWidget	*width;
	GtkWidget	*height;

	input.max_char = 5;
	input.max_size = 5;
	input.placeholder = "width";
	input.deflaut_value = ft_itoa(LARGEUR);
	width = new_input(&input);
	input.placeholder = "height";
	input.deflaut_value = ft_itoa(HAUTEUR);
	height = new_input(&input);
	gtk_layout_put(GTK_LAYOUT(e->gtk.settings.layout), width, 20, 40);
	gtk_layout_put(GTK_LAYOUT(e->gtk.settings.layout), height, 80, 40);
	g_signal_connect(width, "activate", G_CALLBACK(ft_add_w), e);
	g_signal_connect(height, "activate", G_CALLBACK(ft_add_h), e);
}

void	ft_add_resolution(t_rt *e)
{
	t_gtk_input	input;
	GtkWidget	*res;

	input.max_char = 3;
	input.max_size = 3;
	input.placeholder = "RES";
	input.deflaut_value = ft_itoa(RES);
	res = new_input(&input);
	gtk_layout_put(GTK_LAYOUT(e->gtk.settings.layout), res, 20, 110);
	g_signal_connect(res, "activate", G_CALLBACK(ft_add_res), e);
}

void	ft_add_antialiasing(t_rt *e)
{
	GtkWidget *sw;

	sw = gtk_switch_new();
	if (ALIASING == 1)
		gtk_switch_set_active(GTK_SWITCH(sw), FALSE);
	else
		gtk_switch_set_active(GTK_SWITCH(sw), TRUE);
	g_signal_connect(GTK_SWITCH(sw),
		"notify::active", G_CALLBACK(ft_add_anti), e);
	gtk_layout_put(GTK_LAYOUT(e->gtk.settings.layout), sw, 20, 180);
	gtk_widget_show_all(e->gtk.settings.window);
}

void	ft_add_filter(t_rt *e)
{
	t_gtk_input	input;
	GtkWidget	*filt;

	input.max_char = 3;
	input.max_size = 3;
	input.placeholder = "FILT";
	input.deflaut_value = ft_itoa(FILT);
	filt = new_input(&input);
	gtk_layout_put(GTK_LAYOUT(e->gtk.settings.layout), filt, 20, 250);
	g_signal_connect(filt, "activate", G_CALLBACK(ft_add_filt), e);
}