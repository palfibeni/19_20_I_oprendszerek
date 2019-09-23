# Questions:

## C:
- fork() -> We create a duplicate running of our program, with a neww PID. 
Returns the new process's PID, (in the child, the variable remains 0), if the creation is unsuccessful, it return negative.
Every variable beign already created before fork, gets to copy to the child.
- getpid() -> returns current process's PID
- getppid() -> return currenct process's parent's PID
- waitpid(child, &status, 0) -> forces a wait for paramter process to finish.

## bash:
- ps aux -> (bash command) show running processes
- kill -SIGKILL pid -> terminate running process

