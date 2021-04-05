#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    char b[100];
    if (argc == 1)
    {
        getcwd(b, 100);
    }
    else if (argc == 2)
    {
        strcpy(b, argv[1]);
    }
    chdir(b);
    int a[2]; // a[0] is for reading and a[1] is for writing in pipe
    pipe(a);  //pipe for interprocess communication
    pid_t child_pid;
    child_pid = fork();

    if (child_pid == 0) //executing ls command in child process
    {
        close(1);                 // closing normal stdout
        dup(a[1]);                // making stdout same as a[1]
        close(a[0]);              //closing reading part of pipe
        execlp("ls", "ls", NULL); //executing ls command with no arguments passed
    }
    else
    {
        wait(NULL);                     //waiting for child to finish
        close(0);                       // closing normal stdin
        dup(a[0]);                      // making stdin same as a[0]
        close(a[1]);                    // closing writing part in parent
        execlp("wc", "wc", "-l", NULL); //piping the ls with the wc with arg l
    }
}
