# IOS 2021 - Project 2 - Synchronization (Operating Systems)

## Description
This project is a synchronization task for the subject IOS. It involves simulating a Christmas scenario where Santa Claus, elves, and reindeer coordinate their actions using semaphores and shared memory. The project ensures correct synchronization of these entities based on predefined rules.

## Authors
- **Ondrej Galeta**

## Files
- `proj2.h` - Header file containing function declarations, global variables, and semaphore definitions.
- `proj2.c` - Main implementation file (not provided here but expected to contain logic for Santa, elves, and reindeer).
- `Makefile` - (If applicable) Used to compile the project.

## Compilation
To compile the project, use the following command (if a `Makefile` is provided, use `make` instead):
```sh
gcc -o proj2 proj2.c -pthread -lrt
```

## Usage
Run the compiled program with the following parameters:
```sh
./proj2 NE NR TE TR
```
where:
- `NE` - Number of elves
- `NR` - Number of reindeer
- `TE` - Time in milliseconds that elves take to work
- `TR` - Time in milliseconds that reindeer spend on vacation

### Example Execution
```sh
./proj2 3 9 1000 5000
```
This example starts a simulation with:
- 3 elves
- 9 reindeer
- Each elf works for 1000 ms before seeking Santa’s help
- Each reindeer spends 5000 ms on vacation before returning

## Synchronization Mechanisms
The project uses semaphores to ensure:
- Santa wakes up when needed.
- Elves wait in groups to get help.
- Reindeer wait until all have returned before preparing for Christmas.

