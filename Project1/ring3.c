#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void prtastr(const char *s, int fd, int n);
void wastesometime(int n);

int main(int argc,  char *argv[ ]) {
   pid_t childpid;             /* indicates process should spawn another     */
   int error;                  /* return value from dup2 call                */
   int fd[2];                  /* file descriptors returned by pipe          */
   int i;                      /* number of this process (starting with 1)   */
   int nprocs;                 /* total number of processes in ring          */ 
   int n;                      /* parametro utilizado por prtastr */
           /* check command line for a valid number of processes to generate */
   if ( (argc != 3) || ((nprocs = atoi (argv[1])) <= 0) ) {
       fprintf (stderr, "Usage: %s nprocs n\n", argv[0]);
       return 1; 
   }  
   if (pipe (fd) == -1) {      /* connect std input to std output via a pipe */
      perror("Failed to create starting pipe");
      return 1;
   }
   if ((dup2(fd[0], STDIN_FILENO) == -1) ||
       (dup2(fd[1], STDOUT_FILENO) == -1)) {
      perror("Failed to connect pipe");
      return 1;
   }
   if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) {
      perror("Failed to close extra descriptors");
      return 1; 
   }        
   for (i = 1; i < nprocs;  i++) {         /* create the remaining processes */
      if (pipe (fd) == -1) {
         fprintf(stderr, "[%ld]:failed to create pipe %d: %s\n",
                (long)getpid(), i, strerror(errno));
         return 1; 
      } 
      if ((childpid = fork()) == -1) {
         fprintf(stderr, "[%ld]:failed to create child %d: %s\n",
                 (long)getpid(), i, strerror(errno));
         return 1; 
      } 
      if (childpid > 0)               /* for parent process, reassign stdout */
          error = dup2(fd[1], STDOUT_FILENO);
      else                              /* for child process, reassign stdin */
          error = dup2(fd[0], STDIN_FILENO);
      if (error == -1) {
         fprintf(stderr, "[%ld]:failed to dup pipes for iteration %d: %s\n",
                 (long)getpid(), i, strerror(errno));
         return 1; 
      } 
      if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) {
         fprintf(stderr, "[%ld]:failed to close extra descriptors %d: %s\n",
                (long)getpid(), i, strerror(errno));
         return 1; 
      } 
      if (childpid)
         break;
   }
   int log = open("/home/ubuntu/workspace/Project/log.txt",1 , 0);
   prtastr("Prueba",log, n);
   close(log);
   return 0; 
}     

void prtastr(const char *s, int fd, int n){
   int i;
   for(i = 0; i < strlen(s); i++){
      write(fd, &s[i], sizeof(s[i]));
      fprintf(stderr, "This is process %d with ID %ld and parent id %ld and writes %c\n",
           i, (long)getpid(), (long)getppid(), s[i]);

   }
   wastesometime(n);
}

void wastesometime(int n){
   static volatile int dummy = 0;
   int i;
   
   for(i = 0; i < n; i++)
      dummy++;
}