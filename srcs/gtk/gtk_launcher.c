#include "../includes/rt.h"

void		btn_settings_clicked(GtkWidget *btn, t_rt *e)
{
	(void)btn;
	e->gtk.settings.window = new_window(200, 300, "Settings");
	e->gtk.settings.layout = gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(e->gtk.settings.window),
									e->gtk.settings.layout);
	ft_init_values(e);
	ft_settings(e);
	gtk_widget_show_all(e->gtk.settings.window);
	g_signal_connect(G_OBJECT(e->gtk.settings.window),
								"key_press_event", G_CALLBACK(hook), NULL);
	gtk_widget_set_sensitive(GTK_WIDGET(e->gtk.menu.window), 0);
}

void		btn_settings(t_rt *e)
{
	GtkWidget	*btn;

	btn = new_btn(200, 40, "Settings");
	gtk_layout_put(GTK_LAYOUT(e->gtk.menu.layout), btn, 50, 50);
	g_signal_connect(btn, "clicked", G_CALLBACK(btn_settings_clicked), e);
}

void		open_scene_clicked(GtkWidget *btn, t_rt *e)
{
	GtkWidget	*dialog;
	GtkWidget	*win;
	gint		res;

	(void)btn;
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	dialog = gtk_file_chooser_dialog_new(
				"Open File", GTK_WINDOW(win), GTK_FILE_CHOOSER_ACTION_OPEN,
				"Cancel", GTK_RESPONSE_CANCEL,
				"Open", GTK_RESPONSE_ACCEPT, NULL);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		SFILE = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		gtk_widget_destroy(dialog);
		/*if (parse_doc(e))
		{
			gtk_widget_destroy(e->gtk.menu.window);
			ft_start_rt(e);
		}*/
		g_free(SFILE);
	}
	else
		gtk_widget_destroy(dialog);
}

void		open_scene(t_rt *e)
{
	GtkWidget	*btn;

	btn = new_btn(200, 40, "Open scene");
	gtk_layout_put(GTK_LAYOUT(e->gtk.menu.layout), btn, 50, 110);
	g_signal_connect(btn, "clicked", G_CALLBACK(open_scene_clicked), e);
}

void		ft_gtk_launcher(t_rt *e)
{
	btn_settings(e);
	open_scene(e);
}
