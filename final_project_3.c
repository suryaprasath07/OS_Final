#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    struct dirent *de; // Pointer for directory entry
    char s[100];       //for storing the directory name which is passed as argument
    int flag = 0;      //to check if there isn't any file in the directory
    //assingning value to s according to condition
    if (argc == 2)
    {
        strcpy(s, argv[1]);
    }
    else if (argc == 1)
    {
        strcpy(s, ".");
    }
    else
    {
        return -1;
    }
    //opening the directory
    DIR *dr = opendir(s);
    if (dr == NULL) // opendir returns NULL if couldn't open directory
    {
        return -1;
    }
    while ((de = readdir(dr)) != NULL)
    {
        int fd = open(de->d_name, O_RDONLY); //Open for reading only.
        int size = lseek(fd, 0, SEEK_END);   //the file's offset is set to the size of the file plus the offset(0)
        if (de->d_type == 8)                 //d_type=8 then it is filetype
        {
            printf("\name : %s size : %d", de->d_name, size);
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