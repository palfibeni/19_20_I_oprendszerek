# Questions

## C:
- Block a signal:
    - sigset_t sigset; // creates a sigset_t
    - sigemptyset(&sigset); // init empty signal set
    - sigaddset(&sigset,SIGTERM); //add SIGTERM to set
    - //sigfillset(&sigset); //add each signal to the set
    - sigprocmask(SIG_BLOCK,&sigset,NULL); //signals in sigset will be blocked, pasue will wait further
    - sigprocmask(SIG_UNBLOCK,&sigset,NULL); //SIGTERM is now released (not blocked further), the process will get it

- Adding complex handler to signal, with data: gy04/sigaction.value.c
    - we need a 3 parameter handler: 
        - handler(int signumber,siginfo_t* info,void* nonused)
    - we need a sigact listener:
        - struct sigaction sigact;
        - sigact.sa_sigaction=handler; //instead of sa_handler, we use the 3 parameter version
        - sigemptyset(&sigact.sa_mask); 
        - sigact.sa_flags=SA_SIGINFO; //we need to set the siginfo flag 
        - sigaction(SIGTERM,&sigact,NULL); 
    - we need a sigqueue sending method (note that the data has to be accessable to the parent too):
        - union sigval s_value_ptr;
        - s_value_ptr.sival_ptr=&data;  //the struct data must define in commmon code
        - sigqueue(getppid(),SIGTERM,s_value_ptr);


## bash:
- gcc -lrt filename

