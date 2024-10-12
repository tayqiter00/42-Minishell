# Directories
OBJDIR = objs/
SRC_FILES = driver/minishell.c \
            processing/tokenization/get_next_token.c \
            processing/tokenization/get_tokenlist.c \
            checkers/char_check_1.c \
            checkers/char_check_2.c \
            checkers/char_check_3.c \
            checkers/char_check_4.c \
            checkers/char_check_5.c \
            checkers/char_check_6.c \
            libft/ft_strspn.c \
            libft/ft_strlen.c \
            libft/ft_strncmp.c \
            libft/ft_strdup.c \
            libft/ft_substr.c \
            libft/ft_strchr.c \
            libft/ft_strcmp.c \
            libft/ft_bzero.c \
            libft/ft_isalnum.c \
            libft/ft_strjoin.c \
            libft/ft_itoa.c \
            libft/ft_memcpy.c \
            libft/ft_strndup.c \
            libft/ft_strcspn.c \
            libft/ft_strlcpy.c \
            libft/ft_strtok.c \
            libft/ft_atoi.c \
            readinput/read_input.c \
            processing/env_expansion/expand_env.c \
            processing/env_expansion/expand_env_utils_1.c \
            processing/env_expansion/expand_env_utils_2.c \
            processing/token_sanitization/sanitize_token.c \
            builtins/ft_echo.c \
            builtins/ft_pwd.c \
            builtins/ft_cd.c \
            builtins/ft_env.c \
            builtins/ft_exit_utils.c \
            builtins/ft_exit.c \
            builtins/ft_export_utils_1.c \
            builtins/ft_export_utils_2.c \
            builtins/ft_export.c \
            builtins/ft_unset.c \
            heredoc/handle_heredoc.c \
            exit_status/exit_status.c \
            driver/envp.c \
            signals/signal.c \
            execution/evaluate_tokenlist.c \
            execution/execute_cmd.c \
            execution/exec_cmd_utils.c \
            execution/exec_cmd_utils2.c \
            execution/exec_cmd_utils3.c \

# Define object files path
OBJS = $(patsubst %.c, $(OBJDIR)%.o, $(SRC_FILES))

# Compilation flags
# -Wall -Wextra -Werror
FLAGS = 

MINISHELL = minishell
NAME = $(MINISHELL)

# Rules
all: $(OBJDIR) $(NAME)

# Create the object directory
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Compile .c to .o files
$(OBJDIR)%.o: %.c
	@mkdir -p $(dir $@)  
	$(CC) $(FLAGS) -c $< -o $@

# Build the final executable
$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -lreadline

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
