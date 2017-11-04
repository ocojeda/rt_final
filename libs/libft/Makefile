# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbeldame <bbeldame@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/21 03:19:16 by bbeldame          #+#    #+#              #
#    Updated: 2017/11/04 21:25:20 by bbeldame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT		=	LIBFT
NAME		=	libft.a
OBJDIR		=	objs/
SRCDIR		=	srcs/
SRC			=	err_found.c \
				free_splited_str.c \
				ft_atof.c \
				ft_atoi.c \
				ft_bzero.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_lstadd.c \
				ft_lstdel.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstpush.c \
				ft_lstlen.c \
				ft_lstfree.c \
				ft_map.c \
				ft_max.c \
				ft_memalloc.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memdel.c \
				ft_memmove.c \
				ft_memset.c \
				ft_min.c \
				ft_putchar.c \
				ft_putchar_fd.c \
				ft_putendl.c \
				ft_putendl_fd.c \
				ft_putnbr.c \
				ft_putnbr_fd.c \
				ft_putstr.c \
				ft_putstr_fd.c \
				ft_realloc.c \
				ft_split_whitespaces.c \
				ft_strcat.c \
				ft_strchr.c \
				ft_strclr.c \
				ft_strcmp.c \
				ft_strcpy.c \
				ft_strdel.c \
				ft_strdup.c \
				ft_strequ.c \
				ft_striter.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlen.c \
				ft_strmap.c \
				ft_strmapi.c \
				ft_strncat.c \
				ft_strncmp.c \
				ft_strncpy.c \
				ft_strnequ.c \
				ft_strnew.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strrev.c \
				ft_strsplit.c \
				ft_strstr.c \
				ft_strsub.c \
				ft_strtolower.c \
				ft_strtoupper.c \
				ft_strtrim.c \
				ft_tolower.c \
				ft_toupper.c \
				get_next_line.c \
				len_of_tab.c \
				semalloc.c
OBJ			=	$(addprefix $(OBJDIR),$(SRC:.c=.o))
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -I includes/
OPTI		=	-O3
DEBUG		=	-g

WHITE		=	\033[7;49;39m
BLUE		=	\033[7;49;34m
RED			=	\x1B[31m
YELLOW		=	\x1B[33m
GREEN		=	\033[0;49;32m
GREEN_BG	=	\033[1;49;32m
GRAY		=	\033[7;49;90m
NO_COLOR	=	\033[m

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	@printf "\r$(GREEN)[$(PROJECT)] Obj compilation done.                                                  \n"
	@printf "$(YELLOW)[$(PROJECT)] Compiling $(NAME)..."
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "\r$(GREEN)[$(PROJECT)] $(NAME) compiled.                                           \n$(NO_COLOR)"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@printf "$(YELLOW)\r[$(PROJECT)] Compiling $< to $@                                                       \r"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR):
	@mkdir $(OBJDIR)

clean:
	@printf "$(YELLOW)[$(PROJECT)] Removing obj..."
	@rm -rf $(OBJ)
	@rm -rf $(OBJDIR)
	@printf "\r$(GREEN)[$(PROJECT)] Obj removed.                                                \n$(NO_COLOR)"

fclean: clean
	@printf "$(YELLOW)[$(PROJECT)] Removing $(NAME)..."
	@rm -rf $(NAME)
	@printf "\r$(GREEN)[$(PROJECT)] $(NAME) removed.                                            \n$(NO_COLOR)"

re: fclean all

.PHONY: all clean fclean re
