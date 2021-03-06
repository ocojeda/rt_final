/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfaure <tfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 20:42:52 by bbeldame          #+#    #+#             */
/*   Updated: 2017/11/05 15:04:27 by tfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx/mlx.h"
# include "../libs/libvec/includes/libvec.h"
# include <math.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <unistd.h>

# include <libxml/parser.h>
# include <libxml/tree.h>
# include <libxml/xmlIO.h>
# include <libxml/xinclude.h>
# include <libxml/valid.h>
# include <libxml/xmlschemas.h>
# include <libxml/xmlstring.h>
# include <libxml/xmlreader.h>

# include <gtk/gtk.h>

# define END 0
# define CONE 1
# define PLANE 2
# define SPHERE 3
# define CYLINDER 4
# define PARABOLOID 5

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_F 3
# define KEY_H 4
# define KEY_G 5
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_V 9
# define KEY_B 11
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_Y 16
# define KEY_T 17
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_SIX 22
# define KEY_FIVE 23
# define KEY_NINE 25
# define KEY_SEVEN 26
# define KEY_EIGHT 28
# define KEY_ZERO 29
# define KEY_BRACE_R 30
# define KEY_O 31
# define KEY_U 32
# define KEY_BRACE_L 33
# define KEY_I 34
# define KEY_P 35
# define KEY_L 37
# define KEY_J 38
# define KEY_K 40
# define KEY_SEMI 41
# define KEY_N 45
# define KEY_M 46
# define KEY_TAB 48
# define KEY_PLUS 69
# define KEY_MINUS 78
# define PAGE_UP	116
# define PAGE_DOWN	121
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_ESC 53
# define KEY_HOME 115
# define KEY_DEL 117
# define COBJ e->scene.obj
# define CCAM e->scene.cam
# define CLIGHT scene.lights[i]
# define AMBIENT_LIGHT e->scene.ambient
# define ALIASING e->file.aliasing
# define INIT e->mlx.init
# define WIN e->mlx.window
# define IMG e->mlx.image
# define DATA e->mlx.data
# define THREAD th_e[i]->thread
# define HAUTEUR e->file.haut
# define LARGEUR e->file.larg
# define RES e->file.reso
# define RES_BUFF e->file.reso_buff
# define RES_H (HAUTEUR / RES)
# define RES_W (LARGEUR / RES)
# define SFILE e->file.path
# define FILT e->scene.filters

# define MAXOBJ 50
# define NR_ITER 30
# define MAXLIGHT 21
# define NB_THREADS 8
# define DIST_MAX 2000000
# define DIST_MIN -80000
# define EPSILON 1e-7
# define SIZE_LP 50

# define VALIDATOR_XSD "validator.xsd"
# define STD_ERR 2

typedef struct		s_ray
{
	t_vec3			pos;
	t_vec3			dir;
}					t_ray;

typedef struct		s_color
{
	float			b;
	float			g;
	float			r;
	float			a;
}					t_color;

typedef struct		s_mthread
{
	float			y;
	float			max_y;
	float			h;
	float			w;
	t_color			*colors;
}					t_mthread;

typedef struct		s_camera
{
	int				fov;
	t_vec3			pos;
	t_vec3			rot;
	t_mtrx4			ctw;
	float			reso;
	float			aspect;
	float			ratio_x;
	float			ratio_y;
	char			is_circular;
	t_vec3			tmp_rot;
}					t_camera;

typedef struct		s_texture
{
	char			is_init;
	void			*ptr;
	char			*data;
	int				bpp;
	int				sizl;
	int				endian;
	int				width;
	int				height;
}					t_texture;

typedef struct		s_matiere
{
	float			diff;
	float			spec;
	float			refract;
	float			refract_rate;
	float			refract_filter;
	float			reflex;
	t_texture		tex;
	float			absorbtion;
	float			reflex_filter;
	char			*coeff;
	char			opacite;
	int				sinus;
	int				damier;
	int				perlin;
}					t_matiere;

typedef	struct		s_limit
{
	int				type;
	int				r;
	t_vec3			pos;
	t_vec3			vector;

}					t_limit;

typedef struct		s_obj
{
	float			max_dist;
	int				type;
	t_color			color;
	t_vec3			pos;
	float			k;
	t_vec3			vector;
	int				r;
	int				nbr_t;
	t_matiere		mat;
	int				neg;
	int				limit_active;
	int				limit_nbr;
	t_limit			limit[4];
	int				id;
}					t_obj;

typedef struct		s_light
{
	int				is_init;
	t_ray			ray;
	t_color			color;
	float			intensity;
}					t_light;

typedef struct		s_scene
{
	t_camera		cam;
	t_light			*lights;
	t_obj			*obj;
	t_texture		skybox;
	int				x;
	int				y;
	float			ambient;
	int				nbr_light;
	int				nbr_obj;
	int				id;
	int				selected_obj;
	int				selected;
	int				filters;
}					t_scene;

typedef struct		s_file
{
	char			*path;
	int				haut;
	int				larg;
	int				fd_exp;
	int				reso;
	int				reso_buff;
	int				aliasing;
}					t_file;

typedef struct		s_mlx
{
	void			*init;
	void			*window;
	void			*image;
	char			*data;
	int				bpp;
	int				size_l;
	int				endian;
}					t_mlx;

typedef struct		s_reflect
{
	t_ray			ray;
	t_ray			new_ray;
	t_vec3			poi;
	t_vec3			p2;
	t_color			color;
	int				type;
	float			total_distance;
	int				counter;
	float			min_dist;
	int				tmp_id;
	float			dist_rate;
	int				a;
	int				x;
	int				y;
	float			opac;
	float			d1;
	float			d2;
}					t_reflect;

typedef struct		s_calc
{
	float			a;
	float			b;
	float			c;
	float			d;
	float			t0;
	float			t1;
	float			disc;
	float			eq;
	t_vec3			len;
	float			sqrtdisc;
}					t_calc;

typedef struct		s_norme
{
	int				x;
	int				y;
	int				a;
	float			min_dist;
	t_ray			ray;
	float			taux_temp;
	t_color			temp_color1;
	float			distance_rate;
	int				counter;
	t_color			base_color;
	t_color			final_color;
	t_vec3			newpoi;
	t_vec3			poi;
	t_color			color;
}					t_norme;

typedef struct		s_gtk_input
{
	gint			max_size;
	gint			max_char;
	gchar			*placeholder;
	gchar			*deflaut_value;
}					t_gtk_input;

typedef struct		s_gtk_win
{
	GtkWidget		*window;
	GtkWidget		*layout;
}					t_gtk_win;

typedef struct		s_gtk_settings
{
	int				width;
	int				height;
	int				res;
	int				filt;
	GtkWidget		*anti_aliasing;
}					t_gtk_settings;

typedef struct		s_gtk
{
	t_gtk_win		menu;
	t_gtk_win		settings;
	t_gtk_settings	values;
	int				started;
}					t_gtk;

typedef struct		s_rt
{
	t_mlx			mlx;
	t_gtk			gtk;
	t_scene			scene;
	t_file			file;
	t_mthread		thread;
	int				frame;
}					t_rt;

void				ft_start_rt(t_rt *e);

void				frame(t_rt *e);

unsigned int		ret_colors(t_color colo);
t_color				c_color(float r, float g, float b);
t_color				color_mult(t_color color, float taux, float limit);
t_color				ft_map_color(t_color color1, t_color color2, float taux1);

t_color				raytrace(int x, int y, t_rt *e);
t_ray				ray_init(t_rt *e, int x, int y);

t_ray				c_ray(t_vec3 i, t_vec3 j);
t_color				get_color(t_rt *e, t_obj obj, t_vec3 poi, t_ray ray);

void				pixel_to_image(int x, int y, t_rt *e, int color);
int					keypress(int keycode, void *param);
int					mousse_hook(int button, int x, int y, void *param);
int					mouse_hook_escape(t_rt *e);

float				check_negative_objects(float dist_obj,
	t_rt *e, t_ray ray, float max_dist);
float				intersect_obj(t_ray ray, t_obj *obj, t_rt *e);
float				intersect_sphere(t_ray ray, t_obj *sphere);
float				intersect_plane(t_ray ray, t_obj *plane);
float				intersect_cylinder(t_ray ray, t_obj *cyl);
float				intersect_cone(t_ray ray, t_obj *cone);
float				get_res_of_quadratic(t_calc *op, t_obj *obj);
float				get_min_dist(t_rt *e, t_ray ray);
float				intersect_paraboloid(t_ray ray, t_obj *parab);

float				intersect_obj_limit(t_ray ray, t_limit *obj, t_rt *e);

int					damier(t_vec3 *pos);
float				p(float x);
float				get_length(t_vec3 v);

t_vec3				object_norm(t_obj obj, t_vec3 poi, t_vec3 cam);
t_vec3				cone_norm(t_obj obj, t_vec3 poi);
t_vec3				plane_norm(t_obj plane);
t_vec3				sphere_norm(t_obj obj, t_vec3 poi);
t_vec3				cylinder_norm(t_obj obj, t_vec3 poi);
t_vec3				paraboloid_norm(t_obj cone, t_vec3 poi);

float				intensity_obj(t_rt *e, t_vec3 poi,
	t_ray ray, t_light light);
float				diff_intensity(t_obj obj, float dot);

t_color				get_reflected_color(t_rt *e, t_vec3 poi, t_color base_color,
	t_reflect ref);

float				find_min_dist_for_refref(t_rt *e, int *a, t_ray ray);
t_color				get_refracted_color(t_rt *e, t_vec3 poi, t_color base_color,
	t_reflect ref);
t_ray				get_reflected_ray(t_rt *e, t_ray rayon, t_vec3 poi);

t_color				skybox(t_rt *e, t_ray ray);
t_color				get_text_color(int x, int y, t_texture tex);

void				matrix_init(t_rt *e);
void				filter_black_and_white(t_rt *e);
void				filters(t_rt *e);

float				get_res_of_quadratic_neg(t_calc *op, t_obj *obj,
	float dist_obj, float max_dist);
float				intersect_cone_neg(t_ray ray, t_obj *cone,
	float dist_obj, float max_dist);
float				intersect_cylinder_neg(t_ray ray, t_obj *cyl,
	float dist_obj, float max_dist);
float				intersect_sphere_neg(t_ray ray, t_obj *sphere,
	float dist_obj, float max_dist);
float				intersect_paraboloid_neg(t_ray ray, t_obj *parab,
	float dist_obj, float max_dist);

void				parse(t_rt *e, int argc, char **argv);
void				parse2(t_rt *e, xmlDocPtr doc);
void				check_doc(xmlDocPtr	doc);
void				get_nodes_by_name(xmlNodePtr cur,
						char *node_name, t_list **lst);
void				parse_objects(t_rt *e, t_list *lst);
t_vec3				get_vec_from_node(xmlNodePtr node);
t_color				parse_color(xmlNodePtr node);
xmlNodePtr			has_child(xmlNodePtr a_node, char *attr);
void				parse_camera(t_rt *e, xmlNodePtr node);
void				parse_lights(t_rt *e, t_list *lst);
void				set_attrs(t_obj *obj, xmlNodePtr node);

gboolean			hook(GtkWidget *widget, GdkEventKey *event,
		gpointer user_data);
void				ft_gtk_start_launcher(t_rt *e);
void				ft_gtk_launcher(t_rt *e);
GtkWidget			*new_window(gint w, gint h, gchar *name);
GtkWidget			*new_btn(int x, int y, char *name);
void				ft_gtk_link_css(GtkWidget *window, gchar *css);
int					xsd_validate(char *xsd_path, xmlDocPtr doc);
int					calcul_res(t_rt *e, int limit);

void				screenshot_ppm(t_rt *e);
t_color				bruit(float valeur, t_color c1, t_color c2, float seuil);
t_color				bruit2(float valeur, t_color c1, t_color c2, float x);
t_color				bruit3(float valeur, int x, int y);
float				bruit_coherent(float x, float y, float persistance);
void				parse(t_rt *e, int argc, char **argv);
void				check_doc(xmlDocPtr	doc);
void				get_nodes_by_name(xmlNodePtr cur,
						char *node_name, t_list **lst);
void				parse_objects(t_rt *e, t_list *lst);
t_vec3				get_vec_from_node(xmlNodePtr node);
t_color				parse_color(xmlNodePtr node);
xmlNodePtr			has_child(xmlNodePtr a_node, char *attr);
void				parse_camera(t_rt *e, xmlNodePtr node);
void				parse_lights(t_rt *e, t_list *lst);
void				set_attrs(t_obj *obj, xmlNodePtr node);
void				parse_limits(xmlNodePtr node_obj, t_obj *obj);
void				parse_skybox(t_rt *e, t_list *lst);

double				get_perlin(double x, double y, double z);

t_vec3				norm_limit_plane(t_limit *plane, t_ray ray);
float				intersect_limit_sphere(t_ray ray, t_limit *sphere);
t_rt				*copy_rt(t_rt *e);
t_light				copy_light(t_light light);
void				finish_it(t_rt **th_e, t_rt *e);
void				keypress4(int keycode, t_rt *e, int i);
#endif
