       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h> // for pipe()
       #include <string.h>
       #include <sys/wait.h>
	//
	// unnamed pipe example
	//
    int main(int argc, char *argv[]) {
       int pipefd[2]; // unnamed pipe file descriptor array
       pid_t pid;
       char sz[100];  // char array for reading from pipe

       if (pipe(pipefd) == -1) {
           perror("Hiba a pipe nyitaskor!");
           exit(EXIT_FAILURE);
       }
       pid = fork();	// creating parent-child processes
       if (pid == -1)  {
           perror("Fork hiba");
           exit(EXIT_FAILURE);
       }

       if (pid == 0)  {    	// child process
           //sleep(3);	// sleeping a few seconds, not necessary
            close(pipefd[1]);  //Usually we close the unused write end
            printf("Gyerek elkezdi olvasni a csobol az adatokat!\n");
            
            int r2;
            while (read(pipefd[0],&r2,sizeof(r2))) { // addig vár, míg egy író vég sem marad.
                printf("Gyerek olvasta uzenet: %i",r2);
                printf("\n");
            }
            close(pipefd[0]); // finally we close the used read end
       }  else  {    // szulo process 
            printf("Szulo indul!\n");
            //close(pipefd[0]); //Usually we close unused read end
            int n,i,r; // i ciklus változó, n db szám, r aktuális
            n = rand() % 10;
            for (i=0; i < n; i++) {
                r = rand() % 20;
                write(pipefd[1], &r, sizeof(r)); // array can be sent without &
                
            }
            close(pipefd[1]); // Closing write descriptor 
            printf("Szulo beirta az adatokat a csobe!\n");
            fflush(NULL); 	// flushes all write buffers (not necessary)
            wait(NULL);		// waiting for child process (not necessary)
            printf("Szulo befejezte!\n");	
       }
       exit(EXIT_SUCCESS);	// force exit, not necessary
    }

 
