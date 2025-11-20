# Pipe Simulation

A program that simulates inter-process communication (IPC) using pipes in operating systems.

## Description

This program demonstrates how to use pipes for communication between a parent process and a child process:
- The parent process receives a sentence from the user and sends it to the child process via pipe
- The child process processes the string (converts case and removes spaces)
- The child process sends the result back to the parent process via pipe

## Requirements

- GCC compiler
- Unix/Linux/macOS operating system

## Compilation

```bash
make
```

Or compile manually:
```bash
gcc main.c -o pipeSimulation
```

## Running

```bash
make run
```

Or:
```bash
./pipeSimulation
```

## Usage

1. Run the program
2. Enter any sentence when prompted
3. The program will display:
   - The string sent from parent to child
   - The string received from child to parent (processed)
4. Type `exit` to quit the program

## Cleanup

To remove the executable file:
```bash
make clean
```

