#include "rt.h"

static int			calcul_res(t_rt *e, int limit)
{
	int res;
	int air;

	air = e->file.larg * e->file.haut;
	res = 1;
	limit /= 2;
	while ((air / res) > limit)
		res++;
	return (res);
}

static void			parse_scene(t_rt *e, xmlNodePtr node)
{
	xmlChar	*val;

	val = xmlGetProp(node, (xmlChar*)"ambient");
	e->scene.ambient = ft_atof((char*)val);
	e->scene.ambient = (e->scene.ambient > 1) ? 1.00 : e->scene.ambient;
	e->scene.ambient = (e->scene.ambient < 0) ? 0 : e->scene.ambient;
	xmlFree(val);
	val = xmlGetProp(node, (xmlChar*)"width");
	e->file.larg = ft_atoi((char*)val);
	xmlFree(val);
	val = xmlGetProp(node, (xmlChar*)"height");
	e->file.haut = ft_atoi((char*)val);
	e->file.aliasing = 1;
	e->file.reso = calcul_res(e, 400000);
	e->file.reso_buff = e->file.reso;
	e->scene.selected_obj = -1;
	e->scene.filters = 0;
	xmlFree(val);
}

void				parse(t_rt *e, int ac, char **av)
{
	xmlDocPtr	doc;
	xmlNodePtr	root;
	t_list		*lst;

	lst = NULL;
	if (ac != 2 || ft_strncmp(ft_strrev(av[1]), "lmx.", 4) != 0)
		err_found("usage: rt input_map.xml");
	doc = xmlParseFile(ft_strrev(av[1]));
	if (doc == NULL)
		err_found("Wrong xml file");
	check_doc(doc);
	root = xmlDocGetRootElement(doc);
	parse_scene(e, root);
	get_nodes_by_name(root, "objects", &lst);
	parse_objects(e, lst);
	ft_lstfree(&lst);
	get_nodes_by_name(root, "camera", &lst);
	parse_camera(e, (xmlNodePtr)(lst->content));
	ft_lstfree(&lst);
	get_nodes_by_name(root, "light", &lst);
	parse_lights(e, lst);
	ft_lstfree(&lst);
	xmlFreeDoc(doc);
	xmlCleanupParser();
}
