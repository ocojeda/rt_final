PROJECT		=	RT
NAME		=	rt
OBJDIR		=	objs/
SRCDIR		=	srcs/
SRC			=	main.c \
				hooks.c \
				mlx_begin.c \
				raytrace.c \
				color.c \
				ray.c \
				frame.c \
				sphere.c \
				plane.c \
				cylinder.c \
				cone.c \
				normal.c \
				intensity.c \
				reflex.c \
				matrix.c \
				hooks_mousse.c \
				filters.c \
				refraction.c \
				paraboloid.c \
				bruit.c \
				intersect.c \
				negative_intersect.c \
				damier.c \
				parsing/parse.c \
				parsing/checks.c \
				parsing/parser_utils.c \
				parsing/parse_objects.c \
				parsing/parse_camera.c \
				parsing/parse_attributes.c \
				parsing/parse_lights.c
MINILIBX	=	libs/minilibx/libmlx.a
LIBFT		=	libs/libft/libft.a
LIBVEC		=	libs/libvec/libvec.a
LIBXML		=	`xml2-config --libs`
LIBXML_H	=	`xml2-config --cflags`
VPATH		=	$(SRCDIR):$(SRCDIR)parsing

OBJ			=	$(SRC:.c=.o)
OBJ			:=	$(notdir $(OBJ))
OBJ			:=	$(addprefix $(OBJDIR), $(OBJ))
CC			=	gcc
INC 		=	includes
CFLAGS		=	-Wall -Wextra -g -I includes/ -I libs/libft/includes/ -I libs/libvec/includes/ $(LIBXML_H) # add werror
MLXF		=	-framework OpenGL -framework AppKit -lxml2
WHITE		=	\033[7;49;39m
BLUE		=	\033[7;49;34m
RED			=	\x1B[31m
YELLOW		=	\x1B[33m
GREEN		=	\033[0;49;32m
GREEN_BG	=	\033[1;49;32m
GRAY		=	\033[7;49;90m
NO_COLOR	=	\033[m

all: mlx lib vec $(NAME)

$(NAME): $(MINILIBX) $(LIBFT) $(OBJDIR) $(OBJ)
	@printf "\r$(GREEN)[$(PROJECT)] Obj compilation done.                                                        \n"
	@printf "$(YELLOW)[$(PROJECT)] Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(MLXF) -o $(NAME) $(OBJ) $(MINILIBX) $(LIBFT) $(LIBVEC) $(LIBXML)
	@printf "\r$(GREEN)[$(PROJECT)] Compilation done.                          \n$(NO_COLOR)"

$(OBJDIR)%.o: %.c
	@printf "$(YELLOW)\r[$(PROJECT)] Compiling $< to $@                                                          \r"
	@$(CC) $(CFLAGS) -o $@ -c $<

mlx:
	@printf "$(YELLOW)[MINILIBX] Compiling obj...                                                     \r$(NO_COLOR)"
	@make -s -C libs/minilibx 2> /dev/null > /dev/null

lib:
	@make -s -C libs/libft 2> /dev/null > /dev/null

vec:
	@make -s -C libs/libvec 2> /dev/null > /dev/null

$(OBJDIR):
	@mkdir $(OBJDIR)

clean:
	@make -s -C libs/libft clean
	@make -s -C libs/libvec clean
	@printf "$(YELLOW)[$(PROJECT)] Removing obj..."
	@rm -rf $(OBJ)
	@rm -rf $(OBJDIR)
	@printf "\r$(GREEN)[$(PROJECT)] Obj removed.                                                   \n$(NO_COLOR)"

fclean:
	@make -s -C libs/minilibx clean
	@make -s -C libs/libft fclean
	@make -s -C libs/libvec fclean
	@printf "$(YELLOW)[$(PROJECT)] Removing obj..."
	@rm -rf $(OBJ)
	@rm -rf $(OBJDIR)
	@printf "\r$(GREEN)[$(PROJECT)] Obj removed.                                                   \n$(NO_COLOR)"
	@printf "$(YELLOW)[$(PROJECT)] Removing $(NAME)..."
	@rm -rf $(NAME)
	@printf "\r$(GREEN)[$(PROJECT)] $(NAME) removed.                                               \n$(NO_COLOR)"

re: fclean all

norme: norminette srcs libs includes

.PHONY: all clean fclean re