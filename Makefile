CC = cc
FLAGS = -Wall -Wextra -Werror
SAN = -fsanitize=address -g
LFLAGS = -lreadline

TARGET = minishell
SRCS = ft_split.c built_in.c built_in_envs.c built_in_export.c environmentals_helpers.c environmentals_operators_0.c environmentals_operators_1.c executor.c executor_bin.c executor_command.c executor_connector.c executor_redirection.c expander.c ft_atoi.c input_handler.c main.c parser_ast.c parser_ast_free.c parser_ast_helpers_0.c parser_ast_helpers_1.c parser_ast_helpers_2.c parser_stack_helpers_3.c parser_stack_ops.c signals.c strings_0.c strings_1.c tokenizer.c tokenizer_handlers_0.c utilities_0.c utilities_1.c ./minishell_debug/debug_minishell.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) $(SAN) -o $(TARGET) $(OBJS) $(LFLAGS)

%.o: %.c
	$(CC) $(FLAGS) $(SAN) -c $< -o $@ $(LFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all
