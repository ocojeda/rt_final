#include "rt.h"

static void		set_attrs2(t_obj *obj, xmlNodePtr node)
{
	xmlChar		*val;

	if ((val = xmlGetProp(node, (xmlChar *)"negative")))
	{
		obj->neg = ft_strequ("true", (char *)val) ? 1 : 0;
		xmlFree(val);
	}
	if ((val = xmlGetProp(node, (xmlChar *)"refract")))
	{
		obj->mat.refract = ft_atof((char *)val);
		xmlFree(val);
	}
	if ((val = xmlGetProp(node, (xmlChar *)"reflex")))
	{
		obj->mat.reflex = ft_atof((char *)val);
		xmlFree(val);
	}
}

void			set_attrs(t_obj *obj, xmlNodePtr node)
{
	xmlChar		*val;

	if ((val = xmlGetProp(node, (xmlChar *)"radius")))
	{
		obj->r = ft_atof((char *)val);
		xmlFree(val);
	}
	if ((val = xmlGetProp(node, (xmlChar *)"shine")))
	{
		obj->mat.diff = ft_atof((char *)val);
		xmlFree(val);
	}
	if ((val = xmlGetProp(node, (xmlChar *)"angle")))
	{
		obj->k = ft_atof((char *)val);
		xmlFree(val);
	}
	set_attrs2(obj, node);
}

void			set_attrs_limits(t_limit *limit, xmlNodePtr node)
{
	xmlChar		*val;

	if ((val = xmlGetProp(node, (xmlChar *)"radius")))
	{
		limit->r = ft_atof((char *)val);
		xmlFree(val);
	}
}
