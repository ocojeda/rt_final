#include "rt.h"

static void		set_attrs4(t_obj *obj, xmlNodePtr node)
{
	xmlChar		*val;

	if ((val = xmlGetProp(node, (xmlChar *)"sin")))
	{
		obj->mat.sinus = ft_atof((char *)val);
		xmlFree(val);
	}
	else
		obj->mat.sinus = 0;
	if ((val = xmlGetProp(node, (xmlChar *)"damier")))
	{
		obj->mat.damier= ft_atof((char *)val);
		xmlFree(val);
	}
	else
		obj->mat.damier= 0;
	if ((val = xmlGetProp(node, (xmlChar *)"refract_rate")))
	{
		obj->mat.refract_rate = ft_atof((char *)val);
		xmlFree(val);
	}
	else
		obj->mat.refract_rate = 0;	
}	

static void		set_attrs3(t_obj *obj, xmlNodePtr node)
{
	xmlChar		*val;

	if ((val = xmlGetProp(node, (xmlChar *)"refract_filter")))
	{
		obj->mat.refract_filter = ft_atof((char *)val);
		xmlFree(val);
	}
	else
		obj->mat.refract_filter = 0;
	if ((val = xmlGetProp(node, (xmlChar *)"reflex_filter")))
	{
		obj->mat.reflex_filter = ft_atof((char *)val);
		xmlFree(val);
	}
	else
		obj->mat.reflex_filter = 0;
	set_attrs4(obj, node);
}

static void		set_attrs2(t_obj *obj, xmlNodePtr node)
{
	xmlChar		*val;

	if ((val = xmlGetProp(node, (xmlChar *)"negative")))
	{
		obj->neg = ft_strequ("true", (char *)val) ? 1 : 0;
		xmlFree(val);
	}
	else
		obj->neg = 0;
	if ((val = xmlGetProp(node, (xmlChar *)"refract")))
	{
		obj->mat.refract = ft_atof((char *)val);
		xmlFree(val);
	}
	else
	if ((val = xmlGetProp(node, (xmlChar *)"reflex")))
	{
		obj->mat.reflex = ft_atof((char *)val);
		xmlFree(val);
	}
	else
		obj->mat.reflex = 0;
	set_attrs3(obj, node);
}

void			set_attrs(t_obj *obj, xmlNodePtr node)
{
	xmlChar		*val;

	if ((val = xmlGetProp(node, (xmlChar *)"radius")))
	{
		obj->r = ft_atof((char *)val);
		xmlFree(val);
	}
	else
		obj->r = 0;
	if ((val = xmlGetProp(node, (xmlChar *)"diff")))
	{
		obj->mat.diff = ft_atof((char *)val);
		xmlFree(val);
	}
	else
		obj->mat.diff = 0;
	if ((val = xmlGetProp(node, (xmlChar *)"spec")))
	{
		obj->mat.spec = ft_atof((char *)val);
		xmlFree(val);
	}
	else
		obj->mat.spec = 0;
	if ((val = xmlGetProp(node, (xmlChar *)"angle")))
	{
		obj->k = ft_atof((char *)val);
		xmlFree(val);
	}
	else
		obj->k = 0;
	set_attrs2(obj, node);
}
