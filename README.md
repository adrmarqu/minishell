*This project has been created as part of the 42 curriculum by adrmarqu.*

# Minishell

## Description

Minishell is a 42 school curriculum project whose goal is to create a simple UNIX command-line interpreter (a minimal version of bash). Through this project, we explore and implement key operating system concepts including process creation and lifecycle (`fork`, `execve`, `waitpid`), file descriptors and redirections (`pipe`, `dup2`), signal handling (`SIGINT`, `SIGQUIT`), abstract syntax tree parsing, and interactive line editing using the GNU Readline library.

The shell displays a prompt, parses user input into commands, expands environment variables, handles quotes, manages standard input/output redirections and pipes, and executes built-in commands or external binaries located via the `PATH` environment variable.

## Instructions

### Prerequisites

To compile and run Minishell, you need:
- A C compiler (`gcc` or `clang`)
- GNU `make`
- The GNU `readline` development library

#### macOS Installation

On macOS, install `readline` using Homebrew:

```bash
brew install readline
```

If the compiler cannot find `readline.h` or `-lreadline`, ensure the compiler includes Homebrew's paths (e.g., in Apple Silicon `/opt/homebrew/opt/readline` or Intel `/usr/local/opt/readline`):

```bash
export CPATH="$(brew --prefix readline)/include:$CPATH"
export LIBRARY_PATH="$(brew --prefix readline)/lib:$LIBRARY_PATH"
```

#### Linux (Debian/Ubuntu) Installation

On Debian-based systems, install the dependencies via `apt`:

```bash
sudo apt update
sudo apt install build-essential libreadline-dev
```

### Compilation

Clone the repository and compile the executable:

```bash
make
```

Available Makefile targets:
- `make` or `make all`: Compiles `libft` and `minishell`.
- `make clean`: Removes object and dependency files.
- `make fclean`: Removes object files, dependency files, and the `minishell` binary.
- `make re`: Recompiles the entire project from scratch.

### Execution

Once compiled, launch the shell:

```bash
./minishell
```

To exit the shell, use the built-in `exit` command or press `Ctrl-D` on an empty line:

```bash
minishell> exit
```

## Features

- **Prompt**: Displays an interactive prompt waiting for user commands.
- **History**: Navigates previously entered commands using arrow keys (powered by Readline).
- **External Commands**: Searches and launches executables based on the `PATH` variable or relative/absolute paths.
- **Built-in Commands**:
  - `echo` (with `-n` option)
  - `cd` (relative or absolute path, `~`, HOME fallback)
  - `pwd` (prints current directory)
  - `export` (sets environment variables and prints exported list)
  - `unset` (removes environment variables)
  - `env` (displays environment variables)
  - `exit` (exits the shell with numeric status)
- **Redirections**:
  - `<`: Redirects standard input from a file.
  - `>`: Redirects standard output to a file (truncates existing file).
  - `>>`: Redirects standard output in append mode.
  - `<<`: Here-document (reads input until a specified delimiter is encountered).
- **Pipes**:
  - `|`: Connects the standard output of each command to the standard input of the next.
- **Environment Variables**:
  - Expands `$VAR` to its corresponding environment value.
  - Expands `$?` to the exit status of the most recently executed pipeline.
- **Signals**:
  - `Ctrl-C`: Displays a new prompt on a new line in interactive mode; cancels here-document or interrupts running commands.
  - `Ctrl-D`: Exits the shell (or terminates input in here-document).
  - `Ctrl-\`: Does nothing in interactive prompt mode.
- **Bonus Features**:
  - `&&` and `||` logical operators with parenthesis priority parsing.
  - Wildcard expansion (`*`) for matching files in the current working directory.

## Usage Examples

```bash
# Basic command execution
minishell> ls -la

# Environment variable expansion
minishell> echo "Hello $USER, current status: $?"

# Redirections
minishell> echo "42 Barcelona" > test.txt
minishell> cat < test.txt
minishell> echo "New line" >> test.txt

# Here-document
minishell> cat << EOF
> line 1
> line 2
> EOF

# Pipelines
minishell> cat Makefile | grep CC | wc -l

# Logical operators and parenthesis
minishell> (ls nonexistent || echo "Failed") && echo "Recovered"

# Wildcards
minishell> ls *.c
```

## Resources

### References
- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/)
- [GNU Readline Library Documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [POSIX.1-2017 Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- [Writing Your Own Shell - Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [UNIX File Descriptors and Pipes (CS Harvard)](https://www.cs.princeton.edu/courses/archive/fall10/cos217/lectures/17Pipes.pdf)

### AI Usage
AI was utilized in this project for:
1. **Heredoc Diagnosis and Fix**: Identifying why here-document input was discarded instead of piped to standard input, resolving child/parent signal propagation on `SIGINT` (Ctrl-C) to correctly cancel input and set exit status `130`, and ensuring proper file descriptor handoff and cleanup without leaks.
2. **Codebase Review**: Auditing compliance with the 42 subject rules regarding allowed system calls, signal global variable usage restrictions, and pipe execution limitations.
3. **Documentation**: Structuring this `README.md` in adherence to the 42 Subject Chapter V requirements.
