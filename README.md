# Minishell - 42 Barcelona

Minishell is a major systems programming project from the 42 Barcelona curriculum. The goal is to build an interactive UNIX command-line interpreter in C modeled after GNU Bash. Minishell explores low-level operating system concepts including process creation and lifecycle (fork, execve, waitpid), inter-process communication using pipes, file descriptor manipulation with dup2, signal interception (SIGINT, SIGQUIT), abstract syntax tree parsing, environment variable resolution, and interactive line editing via the GNU Readline library.

# Prerequisites

To compile and execute Minishell, you will need:

- A C compiler: gcc or clang
- GNU Make
- The GNU Readline development library (libreadline)

### macOS Setup

Install Readline using Homebrew:
```bash
brew install readline
```

If your compiler does not find Readline headers automatically on Apple Silicon or Intel Macs, export the appropriate flags:
```bash
export CPATH="$(brew --prefix readline)/include:$CPATH"
export LIBRARY_PATH="$(brew --prefix readline)/lib:$LIBRARY_PATH"
```

### Linux (Debian / Ubuntu) Setup

Install dependencies via apt:
```bash
sudo apt update
sudo apt install build-essential libreadline-dev
```

# Configuration

1. Clone the repository:
```bash
git clone https://github.com/adrmarqu/minishell.git
cd minishell
```

No external configuration files are needed. Minishell inherits your current operating system environment variables upon launch.

# Execution

### Compilation

Compile the bundled libft library and the minishell binary:
```bash
make
```

### Launching the Shell

Start Minishell interactively:
```bash
./minishell
```

### Exiting the Shell

Exit the interactive session at any time by running the built-in exit command or pressing Ctrl-D on an empty prompt line:
```bash
minishell$ exit
```

# Project Structure

```
minishell/
├── Makefile                 # Build orchestration for Minishell and bundled Libft
├── en.subject.pdf           # 42 School official project specification
├── inc/                     # Header files
│   ├── minishell.h          # Core structures, tokens, and data models
│   ├── builtins.h           # Declarations for internal shell commands
│   ├── parser.h             # Lexer, tokenizer, and grammar validation
│   ├── executor.h           # Process spawning, pipes, and file redirections
│   └── signals.h            # Signal handlers across prompt and child contexts
├── libft/                   # Bundled custom C utility library
└── srcs/                    # Implementation modules
    ├── main.c               # REPL loop and prompt listener
    ├── builtins/            # echo, cd, pwd, export, unset, env, and exit
    ├── parser/              # Tokenization, quote parsing, syntax tree generation
    ├── executor/            # Execution pipeline, command lookup, fork/exec/wait
    ├── redirections/        # File descriptor redirection (<, >, >>, << heredoc)
    ├── env/                 # Environment table manipulation and expansion ($VAR, $?)
    └── signals/             # Ctrl-C, Ctrl-D, and Ctrl-\ handling
```

# Commands and Makefile Targets

- make or make all: Compiles the bundled Libft library and links the minishell executable
- make clean: Deletes all object files (.o) and dependency files (.d)
- make fclean: Runs clean and removes the compiled minishell binary and libft.a
- make re: Rebuilds the entire project from scratch

# Shell Features

- Interactive Prompt and History: Displays a prompt, parses inputs, and navigates command history using up and down arrow keys.
- Command Search: Searches executables through the system PATH or directly through relative (./prog) and absolute (/bin/ls) paths.
- Built-in Commands:
  - echo: Prints arguments with optional -n flag to suppress trailing newlines
  - cd: Changes the working directory (supports relative, absolute, ~, and HOME fallback)
  - pwd: Prints the current working directory path
  - export: Sets environment variables and lists exported variables in alphabetical order
  - unset: Unsets specified environment variables
  - env: Prints all exported environment variables
  - exit: Terminates the shell with an optional integer exit status
- Redirections:
  - <: Redirects standard input from a file
  - >: Redirects standard output to a file, truncating existing content
  - >>: Redirects standard output in append mode
  - <<: Here-document, buffering input until a specific delimiter token is entered
- Pipes:
  - |: Chains multiple commands together, routing stdout of each command into stdin of the next
- Expansion:
  - $VAR: Expands to the value of the environment variable
  - $?: Expands to the exit code of the most recently executed pipeline
- Signals:
  - Ctrl-C: Emits a newline and displays a clean prompt (cancels running heredoc or process)
  - Ctrl-D: Sends EOF, exiting the shell or terminating here-document input
  - Ctrl-\: Ignored during interactive prompt mode, mimicking Bash behavior
- Bonus Capabilities:
  - Logical operators && (AND) and || (OR) with parenthesis priority parsing
  - Wildcard pattern expansion (*) matching files within the current directory

# Author Details

Author: Adrià Márquez Nebot
Github: https://github.com/adrmarqu
LinkedIn: https://www.linkedin.com/in/adria-marquez
Portfolio: https://adrmarqu.github.io
