#------Program Name-----#
NAME = minishell
ARCH = $(shell uname -m)
PWD = $(shell pwd)

#------Header-------#
HEADER = -I ./includes/ -I $(READLINE_INC_DIR)

#----Directories-----#
OBJ_DIR = ./obj/
LIBFT_DIR = ./libft/

#-----Path-------#
LIBFT_PATH = ./libft/libft.a
MINISHELL_PATH = $(OBJ_DIR)libft.a

#----Readline----#
READLINE_URL = https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
READLINE_TAR_FILE = readline-8.2.tar.gz
READLINE_SRC_DIR = readline-8.2/
READLINE_DIR = readline/$(ARCH)/
READLINE_LIB_DIR = $(READLINE_DIR)/lib
READLINE_LIB = $(READLINE_LIB_DIR)/libreadline.a
READLINE_INC_DIR = $(READLINE_DIR)/include
RLLIB = -L $(READLINE_LIB_DIR)

#------Command-------#
CC = gcc
CFLAGS = -Werror -Wextra -Wall
RLFLAGS = -lreadline -lncurses
FSAN = -fsanitize=address -g3
LEAKS = Leaks --atExit --
RM = rm -rf
AR = ar rcs

#-----Files-----#
SRC_FILES = driver/minishell.c \
            driver/envp.c \
            checkers/char_check_1.c \
            checkers/char_check_2.c \
            checkers/char_check_3.c \
            checkers/char_check_4.c \
            checkers/char_check_5.c \
            checkers/char_check_6.c \
            checkers/char_check_7.c \
            readinput/read_input.c \
            builtins/ft_echo.c \
            builtins/ft_pwd.c \
            builtins/ft_cd.c \
            builtins/ft_cd_utils.c \
            builtins/ft_env.c \
            builtins/ft_exit_utils.c \
            builtins/ft_exit.c \
            builtins/ft_export_utils_1.c \
            builtins/ft_export_utils_2.c \
            builtins/ft_export.c \
            builtins/ft_unset.c \
            heredoc/handle_heredoc.c \
            heredoc/handle_heredoc_utils.c \
            exit_status/exit_status.c \
            signals/signal.c \
            execution/evaluate_tokenlist.c \
            execution/execute_cmd.c \
            execution/exec_cmd_utils.c \
            execution/exec_cmd_utils2.c \
            execution/exec_cmd_utils3.c \
            execve/ft_execve.c \
            execve/ft_execve_utils.c \
            processing/tokenization/get_next_token.c \
            processing/tokenization/get_tokenlist.c \
            processing/tokenization/get_tokenlist_utils.c \
            processing/env_expansion/expand_env.c \
            processing/env_expansion/expand_env_utils_1.c \
            processing/env_expansion/expand_env_utils_2.c \
            processing/token_sanitization/sanitize_token.c \

OBJ_FILES = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

#----Rules & Dependencies-----#
all: execlib execrd $(NAME)

$(NAME): $(OBJ_FILES)
	@cp $(LIBFT_PATH) $(OBJ_DIR)
	@$(AR) $(MINISHELL_PATH) $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(HEADER) $(MINISHELL_PATH) $(RLLIB) $(RLFLAGS) -o $(NAME)

clean:
	@make -s fclean -C $(LIBFT_DIR)
	@$(RM) $(MINISHELL_PATH)
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(MINISHELL_PATH)

re: fclean all

execlib:
	@make -s -C $(LIBFT_DIR)

execrd:
	@curl -O "$(READLINE_URL)"
	@tar -xzf $(READLINE_TAR_FILE)
	@rm -rf $(READLINE_TAR_FILE)
	@cd $(READLINE_SRC_DIR) && ./configure "--prefix=$(PWD)/$(READLINE_DIR)" \
	&& make && make install && cd ..
	@rm -rf $(READLINE_SRC_DIR)
	@echo "#include <stdio.h>\n" > .tmp
	@cat $(READLINE_INC_DIR)/readline/readline.h >> .tmp
	@mv .tmp $(READLINE_INC_DIR)/readline/readline.h

clean_readline:
	@rm -rf readline/
	@rm -rf $(READLINE_SRC_DIR)

# Compile each .c file into .o files in the OBJ_DIR, creating necessary directories
$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)    # Create the directory for the object file if it doesn't exist
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

.PHONY: all clean fclean re execlib execrd clean_readline
