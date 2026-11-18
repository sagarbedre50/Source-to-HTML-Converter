#include<stdio.h>
#include<string.h>
#include"header.h"
int main(int argc, char *argv[])
{
    if(argc!=2) // to check valid command line argument and in it is not valid then display the valid command.
    {
        printf("+---------------------------------------------+");
        printf("| Please enter valid command :                |");
        printf("| Ex : ./a.out sample.txt                     |");
        printf("+---------------------------------------------+");
        return -1;
    }

     FILE *fp;
     fp=fopen(argv[1],"r");

     if(fp==NULL)
     {
        perror("ERROR :");
        return -1;
     }

     int ch;
     
     FILE *hfp;
     hfp=fopen("output.html","w");
     if(hfp==NULL)
     {
        perror("ERROR : ");
        return -1;
     }
     
     html_initialize(hfp);  // html initialization in .html file
     source_to_html(fp,hfp); // to convert c code to html 
     html_end(hfp); // html end in .html files
     
     printf("\n");
     printf("+================================================+\n");
     printf("|          SOURCE CODE TRANSFORMATION DONE       |\n");
     printf("+================================================+\n");
     printf("|  SUCCESS:- HTML file generated successfully!   |\n");
     printf("|  FILE NAME:-    output.html                    |\n");
     printf("|  ACTION:-  Launch browser to view your code.   |\n");
     printf("|  STATUS:-  Syntax highlighting is ready!       |\n");
     printf("+================================================+\n");
     printf("\n");
     
     fclose(hfp);
     fclose(fp);
     return 0;
     
}