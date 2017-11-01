#include "../includes/rt.h"

GtkWidget	*new_btn(int x, int y, char *name)
{
	GtkWidget *btn;

	printf("%s\n", "New Btn");
	btn = gtk_button_new_with_label(name);
	gtk_widget_set_size_request(btn, x, y);
	return (btn);
}

GtkWidget	*new_txt(gchar *str)
{
	GtkWidget *txt;

	printf("%s\n", "New txt");
	txt = gtk_label_new(str);
	return (txt);
}

GtkWidget	*new_input(t_gtk_input *data)
{
	GtkWidget *input;

	printf("%s\n", "New Input");
	input = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(input), data->max_size);
	gtk_entry_set_width_chars(GTK_ENTRY(input), data->max_char);
	gtk_entry_set_placeholder_text(GTK_ENTRY(input), data->placeholder);
	gtk_entry_set_text(GTK_ENTRY(input), data->deflaut_value);
	return (input);
}

GtkWidget	*new_window(gint w, gint h, gchar *name)
{
	GtkWidget *win;

	printf("%s\n", "New Window");
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(win), w, h);
	gtk_window_set_resizable(GTK_WINDOW(win), FALSE);
	gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(win), name);
	return (win);
}
