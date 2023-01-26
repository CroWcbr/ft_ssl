NAME		=	ft_ssl

CC			=	gcc
FLAGS		=	#-Wall -Wextra -Werror

LIBFT_DIR	=	./libft
LIBFT_LIB	=	libft.a

HEADER		=	ft_ssl.h \
				md5.h \
				sha256.h \
				sha512.h

SRC			=	ft_ssl.c \
				ft_ssl_read_hash_file.c \
				ft_ssl_help.c \
				parsing.c \
				parsing_argv.c \
				parsing_print.c \
				md5.c \
				md5_algorithm.c \
				sha256.c \
				sha512.c \
				whirlpool.c

OBJ_DIR		=	obj
OBJ 		=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

RM_DIR		=	rm -rf
RM_FILE		=	rm -f

INCLUDES	= 	-I .

${NAME}:	${OBJ}
			@make -C ${LIBFT_DIR}/ all
			@$(CC) -o $(NAME) $(OBJ) $(FLAGS) ${LIBFT_DIR}/${LIBFT_LIB}
			@echo "\tCompiling...\t" [ $(NAME) ] $(SUCCESS)
									
$(OBJ)		:	| $(OBJ_DIR)

$(OBJ_DIR):
			@mkdir -p $(OBJ_DIR)
			
$(OBJ_DIR)/%.o :	%.c $(HEADER) Makefile
					@${CC} $(FLAGS) $(INCLUDES) -o $@ -c $<

#COLORS
C_NO="\033[00m"
C_OK="\033[32m"
C_GOOD="\033[32m"

#DEBUG
SUCCESS		=	$(C_GOOD)SUCCESS$(C_NO)
OK			=	$(C_OK)OK$(C_NO)
			
all:	$(NAME)

clean:
		@make -C ${LIBFT_DIR}/ clean
		@${RM_DIR} ${OBJ_DIR}
		@echo "\tCleaning...\t" [ $(NAME) ] $(OK)
		
fclean:	clean
		@${RM_FILE} $(LIBFT_DIR)/$(LIBFT_LIB)
		@echo "\tDeleting...\t" [ $(LIBFT_LIB) ] $(OK)
		@${RM_FILE} $(NAME)
		@echo "\tDeleting...\t" [ $(NAME) ] $(OK)
		
re:		fclean all

.PHONY: all clean fclean re
