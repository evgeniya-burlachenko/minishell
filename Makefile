NAME	= 	minishell

SRC_FOLDER = ./srcs/
HEADER_FOLDER = ./includes/
LIBFT_FOLDER = ./libft/
READLINE_FOLDER = $(shell brew --prefix readline)/lib/
HEADER_READLINE_FOLDER = $(shell brew --prefix readline)/include/

SRC_LIST = \
minishell.c \
z_array/z_array.c \
z_array/z_array_utils.c \
utls/utls_print_error.c \
utls/utls_ft.c \
utls/utls_ft_2.c \
utls/utls_ft_3.c \
utls/utls_keys.c \
utls/utls_redirect.c \
utls/utls_redirect_files.c\
utls/utls_redirect_heredoc.c\
utls/utls_redirect_dup.c\
utls/utls_minishell.c \
utls/utls_parser.c \
utls/utls_preparser_tests.c \
utls/utls_export.c \
utls/utls_debug.c \
utls/utls_others.c \
utls/utls_signal.c \
builtins/_cd.c \
builtins/_echo.c \
builtins/_env.c \
builtins/_exit.c \
builtins/_export.c \
builtins/_pwd.c \
builtins/_unset.c \
builtins/_others.c \
moduls/signal.c \
moduls/runner.c \
errors/fork_errors.c \
parser/_parse.c \
parser/_symb.c \
parser/_quote.c \
parser/_tilda_red1.c \
parser/_tilda_red2.c \

HEADER_LIST = \
minishell.h \
z_array.h \
errors.h

SRCS = $(addprefix $(SRC_FOLDER), $(SRC_LIST))
HEADERS = $(addprefix $(HEADER_FOLDER), $(HEADER_LIST))

LIBFT= $(LIBFT_FOLDER)libft.a

OTHER_DEPEND = \
Makefile

OBJS	=	$(SRCS:.c=.o)
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror 
RM		=	rm -f 

ALL_LIBS	= \
-L $(READLINE_FOLDER) -lreadline \
-L $(LIBFT_FOLDER) -lft
ALL_HEADERS = \
-I $(HEADER_READLINE_FOLDER) \
-I $(LIBFT_FOLDER) \
-I $(HEADER_FOLDER)

all:	$(NAME)

$(LIBFT): libft ;

%.o:	%.c
	$(CC) -c $(CFLAGS) $(ALL_HEADERS) $< -o $@

$(NAME):	$(LIBFT) $(OTHER_DEPEND) $(OBJS) $(HEADERS) 
	$(CC) $(CFLAGS) $(OBJS) $(ALL_LIBS) $(ALL_HEADERS) -o $(NAME)

libft:
	@make -C $(LIBFT_FOLDER)

clean:
	@$(RM) $(OBJS)
	@make -C libft clean

fclean:	clean
	@$(RM) $(NAME)
	@make -C libft fclean

re:	fclean $(NAME)

.PHONY:	all libft clean fclean re