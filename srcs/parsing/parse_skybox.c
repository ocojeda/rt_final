#include "rt.h"

void			parse_skybox(t_rt *e, t_list *lst)
{
	xmlChar		*path;
	xmlNodePtr	node;

	if (!lst)
		return ;
	node = (xmlNodePtr)(lst->content);
	path = xmlGetProp(node, (xmlChar *)"path");
	if (!path)
		return ;
	e->scene.skybox.ptr = mlx_xpm_file_to_image(
		INIT,
		(char *)path,
		&e->scene.skybox.width,
		&e->scene.skybox.height);
	xmlFree(path);
	if (!e->scene.skybox.ptr)
		err_found("skybox can't be loaded");
	if (!(e->scene.skybox.data = mlx_get_data_addr(e->scene.skybox.ptr,
		&e->scene.skybox.bpp, &e->scene.skybox.sizl,
		&e->scene.skybox.endian)))
		err_found("skybox can't be loaded");
	else
		e->scene.skybox.is_init = 1;
}
