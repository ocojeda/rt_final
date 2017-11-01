#include "../includes/rt.h"

int		xsd_read_error(void)
{
	ft_putendl_fd("Could not open XML Schema", STD_ERR);
	xmlCleanupParser();
	xmlMemoryDump();
	exit(-1);
}

int		dtd_read_error(xmlDtdPtr dtd)
{
	ft_putendl_fd("Could not open DTD file", STD_ERR);
	xmlFreeDtd(dtd);
	exit(-1);
}

void	xml_alloc_error(void)
{
	ft_putendl_fd("An error occured", STD_ERR);
	exit(-1);
}

void	xml_read_error(void)
{
	ft_putendl_fd("Wrong xml file\n", STD_ERR);
	exit(-1);
}

static int			dtd_validate(xmlDocPtr doc, char *file, int print_e)
{
	int				ret;
	xmlDtdPtr		dtd;
	xmlValidCtxtPtr	vctxt;

	if ((dtd = xmlParseDTD(NULL, (xmlChar*)file)) == NULL)
		dtd_read_error(dtd);
	if ((vctxt = xmlNewValidCtxt()) == NULL)
		xml_alloc_error();
	if (print_e)
	{
		vctxt->userData = (void *)stderr;
		vctxt->error = (xmlValidityErrorFunc)NULL;
		vctxt->warning = (xmlValidityWarningFunc)NULL;
	}
	ret = xmlValidateDtd(vctxt, doc, dtd);
	xmlFreeValidCtxt(vctxt);
	xmlFreeDtd(dtd);
	return (ret);
}

static xmlSchemaPtr	get_xsd(char *xsd_path)
{
	xmlSchemaPtr			ptr_schema;
	xmlSchemaParserCtxtPtr	ptr_ctxt;

	ptr_schema = NULL;
	ptr_ctxt = xmlSchemaNewParserCtxt(xsd_path);
	xmlSchemaSetParserErrors(ptr_ctxt, (xmlSchemaValidityErrorFunc)NULL,
		(xmlSchemaValidityWarningFunc)NULL, stderr);
	ptr_schema = xmlSchemaParse(ptr_ctxt);
	xmlSchemaFreeParserCtxt(ptr_ctxt);
	return (ptr_schema);
}

static int			xsd_validate(char *xsd_path, xmlDocPtr doc)
{
	xmlSchemaPtr			ptr_schema;
	xmlSchemaValidCtxtPtr	ptr_validctxt;
	int						vl_return;

	ptr_schema = get_xsd(xsd_path);
	if (!ptr_schema)
		return (xsd_read_error());
	if (doc)
	{
		ptr_validctxt = xmlSchemaNewValidCtxt(ptr_schema);
		xmlSchemaSetValidErrors(ptr_validctxt,
								(xmlSchemaValidityErrorFunc)NULL,
								(xmlSchemaValidityWarningFunc)NULL, stderr);
		vl_return = xmlSchemaValidateDoc(ptr_validctxt, doc);
		if (vl_return == 0)
			xmlSchemaFreeValidCtxt(ptr_validctxt);
		if (vl_return == 0)
			return (1);
		else if (vl_return > 0)
			return (0);
		else
			return (-1);
	}
	return (-1);
}

int					do_checks(xmlDocPtr doc)
{
	xmlValidCtxtPtr	vctxt;
	int				dtd;
	int				xsd;

	if (!(vctxt = xmlNewValidCtxt()))
		return (0);
	dtd = dtd_validate(doc, VALIDATOR_DTD, 1);
	xsd = xsd_validate(VALIDATOR_XSD, doc);
	return (dtd && xsd) ? 1 : 0;
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

void		btn_settings_clicked(GtkWidget *btn, t_rt *e)
{
	(void)btn;
	e->gtk.settings.window = new_window(200, 400, "Settings");
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

	printf("%s\n", "Btn Setting");
	btn = new_btn(200, 40, "Settings");
	gtk_layout_put(GTK_LAYOUT(e->gtk.menu.layout), btn, 50, 50);
	g_signal_connect(btn, "clicked", G_CALLBACK(btn_settings_clicked), e);
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

	printf("%s\n", "Open scene");
	btn = new_btn(200, 40, "Open scene");
	gtk_layout_put(GTK_LAYOUT(e->gtk.menu.layout), btn, 50, 110);
	g_signal_connect(btn, "clicked", G_CALLBACK(open_scene_clicked), e);
}

void		ft_gtk_launcher(t_rt *e)
{
	printf("%s\n", "Setting Bouton");
	btn_settings(e);
	open_scene(e);
}