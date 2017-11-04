#include "../includes/rt.h"

int		xsd_read_error(void)
{
	ft_putendl_fd("Could not open XML Schema", STD_ERR);
	xmlCleanupParser();
	xmlMemoryDump();
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

int			xsd_validate(char *xsd_path, xmlDocPtr doc)
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