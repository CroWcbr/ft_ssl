NAME		=	ft_ssl

CC			=	gcc
FLAGS		=	#-Wall -Wextra -Werror

INCLUDE		= 	include/
LIBFT_DIR	=	./libft
SRC_DIR		=	src
OBJ_DIR		=	obj

LIBFT_LIB	=	libft.a

SRC			=	ft_ssl.c \
				ft_ssl_read_hash_file.c \
				ft_ssl_help.c \
				parsing/parsing.c \
				parsing/parsing_argv.c \
				parsing/parsing_print.c \
				md5/md5.c \
				md5/md5_algorithm.c \
				sha256/sha256.c \
				sha256/sha256_algorithm.c \
				sha256/sha256_utily.c \
				sha256/sha256_utily2.c \
				sha512/sha512.c \
				sha512/sha512_algorithm.c \
				sha512/sha512_utily.c \
				sha512/sha512_utily2.c \
				whirlpool/whirlpool.c \
				whirlpool/whirlpool_algorithm.c

OBJ			=	$(SRC:%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				@mkdir -p $(@D)
				$(CC) $(FLAGS) -c -o $@ $< -I $(INCLUDE)

RM_DIR		=	rm -rf
RM_FILE		=	rm -f

#COLORS
C_NO		=	"\033[00m"
C_OK		=	"\033[32m"
C_GOOD		=	"\033[32m"

#DEBUG
SUCCESS		=	$(C_GOOD)SUCCESS$(C_NO)
OK			=	$(C_OK)OK$(C_NO)

all:		$(NAME)

$(NAME):	$(OBJ)
			@make -C ${LIBFT_DIR}/ all
			@$(CC) -o $(NAME) $(FLAGS) -o $@ $^ $(LIBFT_DIR)/$(LIBFT_LIB)
			@echo "\tCompiling...\t" [ $(NAME) ] $(SUCCESS)

clean:
			@make -C ${LIBFT_DIR}/ clean
			@${RM_DIR} ${OBJ_DIR}
			@echo "\tCleaning...\t" [ $(NAME) ] $(OK)

fclean:		clean
			@${RM_FILE} $(LIBFT_DIR)/$(LIBFT_LIB)
			@echo "\tDeleting...\t" [ $(LIBFT_LIB) ] $(OK)
			@${RM_FILE} $(NAME)
			@echo "\tDeleting...\t" [ $(NAME) ] $(OK)

re:			fclean all

.PHONY: all clean fclean re bonus
