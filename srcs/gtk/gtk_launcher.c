#include "../includes/rt.h"

int					do_checks(xmlDocPtr doc)
{
	xmlValidCtxtPtr	vctxt;
	int				xsd;

	if (!(vctxt = xmlNewValidCtxt()))
		return (0);
	xsd = xsd_validate(VALIDATOR_XSD, doc);
	return (xsd) ? 1 : 0;
}

xmlDocPtr		getdoc(char *docname)
{
	xmlDocPtr doc;

	doc = xmlReadFile(docname, NULL, 0);
	if (doc == NULL)
	{
		ft_putendl_fd("Wrong xml file\n", STD_ERR);
		return (NULL);
	}
	return (doc);
}

void		open_scene_clicked(GtkWidget *btn, t_rt *e)
{
	GtkWidget	*dialog;
	GtkWidget	*win;
	gint		res;
	xmlDocPtr	doc;

	(void)btn;
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	dialog = gtk_file_chooser_dialog_new(
				"Open File", GTK_WINDOW(win), GTK_FILE_CHOOSER_ACTION_OPEN,
				"Cancel", GTK_RESPONSE_CANCEL,
				"Open", GTK_RESPONSE_ACCEPT, NULL);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		SFILE = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));;
		gtk_widget_destroy(dialog);
		if (!(doc = getdoc(SFILE)) || !do_checks(doc))
			return ;
		parse2(e, doc);
		gtk_widget_destroy(e->gtk.menu.window);
		ft_start_rt(e);
		g_free(SFILE);
	}
	else
		gtk_widget_destroy(dialog);
}

void		open_scene(t_rt *e)
{
	GtkWidget	*btn;

	btn = new_btn(200, 40, "Open scene");
	gtk_layout_put(GTK_LAYOUT(e->gtk.menu.layout), btn, 50, 50);
	g_signal_connect(btn, "clicked", G_CALLBACK(open_scene_clicked), e);
}

void		ft_gtk_launcher(t_rt *e)
{
	open_scene(e);
}