# Questions

## C:
- kill(pid, param): calls kill -param for given pid
- pause(): waits for a "signal" from the system, it could be a kill command
- signal(param, handler): if param signal recieved, run handler instead
    -- if the given handler is SIG_IGN, ignored signal won't unlock pause().
    -- if the given handler is SIG_DFL, the command's default functionality runs.
- raise(param): signals the current process with the given param, could be SIGTERM to terminate is


## bash:
- kill -SIGKILL pid: terminates a process instantly.
- kill -SIGTERM pid: terminates a process, can be caught, and ignored.

