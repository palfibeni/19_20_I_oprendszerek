# Questions

## C:
- int pipefd[2]; pipe(pipefd) -> create a reader-writer pair, 0-> reader, 1-> writer
- read(pipefd[0], destination, sizeof(destination)): it waits for the data to arrive.
- write(pipefd[1], str, sizeof(str))
- close(pipefd[0]): before write we should close the reader
- close(pipefd[1]): before read we should close the writer
    - close only closed the pipe for the actual process, not for everyone
    
- the problem arrise, when multiple process has to read, and write this pipe.
    to fix this, we can use multiple pipe, or use signals with a single pipe.

## bash:
