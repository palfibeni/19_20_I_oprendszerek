# Questions

## C:
- Named pipeline:
    - create:
        - char pipename[20];
        - sprintf(pipename,"/tmp/%d",getpid()); pipename should be unique, use Neptun code, or PID
        - int fid=mkfifo(pipename, S_IRUSR|S_IWUSR ); 
        - if (fid==-1) {...}
    - connect: 
        - int fd=open(pipename,O_RDONLY); / int fd=open(pipename,O_WRONLY);
        - read(fd,s,sizeof(s)); / write(fd,"Hajra Fradi!\n",12);
    - destroy:
        - unlink(pipename); PID named files gets deleted usually when the program ends

## bash:
