#include<stdio.h>
#include"header.h"
void html_initialize(FILE *fp)
{
   
     fprintf(fp, "<html>\n");
     fprintf(fp, "<head>\n");
     fprintf(fp, "<title>Source To HTML</title>\n");
     fprintf(fp, "<link rel=\"stylesheet\" href=\"style.css\">\n");
     fprintf(fp, "</head>\n");
     fprintf(fp, "<body>\n");
     fprintf(fp, "<pre><code>\n");
   

}
void html_end(FILE *fp)
{
  
    fprintf(fp, "</code></pre>\n");
    fprintf(fp, "</body>\n");
    fprintf(fp, "</html>\n");

}