# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skelly <skelly@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/04 15:45:13 by skelly            #+#    #+#              #
#    Updated: 2021/12/30 09:31:07 by skelly           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a
HEADER			=	libft.h
FILES		=	ft_memset.c			\
				ft_bzero.c			\
				ft_memcpy.c			\
				ft_memccpy.c		\
				ft_memmove.c		\
				ft_memchr.c			\
				ft_memcmp.c			\
				ft_strlen.c			\
				ft_strlcpy.c		\
				ft_strlcat.c		\
				ft_strncmp.c		\
				ft_strchr.c			\
				ft_strrchr.c		\
				ft_strnstr.c		\
				ft_atoi.c			\
				ft_isalpha.c		\
				ft_isdigit.c		\
				ft_isalnum.c		\
				ft_isascii.c		\
				ft_isprint.c		\
				ft_toupper.c		\
				ft_tolower.c		\
				ft_calloc.c			\
				ft_strdup.c			\
				ft_strjoin.c		\
				ft_strtrim.c		\
				ft_split.c			\
				ft_itoa.c			\
				ft_strmapi.c		\
				ft_substr.c			\
				ft_putchar_fd.c		\
				ft_putstr_fd.c		\
				ft_putendl_fd.c		\
				ft_putnbr_fd.c		\
				ft_malloc_minishell.c

FILES_B = 		ft_lstnew.c			\
				ft_lstadd_front.c	\
				ft_lstsize.c		\
				ft_lstlast.c		\
				ft_lstadd_back.c	\
				ft_lstdelone.c		\
				ft_lstclear.c		\
				ft_lstiter.c		\
				ft_lstmap.c			\
				
OBJS		=	$(patsubst %.c, %.o, $(FILES))

OBJS_B		=	$(patsubst %.c, %.o, $(FILES_B))

CFLAGS			=	-Wall -Wextra -Werror -c -I

RM				=	rm -f

%.o : %.c 
	gcc $(CFLAGS) $(HEADER) $< -o $@

all: $(NAME) 

$(NAME): $(OBJS) $(HEADER) Makefile
	ar rcs $(NAME) $?

bonus: $(OBJS_B)
	ar rcs $(NAME) $?

norm:
	norminette . | grep Error

clean:
	@$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean bonus
