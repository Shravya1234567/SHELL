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
