# Linux Shell Implementation

A simple custom shell implementation written in C for Operating Systems course. This project demonstrates fundamental concepts of process creation, command execution, and command history management in Unix-like operating systems.

## Features

- **Interactive Command Prompt**: Custom prompt (`Terminal>`) for command input
- **Command Execution**: Execute standard Linux commands using `fork()` and `execvp()`
- **Command History**: Store and retrieve up to 100 previously executed commands
- **History Navigation**:
  - View all command history with `history`
  - Re-execute the last command with `!!`
  - Re-execute a specific command by number with `!n` (e.g., `!5`)
- **Exit Command**: Gracefully exit the shell with `exit`

## Prerequisites

- GCC compiler
- Unix-like operating system (Linux, macOS, etc.)
- Make utility

## Installation

1. Clone the repository:

```bash
git clone <repository-url>
cd "Shell 4 Linux"
```

2. Compile the project:

```bash
make
```

This will create an executable named `linuxshell`.

## Usage

### Running the Shell

Execute the compiled shell:

```bash
./linuxshell
```

You will see the custom prompt:

```shell
Terminal>
```

### Basic Commands

Execute any standard Linux command:

```shell
Terminal> ls
Terminal> pwd
Terminal> echo "Hello, World!"
```

### History Commands

View command history:

```shell
Terminal> history
1 ls
2 pwd
3 echo "Hello, World!"
```

Re-execute the last command:

```shell
Terminal> !!
```

Re-execute a specific command by its number:

```shell
Terminal> !2
pwd
```

### Exiting the Shell

```shell
Terminal> exit
```

## Project Structure

```
.
├── main.c          # Main source code file
├── makefile        # Build configuration
├── README.md       # Project documentation
```

## Implementation Details

### Key Components

- **Process Management**: Uses `fork()` to create child processes and `execvp()` to execute commands
- **Command Parsing**: Tokenizes user input into command and arguments
- **History Storage**: Maintains an array of up to 100 commands
- **Error Handling**: Provides informative messages for invalid commands and history operations

### Constants

- `MAX_LINES`: Maximum length of command input (80 characters)
- `MAX_HISTORY`: Maximum number of commands stored in history (100 commands)

### Functions

- `message(int code)`: Displays error and informational messages based on error codes

## Limitations

- Maximum command length: 80 characters
- Maximum history size: 100 commands
- Does not support:
  - Piping (`|`)
  - Redirection (`>`, `<`, `>>`)
  - Background processes (`&`)
  - Built-in commands beyond `history`, `!!`, `!n`, and `exit`
  - Command line editing (arrow keys)

## Error Messages

- `No command in history!`: Displayed when history is empty and `!!` or `!n` is used
- `Such a command is NOT in history!`: Displayed when referencing a non-existent history number
- `Fork failed`: Critical error when process creation fails

## Development

### Building from Source

```bash
gcc main.c -o linuxshell
```

### Cleaning Build Files

```bash
rm -f linuxshell
```

## License

This project is created for educational purposes.
