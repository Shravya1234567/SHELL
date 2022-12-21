# ASSIGNMENT 2

RUN MAKEFILE AS FOLLOWS:

```bash
   make main
   ./main
```

## Specification 1

- When the program is executed a shell prompt of following form will appear:

```bash
   <username@system_name:curr_dir>
```

- Tokenization of commands is handled.
- This specification is handled in main.c
- All input operations were handled in main.c
- All headers are included in headers.h
- All macros and global variables are defined in macros.h  

## Specification 2

- Implemented bulit-in commands : cd, echo, pwd
- All cases of cd command were handled
- For cd-, the directory in which we invoke the shell will be considered as home directory and the respective path will be printed from home(the directory in which we invoke the shell).
- pwd command prints absolute path from system's home.
- All tabs and spaces were handled for echo.
- All cases of cd command were handled in cd.c and their function declarations are in cd.h.
- pwd and echo commands are handled in pwd.c and echo.c respectively.

## Specification 3

- Implemented all cases of ls command.
- Specific colour coding is used.
- BLUE for directories, GREEN for executables and WHITE for regular files.
- ls is handled in ls.c

## Specification 4

- This is handled in fg.c(both foreground and background)
- Time taken by the foreground process is printed in the next prompt.
- sleep 1 ;sleep 2 when executed, time taken by sleep 1 and sleep 2 will be printed
- Any command invoked & is treated as background command.
- Whenever a new background process is started, the PID of the newly created background process is printed.

## Specification 5

- This specification is handled in pinfo.c
- pinfo prints the information about the shell program.
- "+" is added to status code if it is a foreground process.

## Specification 6

- This specification is handled in main.c
- If a background process is terminated, it prints a message on stderror(whether the process is terminated normally or abnormally)
- Linked list is used to store the pid of process and its corresponding process name.
- Linked list definition is in ll.h

## Specification 7

- This specification is handled in discover.c
- '.' is used for current directoy

## Specification 8

- This specification is handled in history.c
- A file history.txt is used to store last 20 commands.
- History prints last 10 commands.

# ASSIGNMENT 3

TO RUN THE MAKEFILE RUN THE FOLLOWING COMMAND

```bash
  make main
  ./main
```

## SPECIFICATION 1

- This specification is handled in redirection.c.
- I/O redirection is handled('<','>','>>').

## SPECIFICATION 2

- This specification is handled in pipe.c.
- One or more commands can be piped.

## SPECIFICATION 3

- This specification is handled in pipe.c and redirection.c.
- Input/output redirection within command pipelines.

## SPECIFICATION 4

- JOBS : This specification is handled in jobs.c.
jobs command prints a list of all currently running background processes in alphabetical order. jobs -r prints running process and jobs -s prints processes that are stopped.

- SIG : Takes the job number of a running job and sends the signal corresponding to the signal number to that process. This specification is handled in sig.c

- FG : This specification is handled in fg.c. Brings the running or stopped background job corresponding to job number to the foreground and changes its state to running.

- BG : This specification is handled in bg.c. Changes the state of a stopped background job to running.

## SPECIFICATION 5

- This specification is handled in signal.c

- CTRL-Z : It pushes any currently running foreground job into the background and changes its states from running to stopped.

- CTRL-C : It interrputs any currently running foreground job.

- CTRL-D : It logs out from the shell.
