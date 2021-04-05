#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[])
{
    struct dirent *de; // Pointer for directory entry
    char s[100];
    if (argc == 2)
    {
        strcpy(s, argv[1]);
    }
    else
    {
        strcpy(s, ".");
    }
    DIR *dr = opendir(s);
    if (dr == NULL) // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory");
        return 0;
    }
    int directories = 0;
    int files = 0;
    while ((de = readdir(dr)) != NULL)
    {
        if (de->d_type == 8)
        {
            files++;
            printf("\nFile %d : %s", files, de->d_name);
        }
        else
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
