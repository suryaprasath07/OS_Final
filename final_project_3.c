#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct dirent *de; // Pointer for directory entry
    char s[100];
    getcwd(s,sizeof(s));       //for storing the directory name which is passed as argument
    int flag = 0;      //to check if there isn't any file in the directory
    //opening the directory
    DIR *dr = opendir(s);
    if (dr == NULL) // opendir returns NULL if couldn't open directory
    {
        return -1;
    }
    while ((de = readdir(dr)) != NULL)
    {
        int fd = open(de->d_name, O_RDONLY); //Open for reading only.
        if (de->d_type == 8)                 //d_type=8 then it is filetype
        {
            int size = lseek(fd, 0, SEEK_END);   //the file's offset is set to the size of the file plus the offset(0)
            printf("\n Name : %s size : %d", de->d_name, size);
            flag = 1;
        }
        close(fd);
    }
    if (flag == 0)
    {
        printf("\nNo Files in this directory");
    }
    printf("\n");
    closedir(dr);
}
