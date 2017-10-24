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

# include <gtk/gtk.h>

# define END 0
# define CONE 1
# define PLANE 2
# define SPHERE 3
# define CYLINDER 4

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
# define SFILE e->file.path
# define RES_H (HAUTEUR / RES)
# define RES_W (LARGEUR / RES)

# define MAXOBJ 50
# define NR_ITER 6
# define MAXLIGHT 21
# define NB_THREADS 8
# define DIST_MAX 20000
# define DIST_MIN -80000
# define EPSILON 1e-7

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
//	t_vec3			focus_point;
	t_vec3			rot;
	t_mtrx4			ctw;
	float			reso;
	float			aspect;
	float			ratio_x;
	float			ratio_y;
	char			is_circular;
	t_vec3			tmp_rot;
}					t_camera;

typedef struct		s_matiere
{
	//t_checker		checker;
	float			diff;
	float			spec;
	float			refract;
	float			reflex;
	//t_texture		tex;
	float			absorbtion;
	char			*coeff;
	char			opacite;
	int				sin;
	int				perlin;
	//t_texture		texture;
}					t_matiere;

typedef struct		s_obj
{
	char			is_init;
	char			is_disp;
	int				type;
	t_color			color;
	t_vec3			pos;
	t_vec2			last_pos;
	t_vec3			dir;
	float			k;
	t_vec3			vector;
	int				r;
	float			t;
	int				nbr_t;
	t_vec3			normal;
	t_matiere		mat;
	char			neg;
	int				plimit_active;
	int				plimit_type;
	int				plimit_valid;
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
//	t_texture		skybox;
//	int				last;
	float			ambient;
	int				nbr_light;
	int				nbr_obj;
//	int				nbr_complex;
//	char			nbr_tot;
	int				id;
//	int				supersampling;
	int				selected_obj;
	int				selected;
	int				filters;
//	int				max_iter;
}					t_scene;

typedef struct		s_file
{
	char			*path;
	int				haut;
	int				larg;
//	int				fdp;
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
	t_color			color;
	float			total_distance;
	int				counter;
	float			min_dist;
	int				tmp_id;
	float			dist_rate;
	int				a;
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
//	t_keys			keys;
	t_gtk			gtk;
	t_scene			scene;
	t_file			file;
	t_mthread		thread;
	int				frame;
}					t_rt;
/*
* parsing fonctions
*/
void			ft_start_rt(t_rt *e);
void			init_rt(t_rt *e);

/*
* multhread fonctions
*/
void			frame(t_rt *e);

/*
* color managing fonctions
*/
unsigned int	ret_colors(t_color colo);
t_color			c_color(float r, float g, float b);
t_color			color_mult(t_color color, float taux, float limit);
t_color			ft_map_color(t_color color1, t_color color2, float taux1);

/*
*raytracing basic fonctions
*/
t_color			raytrace(int x, int y, t_rt *e);
t_ray			ray_init(t_rt *e, int x, int y);

t_ray			c_ray(t_vec3 i, t_vec3 j);
t_color			get_color(t_rt *e, t_obj obj, t_vec3 poi);

/*
*mlx relative fonctions
*/
void			pixel_to_image(int x, int y, t_rt *e, int color);
int				keypress(int keycode, void *param);
int				mousse_hook(int button, int x, int y, void *param);
/*
* intersect fonctions
*/

float			intersect_obj(t_ray ray, t_obj *obj, t_rt *e);
float			intersect_sphere(t_ray ray, t_obj *sphere);
float			intersect_plane(t_ray ray, t_obj *plane);
float			intersect_cylinder(t_ray ray, t_obj *cyl);
float			intersect_cone(t_ray ray, t_obj *cone);
t_vec3			plane_norm(t_obj plane);
float			get_res_of_quadratic(t_calc *op, t_obj *obj);
float			get_min_dist(t_rt *e, t_ray ray);

/*
* math aux fonctions
*/
float			p(float x);
float			get_length(t_vec3 v);

/*
* fonction pour les normales
*/
t_vec3				color_norm(t_obj obj, t_vec3 poi, t_vec3 light);
t_vec3				object_norm(t_obj obj, t_vec3 poi);
t_vec3				cone_norm(t_obj obj, t_vec3 poi);
t_vec3				plane_norm(t_obj obj);
t_vec3				sphere_norm(t_obj obj, t_vec3 poi);
t_vec3				cylinder_norm(t_obj obj, t_vec3 poi);

/*
*	que le lumiere soit
*/

float		intensity_obj(t_rt *e, t_vec3 poi, t_obj obj, t_light light);
float		diff_intensity(t_obj obj, float dot);

/*
*	reflexion fonctions
*/
t_color		get_reflected_color(t_rt *e, t_vec3 poi,
t_color base_color, t_reflect ref);
t_color		ret_reflected_pixel(t_rt *e, t_reflect ref, t_ray ray,
		float min_dist);

void		matrix_init(t_rt *e);
void		filter_black_and_white(t_rt *e);
void		filters(t_rt *e);

float			get_res_of_quadratic_neg(t_calc *op, t_obj *obj, float dist_obj);
float			intersect_cone_neg(t_ray ray, t_obj *cone, float dist_obj);
float		intersect_cylinder_neg(t_ray ray, t_obj *cyl, float dist_obj);
float			intersect_sphere_neg(t_ray ray, t_obj *sphere, float dist_obj);

void				ft_init_values(t_rt *e);
gboolean			hook(GtkWidget *widget, GdkEventKey *event,
		gpointer user_data);
void				ft_gtk_start_launcher(t_rt *e);
void				ft_gtk_start_settings(t_rt *e);
void				ft_settings(t_rt *e);
void				ft_gtk_launcher(t_rt *e);
GtkWidget			*new_window(gint w, gint h, gchar *name);
GtkWidget			*new_input(t_gtk_input *data);
GtkWidget			*new_txt(gchar *str);
GtkWidget			*new_btn(int x, int y, char *name);
void				ft_gtk_link_css(GtkWidget *window, gchar *css);
void				ft_add_w(GtkEntry *entry, t_rt *e);
void				ft_add_h(GtkEntry *entry, t_rt *e);
void				ft_add_res(GtkEntry *entry, t_rt *e);
void				ft_add_anti(GObject *sw, GParamSpec *ps, t_rt *e);
void				ft_add_antialiasing(t_rt *e);
void				ft_add_resolution(t_rt *e);
void				ft_add_win_size(t_rt *e);
GtkWidget			*new_window(gint w, gint h, gchar *name);
GtkWidget			*new_input(t_gtk_input *data);
GtkWidget			*new_txt(gchar *str);
GtkWidget			*new_btn(int x, int y, char *name);
void				ft_gtk_link_css(GtkWidget *window, gchar *css);
void				gtk_hook(int keycode, t_rt *e);
int					calcul_res(t_rt *e, int limit);

#endif