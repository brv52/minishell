# Minishell — Unix-like Shell Implementation in C

A production-style command-line shell built in C to replicate the core behavior of a Unix terminal. This project demonstrates command parsing, process execution, redirection handling, environment management, and signal-aware interaction in a modular, low-level systems design.

This project is built for technical hiring and portfolio review: it highlights the ability to work with POSIX APIs, process control, shell semantics, and reliable C code structure under real system constraints.

---

## Project Overview

Minishell is a simplified implementation of a Linux shell designed to handle interactive command execution with the same foundational behavior expected from a Unix shell. The application reads user input, tokenizes commands, parses operators and precedence, constructs an execution tree, and runs commands with proper file descriptor redirection and exit status management.

### Key capabilities

- Interactive terminal input using `readline`
- Lexing and tokenization of shell syntax
- Recursive-descent / stack-based AST parsing for command operators
- Support for built-ins such as `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`
- Pipeline execution with `|`
- Redirection support for `<`, `>`, `>>`, and `<<`
- Logical operators `&&` and `||`
- Custom environment variable map with hash-based storage
- Signal handling for terminal interrupt behavior
- Runtime status tracking for commands and shell state

### Why this project matters

This is a strong systems engineering project because it requires understanding of the operating system at a deep level:

- process creation and life cycles
- file descriptor manipulation
- shell parsing and execution semantics
- memory ownership and cleanup in C
- signal-driven interactive behavior

It is particularly relevant for backend, systems, infrastructure, and low-level software roles.

---

## Architecture and Technical Implementation

### 1. Shell execution model

The shell follows the standard Unix command execution flow:

1. Read input from the terminal
2. Tokenize the command string
3. Parse tokens into an AST
4. Execute the tree according to operator precedence and semantics
5. Manage process lifecycle and exit codes

The main loop is implemented in `main.c`, where the shell maintains runtime state and continuously accepts commands until the user exits.

### 2. Tokenization and parsing

The tokenizer converts raw user input into structured tokens such as:

- command words
- operators (`|`, `||`, `&&`, `<`, `>`, `>>`, `<<`)
- parentheses for grouped command flow

The parser builds an AST in `parser_ast.c`, with node types for:

- `COMMAND` nodes that carry argv-style arguments
- `OPERATOR` nodes that represent expressions such as pipes and redirections

This representation enables a clean and extensible execution pipeline rather than ad hoc command execution.

### 3. Execution engine

The executor layer is responsible for dispatching commands based on the parsed tree:

- `executor.c` selects the correct execution path
- `executor_command.c` handles command execution
- `executor_connector.c` manages `|`, `&&`, and `||`
- `executor_redirection.c` handles input/output file redirection and heredoc behavior

The design uses the standard POSIX process model:

- `fork()` for child processes
- `pipe()` for inter-process communication
- `dup2()` for stdin/stdout redirection
- `waitpid()` to wait for process completion

This creates a real shell execution flow rather than a mock or simulated parser.

### 4. Built-in commands and environment management

Built-ins are implemented in `built_in.c` and the environment is managed by a custom hash-map implementation in the `environmentals_*` files.

Supported built-ins include:

- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

The environment model stores shell variables and status information while preserving command exit state between iterations.

### 5. Signal handling

Signal handling is implemented in `signals.c` and `signal_handler.h` to maintain interactive shell behavior when the user sends interrupts. The shell suppresses or handles signals appropriately during pipeline execution, ensuring it behaves like a real terminal application.

### 6. I/O and runtime characteristics

This project does not use sockets, Docker orchestration, or event-loop networking. It is a local CLI application built on Unix process and file-descriptor primitives. The runtime is synchronous and blocking by design, which is appropriate for a shell implementation and consistent with Unix shell semantics.

In practical terms, the project demonstrates:

- C system programming skills
- command-line application architecture
- POSIX process coordination
- low-level resource management
- correct error handling under terminal and process conditions

---

## Prerequisites

This project targets a Linux environment and requires:

- GCC or Clang
- GNU Make
- `readline` development library
- Standard Unix tooling

Install dependencies on Debian/Ubuntu:

```bash
sudo apt-get update
sudo apt-get install -y build-essential libreadline-dev
```

On macOS (Homebrew):

```bash
brew install readline
```

---

## Build Instructions

The project includes a Makefile for building the shell:

```bash
make
```

Run the resulting binary:

```bash
./minishell
```

Useful maintenance commands:

```bash
make clean
make fclean
make re
```

The Makefile compiles with strict warning settings and includes AddressSanitizer support for debugging and validation.

---

## Usage Examples

### Basic commands

```bash
echo hello
pwd
ls -l
```

### Environment variables

```bash
export USER=student
env
unset USER
```

### Pipes

```bash
ls -l | grep src
cat file.txt | wc -l
```

### Redirection

```bash
cat < input.txt > output.txt
printf "hello\n" >> log.txt
```

### Heredoc

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

### Built-ins

```bash
cd /tmp
pwd
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
├── script.sh
└── minishell_debug/
```

---

## Skills Demonstrated

- C programming and memory management
- Unix/Linux system programming
- Process control and inter-process communication
- Shell parsing and execution semantics
- Redirection and file-descriptor handling
- API design and modular software architecture
- Defensive programming and error handling
- Signal-aware application behavior

---

## Summary for Recruiters

This project showcases the ability to build a real-world, low-level system application in C, with strong emphasis on process orchestration, shell behavior, and operating system interfaces. It is a strong candidate project for roles involving backend systems, infrastructure engineering, low-level software, CLI tooling, and Unix/Linux development.
