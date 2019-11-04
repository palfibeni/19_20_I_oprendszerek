#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
  
    // make two process which run same 
    // program after this instruction 
    fork(); 
    fork(); 
    fork(); 
    fork(); 
  
    printf("Hello world! child: %i parent: %i \n", getpid(), getppid()); 
    return 0; 
} 