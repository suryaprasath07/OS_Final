#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int to_upper_file(FILE *);

int main(int argc,char* argv[])
{
    FILE *fp;
    int status;
    int i,sum=0;
    printf("argc=%d\n",argc);
    if(argc==1)
    {
        printf("Insufficient arguements:");
        printf("no file name provided at command line");
        return;
    }
    if(argc>1)
    {
             fp=fopen(argv[1],"r+");
             if(strcmp(argv[1],"nofilter")>0||strcmp(argv[1],"-M")>0)
             {
                if(strcmp(argv[1],"-M")>0)
                {
                    status=to_upper_file(fp);
                    if(status==0)
                    {
                        printf("\n the content of\"%s\" file was converted to upper case\n",argv[1]);
                        return;
                    }
                    if(status==-1)
                    {
                        printf("\n failed to convert");
                        return;
                    }
                }
             }
    }
    return 0;
}

int to_upper_file(FILE *fp)
{
    char ch;
 
    if (fp == NULL)
    {
        perror("Unable to open file");
        return -1;
    }
    else
    {
        
        while (ch != EOF)
        {
            ch = fgetc(fp);
            if ((ch >= 'a') && (ch <= 'z'))
            {
                ch = ch - 32;
                fseek(fp,-1,SEEK_CUR);
                fputc(ch,fp);
            }    
        }
        return 0;
    }
}