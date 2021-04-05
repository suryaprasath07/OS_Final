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
    int a[2];   // reading and a[1] is for
                // writing over a pipe
    pipe(a);    //piping for interprocess communication
    if (!fork())
    {
        // closing normal stdout
        close(1);

        // making stdout same as a[1]
        dup(a[1]);

        // closing reading part of pipe
        // we don't need of it at this time
        close(a[0]);

        // executing ls
        execlp("ls", "ls", NULL);
    }
    else
    {
        // closing normal stdin
        close(0);

        // making stdin same as a[0]
        dup(a[0]);

        // closing writing part in parent,
        // we don't need of it at this time
        close(a[1]);

        // executing wc
        execlp("wc", "wc", "-l", NULL);
    }
}