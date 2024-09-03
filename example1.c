//program example1.c this program shows how to use pipes for IPC
//create one child, the child adds the element o the array array1 and send the result to the parent
//The parent print the result

//compile:  gcc -o example1 example1.c
//execute:  ./example1


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
int fd[2]; //creates pipe fd
pipe(fd);


int sum=0;


int array1[6] = {2,3,7,-1,10,6}; // This is a hardwire solution (yours is different)
 

 printf("hello world, I am Parent the only one with process ID: (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
       // fork failed; exit
        fprintf(stderr, "fork failed\n");
         exit(1);
        
        } else if (rc == 0) {
        close(fd[0]);
        int i;
        for(i=0; i<6; i++){  //add all the elements of the array.
          sum = sum+array1[i];
         }
          write(fd[1], &sum, sizeof(sum));
          printf(" I am process %d and I am sending : %d to my parent\n", (int) getpid(),  sum);
         close(fd[1]);
        exit(0);   //I am including exit(0) to kill the process after is done !!!!@
    }
   else {
        int sum1;
        int final=0;
        close(fd[1]);
        read(fd[0], &sum1, sizeof(sum));
        final = sum1;
        close(fd[0]);
        printf("I am the parent at the end with ID %d with a final sum of: %d \n" , (int) getpid(), final);
    }

    return 0;
}
