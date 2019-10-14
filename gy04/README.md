# Questions

## C:
- Block a signal:
-- sigset_t sigset; // creates a sigset_t
-- sigemptyset(&sigset); // init empty signal set
-- sigaddset(&sigset,SIGTERM); //add SIGTERM to set
-- //sigfillset(&sigset); //add each signal to the set
-- sigprocmask(SIG_BLOCK,&sigset,NULL); //signals in sigset will be blocked, pasue will wait further
-- sigprocmask(SIG_UNBLOCK,&sigset,NULL); //SIGTERM is now released (not blocked further), the process will get it

- Adding complex handler to signal, with data: gy04/sigaction.value.c

## bash:
- gcc -lrt filename

