# minishell

A minimal Unix shell implementation in C, replicating core features of bash. This project demonstrates deep understanding of shell mechanics, process management, and system programming.

```
███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████╗ ██╗  ██╗ ███████╗ ██╗      ██╗ 
████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════╝ ██║  ██║ ██╔════╝ ██║      ██║  
██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████╗ ███████║ █████╗   ██║      ██║  
██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██║ ██╔══██║ ██╔══╝   ██║      ██║  
██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████║ ██║  ██║ ███████╗ ███████╗ ███████╗
╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════╝ ╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝
```

## Overview

**minishell** is a fully functional Unix shell written from scratch in C. It implements essential shell functionality including command parsing, execution, piping, redirection, environment variable management, and built-in commands. The shell handles complex scenarios like heredoc redirections, pipe chains, signal management, and quoted string parsing.

## Features

### Core Functionality
- **Command Execution**: Parse and execute external commands with proper argument handling
- **Pipes**: Chain multiple commands with pipe operators (`|`)
- **Redirections**: 
  - Input redirection (`<`)
  - Output redirection (`>`)
  - Append output (`>>`)
  - Heredoc (`<<`)
- **Environment Variables**: Full support for environment variable expansion and management
- **Quoted String Handling**: Proper parsing of single and double quotes with escape sequences
- **Signal Handling**: Graceful handling of SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\\)

### Built-in Commands
- **`echo`**: Print text with optional newline suppression (`-n` flag)
- **`cd`**: Change directory with support for relative and absolute paths
- **`pwd`**: Print working directory
- **`export`**: Set and manage environment variables
- **`unset`**: Remove environment variables
- **`env`**: Display current environment
- **`exit`**: Terminate the shell with an optional exit code
- ** Every other command has been handled with execve
  
### Advanced Features
- **Heredoc Support**: Multi-line input with custom delimiters
- **Variable Expansion**: `$VAR` and `$?` (exit status) support
- **Command Path Resolution**: Automatic PATH search for external commands
- **Garbage Collection**: Automatic memory management to prevent leaks
- **Syntax Validation**: Input parsing with proper error handling

## Requirements

- GCC or compatible C compiler
- Linux/Unix-based operating system
- GNU Readline library (`libreadline-dev` on Debian/Ubuntu)
- POSIX-compliant system

## Building

```bash
# Build the project
make

# Clean build artifacts
make clean

# Full clean (remove executable and libft.a)
make fclean

# Rebuild from scratch
make re
```

The build process compiles the `minishell` executable with the custom `libft` library included.

## Usage

```bash
# Run the shell
./minishell

# Execute commands normally
$ ls -la
$ pwd
$ echo "Hello World"

# Use pipes
$ cat file.txt | grep "pattern" | wc -l

# Use redirections
$ echo "text" > output.txt
$ cat < input.txt >> output.txt

# Use heredoc
$ cat << EOF
> This is a heredoc
> EOF

# Set and use environment variables
$ export MY_VAR=value
$ echo $MY_VAR

# Run built-in commands
$ cd /path/to/dir
$ unset MY_VAR
```

## Project Structure

```
minishell/
├── Makefile                      # Build configuration
├── README.md                     # This file
│
├── libft/                        # Custom C library
│   ├── *.c                       # String, memory, and utility functions
│   ├── ft_gnl/                   # Get Next Line (file reading)
│   ├── ft_printf/                # Custom printf implementation
│   └── libft.h                   # Library header
│
└── src/                          # Main shell source code
    ├── main.c                    # Entry point
    ├── mini_shell.h              # Main header with structures
    ├── read_line_loop.c          # Main shell loop
    ├── main_parsing.c            # High-level parsing logic
    │
    ├── parsing/                  # Input parsing and tokenization
    │   ├── input_parsing.c       # Tokenize input
    │   ├── input_parsing_two.c   # Additional parsing logic
    │   ├── quotes.c              # Handle quoted strings
    │   ├── token_refiner.c       # Process and refine tokens
    │   └── token_refiner_two.c   # Additional token processing
    │
    ├── execution/                # Command execution
    │   ├── basic_exec.c          # Basic execution flow
    │   ├── single_cmd_exec.c     # Single command execution
    │   ├── pipe_cmd_exec.c       # Pipe chain execution
    │   ├── cmd_initialization.c  # Command structure setup
    │   ├── file_manage.c         # File descriptor management
    │   ├── file_manage_two.c     # Additional file operations
    │   └── exec_util.c           # Execution utilities
    │
    ├── builtins/                 # Built-in command implementations
    │   ├── cd.c                  # Change directory
    │   ├── echo.c                # Echo command
    │   ├── env.c                 # Environment display
    │   ├── exit.c                # Exit shell
    │   ├── export.c              # Set environment variables
    │   ├── pwd.c                 # Print working directory
    │   └── unset.c               # Unset environment variables
    │
    ├── garbage_collector/        # Memory management
    │   ├── garbage_collector.c   # Main garbage collection
    │   └── garbage_collector_util.c
    │
    ├── signals/                  # Signal handling
    │   └── signal.c              # SIGINT and SIGQUIT handling
    │
    ├── env_variables.c           # Environment variable management
    ├── ft_error.c                # Error handling and reporting
    ├── ft_find_cmd_path.c        # Command path resolution in PATH
    ├── ft_heredoc.c              # Heredoc implementation
    ├── ft_init_cmd.c             # Command initialization
    ├── ft_init_cmd_two.c         # Additional command setup
    ├── ft_split_plus.c           # Enhanced string splitting
    ├── ft_split_plus_two.c       # Additional split functions
    ├── ft_builtin_check.c        # Identify built-in commands
    ├── handle_token_search.c     # Token searching utilities
    └── check.c                   # Validation checks
```

## Architecture

### Data Structures

**`t_cmd`** - Command structure
- Stores parsed command information
- Contains flags for redirections, pipes, and heredocs
- Maintains file descriptors and process IDs
- Tracks environment and arguments

**`t_env`** - Environment variable linked list
- Doubly-linked list of key-value pairs
- Allows efficient variable lookup and modification

**`t_token`** - Token linked list
- Represents parsed input as connected tokens
- Enables flexible token manipulation during parsing

**`t_garbage_collector`** - Memory tracker
- Linked list of allocated pointers
- Centralized memory cleanup on exit

### Execution Flow

1. **Input Reading**: Readline library provides user input
2. **Parsing**: Input tokenized and validated
3. **Token Refinement**: Quoted strings processed, variables expanded
4. **Command Initialization**: Parsed tokens converted to command structures
5. **Execution**:
   - Built-in commands executed directly
   - External commands forked and executed
   - Pipes and redirections handled via file descriptors
6. **Cleanup**: Garbage collector frees all allocated memory

### Signal Handling

- **SIGINT (Ctrl+C)**: Interrupts current command, returns to prompt
- **SIGQUIT (Ctrl+\\)**: Terminates shell with core dump indication

## Key Implementation Details

### Parsing Strategy
- Custom tokenizer handles spaces, quotes, and special characters
- Two-pass parsing: initial tokenization, then refinement
- Quote handling preserves embedded variables and escape sequences

### Pipe Implementation
- Each pipe creates a pair of file descriptors
- Parent process manages all child processes
- Proper stdin/stdout redirection for each command

### Environment Variable Expansion
- `$VAR` syntax for variable expansion
- `$?` expands to the exit status of the last command
- Unset variables expand to an empty string

### Heredoc Processing
- Temporary file created for each heredoc
- Delimiter matching ensures proper termination
- Supports variable expansion within heredoc content

### Memory Management
- Garbage collector tracks all allocations
- Single cleanup at program exit
- Prevents memory leaks across complex execution chains

## Compilation Notes

- Compiled with `-Wall -Wextra -Werror` flags for strict compliance
- Includes debug symbols with `-g` flag
- Requires `libreadline` for interactive line editing
- Custom libft library compiled and linked automatically

## Testing

The shell has been tested with:
- Basic command execution
- Multiple pipe chains (up to 512 pipes supported)
- Complex redirect combinations
- Heredoc with various delimiters
- Environment variable manipulation
- Signal interruption and handling
- Quote and escape sequence parsing

## Known Limitations

- Maximum of 512 pipes per command chain
- Heredoc delimiter limited to reasonable lengths
- Some advanced bash features not implemented (job control, history editing shortcuts)

## Known Errors

- When using Ctrl-C in a ```SHLVL``` >= 3, the readline prompt ```minishell> ```  may become duplicated.
- Heredoc doesn't behave exactly like bash when piped into multiple cat commands. 
Example: ``` cat | cat | cat << eof ```

## Contributing

This project follows 42 School coding standards (Norm):
- Maximum 25 lines per function
- Strict formatting and style guidelines
- Comprehensive error handling
- Clear, modular code organization

## Authors
- unicorcn453
- Dimitar-T

---

