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
LIBS		=	-lncurses $(LFTDIR)/libft.a -lreadline -L/opt/homebrew/opt/readline/lib
INCS		=	-I $(LFTDIR) -I $(INCDIR) -I/opt/homebrew/opt/readline/include

SRCS		=	$(SRCDIR)/core/main.c \
				$(SRCDIR)/core/lexer/lexer.c \
				$(SRCDIR)/core/lexer/deque.c \
				$(SRCDIR)/core/lexer/free_struct.c \
				$(SRCDIR)/core/lexer/token.c
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