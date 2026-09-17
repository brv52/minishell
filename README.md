# Minishell

A compact, Unix-like shell implementation written in C. This project recreates the core flow of an interactive terminal: reading user input, tokenizing commands, parsing operator precedence, executing commands with process isolation, and managing shell state such as environment variables and signals.

It is designed as a systems programming project focused on low-level process execution, file descriptor manipulation, and shell semantics rather than a full desktop application or network service.

---

## 1. Project Overview

This repository implements a simplified command-line shell that supports:

- Interactive input handling through the readline library
- Lexical tokenization of commands and operators
- Parsing into an abstract syntax tree (AST)
- Execution of external binaries and built-in commands
- Pipelines and redirection operators
- Environment variable management
- Signal handling for interactive shell behavior
- Exit status tracking for command execution

The project follows the classic Unix shell model:

1. Read a command from the user
2. Tokenize it into a structured stream
3. Build an execution tree
4. Fork child processes when needed
5. Redirect file descriptors
6. Wait for completion and propagate exit status

This is a strong systems-programming project demonstrating process control, C memory management, UNIX APIs, and shell parser/executor fundamentals.

### Core features

- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Operators: `|`, `&&`, `||`, `<`, `>`, `>>`, `<<`
- Parent-shell state tracking with a custom environment map
- AST-driven execution model instead of ad hoc command execution
- Clean error handling for malformed input and redirection failures

---

## 2. Core Architecture & Technical Implementation

### High-level execution flow

The project is organized around a standard shell pipeline:

- `main.c` initializes the shell state and runs the main REPL loop
- `input_handler.c` reads commands from the user
- `tokenizer.c` converts raw input into `t_token` values
- `parser_ast.c` and related parser files build a tree of commands and operators
- `executor.c`, `executor_connector.c`, and `executor_redirection.c` execute the parsed AST
- `built_in.c` and `environmentals_*` manage shell built-ins and environment variables
- `signals.c` installs handlers for interactive signal behavior

### Data and execution model

The shell state is represented by a `t_shell_data` structure in `minishell.h`, containing:

- the current prompt string
- the token list for the current command
- the parsed AST tree
- the environment table

This design keeps the shell state explicit and modular while allowing parsing and execution to operate on a structured command tree.

### Parsing and command representation

The parser uses a stack-based AST construction approach. Command nodes and operator nodes are represented in `parser.h` with a tagged union:

- `COMMAND` nodes hold argv-style arguments and type metadata
- `OPERATOR` nodes hold the operation (`PIPE`, `AND`, `OR`, redirections, etc.) and left/right subtrees

This allows nesting expressions like pipelines and redirections into a single executable tree, providing a clean execution model that mirrors shell syntax.

### Process execution

Execution is process-centric and uses the POSIX API heavily:

- `fork()` to create child processes
- `pipe()` for inter-process communication
- `dup2()` to remap stdin/stdout
- `waitpid()` to synchronize child completion
- `execve()`-style child execution semantics through shell command resolution

This design matches the behavior expected from a Unix shell: each stage of a pipeline can execute independently while preserving the intended command flow.

### Redirection and file-descriptor handling

The shell supports common redirections using file descriptors and `open()` calls:

- input redirection with `<`
- output redirection with `>`
- append mode with `>>`
- heredoc-style input with `<<`

The executor preserves original standard file descriptors with `dup()`, applies redirections, runs the command, and restores the terminal state afterward. This ensures the shell remains stable across command execution.

### Environment management

Environment variables are stored in a custom hash map implementation (`environmentals.h`, `environmentals_helpers.c`, `environmentals_operators_*.c`). The shell tracks key/value pairs in a bucketed structure, exposes lookup and mutation functions, and stores shell status information like the last exit code.

### Signal handling

The shell registers signal handlers for interactive control flow using `sigaction()` and `signal()`. The code handles the terminal interrupt semantics for patterns such as Ctrl+C and child-process propagation in pipelines.

### I/O and runtime model

This project is not a networked service and does not use sockets or Docker orchestration. The runtime model is a local CLI shell built on POSIX process control, file-descriptor redirection, and blocking terminal I/O. In other words, it is a process-driven, single-host command interpreter rather than a non-blocking server, socket-based daemon, or container runtime.

The execution model is intentionally synchronous and process-oriented:

- commands are read from a terminal
- execution waits for child completion before continuing
- pipelines and redirections are represented as OS-level data flow rather than callback-based event loops

This is a traditional Unix shell architecture, which is appropriate for systems-level learning and interview-ready demonstration.

---

## 3. Prerequisites & Build Instructions

### Prerequisites

The project is intended for a Linux environment and requires:

- GCC or Clang
- GNU Make
- `readline` development library
- Standard POSIX build tools

On Debian/Ubuntu-based systems:

```bash
sudo apt-get update
sudo apt-get install -y build-essential libreadline-dev
```

On macOS with Homebrew:

```bash
brew install readline
```

### Build with the provided Makefile

The repository includes a Makefile that builds the shell binary:

```bash
make
```

This compiles the project with warnings enabled and also includes AddressSanitizer instrumentation for debugging:

```bash
CC = cc
FLAGS = -Wall -Wextra -Werror
SAN = -fsanitize=address -g
LFLAGS = -lreadline
```

To remove object files:

```bash
make clean
```

To remove the built binary and objects:

```bash
make fclean
```

To rebuild from a clean state:

```bash
make re
```

### Run the shell

```bash
./minishell
```

---

## 4. Usage Examples

Once the shell is running, you can use commands similar to a regular Unix shell:

### Basic execution

```bash
echo hello
pwd
ls -l
```

### Environment and shell state

```bash
export USER=student
env
unset USER
echo $USER
```

### Pipelines

```bash
ls -l | grep src
cat file.txt | wc -l
```

### Redirection

```bash
cat < input.txt > output.txt
printf "hello\n" >> log.txt
```

### Heredoc input

```bash
cat << EOF
hello from minishell
EOF
```

### Logical operators

```bash
false && echo "won't run"
true || echo "this will run"
```

### Built-in shell commands

```bash
pwd
cd /tmp
echo hello
exit
```

---

## Project Structure

```text
.
├── built_in.c
├── built_in_envs.c
├── built_in_export.c
├── environmentals_helpers.c
├── environmentals_operators_0.c
├── environmentals_operators_1.c
├── executor.c
├── executor_bin.c
├── executor_command.c
├── executor_connector.c
├── executor_redirection.c
├── expander.c
├── input_handler.c
├── main.c
├── parser_ast.c
├── parser_ast_helpers_0.c
├── parser_ast_helpers_1.c
├── parser_ast_helpers_2.c
├── parser_stack_ops.c
├── parser_stack_helpers_3.c
├── signals.c
├── tokenizer.c
├── tokenizer_handlers_0.c
├── utilities_0.c
├── utilities_1.c
├── minishell.h
├── parser.h
├── executor.h
├── environmentals.h
├── built_in.h
├── signal_handler.h
├── README.md
├── Makefile
└── minishell_debug/
```

---

## Notes

This implementation is intentionally focused on the core mechanics of a shell and is best viewed as a professional systems-programming exercise. It demonstrates solid C engineering principles, robust memory handling, process orchestration, and shell behavior modeling without depending on external frameworks or container infrastructure.

Designed to be clean, modular, and interview-friendly, the project is suitable for showcasing low-level Unix systems expertise and command-line application architecture.
