# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lade-kon <lade-kon@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/05/15 19:29:55 by lade-kon      #+#    #+#                  #
#    Updated: 2024/05/24 14:19:10 by lade-kon      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SERVER			:=	server
CLIENT			:=	client

CC				:=	cc
CFLAGS			:=	-Wall -Werror -Wextra #-g -fsanitize=address

LIBFT_DIR		:=	lib/libft
LIBFT_A			:=	$(LIBFT_DIR)/libft.a

INCLS_MINITALK	:=	incl
INCLS_LIBFT		:=	$(LIBFT_DIR)/incl
INCLUDES		:=	-I $(INCLS_MINITALK) -I $(INCLS_LIBFT)

SRC_DIR			:=	src

SRC_FILE_SERVER	:=	server.c
SRC_FILE_CLIENT	:=	client.c
SRC_FILE_MAIN	:=	main.c

SRC_SERVER		:=	$(addprefix $(SRC_DIR)/, $(SRC_FILE_SERVER))
SRC_CLIENT		:=	$(addprefix $(SRC_DIR)/, $(SRC_FILE_CLIENT))
SRC_MAIN		:=	$(addprefix $(SRC_DIR)/, $(SRC_FILE_MAIN))

OBJ_DIR			:=	obj
OBJ_FILE_SERVER	:=	$(SRC_SERVER:.c=.o)
OBJ_FILE_CLIENT	:=	$(SRC_CLIENT:.c=.o)
OBJ_FILE_MAIN	:=	$(SRC_MAIN:.c=.o)
OBJ_SERVER		:=	$(addprefix $(OBJ_DIR)/, $(OBJ_FILE_SERVER))
OBJ_CLIENT		:=	$(addprefix $(OBJ_DIR)/, $(OBJ_FILE_CLIENT))
OBJ_MAIN		:=	$(addprefix $(OBJ_DIR)/, $(OBJ_FILE_MAIN))


all: $(SERVER) $(CLIENT)

$(LIBFT_A):
	@git submodule update --init --recursive --remote
	@make -C $(LIBFT_DIR) > /dev/null

$(SERVER): $(OBJ_SERVER) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(INCLUDES) $(LIBFT_A) -o $(SERVER)

$(CLIENT): $(OBJ_CLIENT) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(INCLUDES) $(LIBFT_A) -o $(CLIENT)

main: $(OBJ_MAIN) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ_MAIN) $(INCLUDES) $(LIBFT_A) -o main

$(OBJ_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)/$(SRC_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

norminette:
	@echo "${CYAN}🧐 Checking the Norm...${RESET}"
	@norminette -R CheckForbiddenSourceHeader
	@echo "${GREEN} Norm-i-netting complete. Files are NORM PROOF!${RESET}" 

update:
	@git submodule update --init --recursive --remote

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean > /dev/null

fclean: clean
	@rm -f $(SERVER)
	@rm -f $(CLIENT)
	@make -C $(LIBFT_DIR) fclean > /dev/null

re: fclean all

## Colours ##
RESET	:= \033[0m
RED		:= \033[1;91m
GREEN	:= \033[1;92m
YELLOW	:= \033[1;93m
BLUE	:= \033[1;94m
PURPLE	:= \033[1;95m
CYAN	:= \033[1;96m
WHITE	:= \033[1;97m
BLACK	:= \033[1;90m