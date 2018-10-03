NAME				=	ft_ssl

CC					=	gcc
CC_FLAGS			=	-Wall -Werror -Wextra -g -o0

SRC_PATH			=	./srcs/
HASH_PATH			=	$(SRC_PATH)hash/
CIPHER_PATH			=	$(SRC_PATH)cipher/

INC_PATH			=	./includes/ $(LIBFTPRINTF_PATH)includes/ $(LIBFT_PATH)includes/
OBJ_PATH			=	./obj/
LIBFTPRINTF_PATH	=	./libftprintf/
LIBFT_PATH			=	$(LIBFTPRINTF_PATH)/libft/

OBJ					=	$(addprefix $(OBJ_PATH),$(OBJ_NAME))

INC					=	$(addprefix -I, $(INC_PATH))

OBJ_NAME			=	$(SRC_NAME:.c=.o)
OBJ_NAME			+=	$(HASH_NAME:.c=.o)
OBJ_NAME			+=	$(CIPHER_NAME:.c=.o)

HASH_NAME			=	utils.c					\
						proceed_chunk_md5.c		\
						proceed_chunk_sha2.c	\
						ft_hash.c				\
						initialize_vars.c		\
						create_padded_msg.c		\
						proceed_chunk_sha512.c	\
						ft_print_hash.c			\
						ft_print_hash2.c		\
						hash_arg.c

SRC_NAME			=	main.c					\
						get_msg_from_file.c		\
						get_cmd.c				\
						append_flag.c			\
						
CIPHER_NAME			=	encode_to_base64.c		\
						decode_from_base64.c	\
						print_base64_code.c		\
						get_pwd.c				\
						initial_shuffle.c		\
						des_cbc.c

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFTPRINTF_PATH)
	@$(CC) -o $(NAME) $(OBJ) $(LIBFTPRINTF_PATH)libftprintf.a -lbsd
	@echo "Compiling" [ $(NAME) ]

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CC_FLAGS) -o $@ -c $< $(INC) #-lbsd
	@echo "Linking" [ $< ]

$(OBJ_PATH)%.o: $(HASH_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CC_FLAGS) -o $@ -c $< $(INC) #-lbsd
	@echo "Linking" [ $< ]

$(OBJ_PATH)%.o: $(CIPHER_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CC_FLAGS) -o $@ -c $< $(INC) #-lbsd
	@echo "Linking" [ $< ]

clean:
	@make -C $(LIBFTPRINTF_PATH) clean
	@rm -rf $(OBJ_PATH)
	@echo "Cleaning obj [ $(NAME) ]..."

fclean: clean
	@rm -f $(NAME)
	@echo "Remove [ $(NAME) ]..."

re: fclean all

