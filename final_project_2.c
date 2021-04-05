#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[])
{
    struct dirent *de; // Pointer for directory entry
    char s[100];       //for storing the directory name which is passed as argument
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
    int directories = 0;
    int files = 0;
    while ((de = readdir(dr)) != NULL)
    {
        if (de->d_type == 8) //d_type=8 then it is filetype
        {
            files++;
            printf("\nFile %d : %s", files, de->d_name);
        }
        else if (de->d_type == 4) //d_type=4 then it is directory
        {
            directories++;
            printf("\nDirectory %d : %s", directories, de->d_name);
        }
    }
    printf("\n");
    closedir(dr);

    printf("\nNumber of Directories is : %d", directories);
    printf("\nNumber of files is : %d\n", files);
    return 0;
}
