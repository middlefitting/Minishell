NAME		=	minishell
#CMDS
CC			=	cc
RM			=	rm -rf
LIBC		=	ar rcs
#FLAGS
CFLAGS		=	#-Wall -Wextra -Werror
DFLAGS		=	-g3 -fsanitize=address
#DIRS
LFTDIR		=	libft
SRCDIR		=	src
INCDIR		=	./include
LIBS		=	-lncurses $(LFTDIR)/libft.a -lreadline -L /usr/local/opt/readline/lib
INCS		=	-I $(LFTDIR) -I $(INCDIR) -I /usr/local/opt/readline/include

SRCS		=	$(SRCDIR)/core/main.c \
				$(SRCDIR)/core/lexer/lexer.c \
				$(SRCDIR)/core/lexer/deque.c \
				$(SRCDIR)/core/lexer/free_struct.c \
				$(SRCDIR)/core/lexer/token.c \
				$(SRCDIR)/core/lexer/init_data.c \
				$(SRCDIR)/core/envp/envp.c \
				$(SRCDIR)/core/envp/env_utils.c \
				$(SRCDIR)/core/env_parser/env_parser.c \
				$(SRCDIR)/core/exec/check_redir.c \
				$(SRCDIR)/core/exec/close.c \
				$(SRCDIR)/core/exec/exec.c \
				$(SRCDIR)/core/exec/fork_pipe_cmd.c \
				$(SRCDIR)/core/exec/here_doc.c \
				$(SRCDIR)/core/exec/m_builtins1.c \
				$(SRCDIR)/core/exec/m_builtins2.c \
				$(SRCDIR)/core/exec/m_function1.c \
				$(SRCDIR)/core/exec/m_function2.c \
				$(SRCDIR)/core/exec/m_function3.c \
				$(SRCDIR)/core/exec/m_split.c \
				$(SRCDIR)/core/exec/make_path.c \
				$(SRCDIR)/core/exec/free.c \
				$(SRCDIR)/core/signal/signal.c \
				$(SRCDIR)/core/exec/print_error.c \
				$(SRCDIR)/core/builtin/export.c
OBJS		=	${SRCS:.c=.o}

all :
	@$(MAKE) -j6 $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C $(LFTDIR) libft.a
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

clean :
	@$(MAKE) -C $(LFTDIR) fclean
	@$(RM) $(OBJS) $(BOBJS)

fclean : clean
	@$(RM) $(NAME)

re :
	@$(MAKE) fclean
	@$(MAKE) all

rebug	:
	@$(MAKE) fclean
	@$(MAKE) IF_DEBUG=1 all

.PHONY : all clean fclean re


# NAME					=	server

# FILE					=	core/main.c \

# SRC_DIR					=	./src
# SCRS					=	$(addprefix $(SRC_DIR)/, $(FILE))

# OBJ_DIR					=	./obj
# OBJS					=	$(addprefix $(OBJ_DIR)/, $(patsubst %.c,%.o,$(FILE)))

# LIBRARY_DIR				=	./library
# LIB						=	$(LIBRARY_DIR)/minishell.a

# CFLAGS					=	-Wall -Wextra -Werror
# LIBFT					=	libft
# LIBS					=	$(LIBFT)/libft.a -lreadline -L/opt/homebrew/opt/readline/lib
# INCS					=	-I $(LIBFT) -I ./include -I/opt/homebrew/opt/readline/include


# all						: 	$(NAME)

# $(NAME)					:	$(LIB)
# 							cc $(CFLAGS) -o $@ $^


# $(LIB)					:	$(OBJS)
# 							@mkdir -p $(dir $@)
# 							ar rc $@ $^


# $(OBJ_DIR)/%.o			: 	$(SRC_DIR)/%.c
# 							@mkdir -p $(dir $@)
# 							make -C $(LIBFT)
# 							$(CC) $(CFLAGS) $(LIBS) $(INCS) -c $< -o $@ -L $(LIBFT) -lft

# clean					:
# 							rm -rf $(OBJ_DIR) $(LIBRARY_DIR)

# fclean					: 	clean
# 							rm -f $(NAME)

# re						: 	fclean all

# .PHONY					: 	clean fclean all re
