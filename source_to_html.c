#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<ctype.h>
#include"header.h"

void is_keyword(char str[],FILE *hfp) // to check keyword
{
      char key_words[28][10] = {"auto","break","case","char","const","continue","default","do",
       "double","enum","extern","float","for","goto","int","long","register","short",    
       "signed","sizeof","static","struct","typedef","union","unsigned","void","volatile","while"};

       char key_case[4][10] = {"else","if","switch","return",};

       char input_output[5][10]={"printf","scanf","fopen","fclose","perror"};

    int count=0;
    for (int i = 0; i < 28; i++)
    {
        if(strcmp(key_words[i],str)==0)
        {
            fprintf(hfp, "<span class=\"keyword\">%s</span>", str);
            count++;

        }
    }
    for (int i = 0; i < 5; i++)
    {
        if(strcmp(input_output[i],str)==0)
        {
            fprintf(hfp, "<span class=\"ip_op\">%s</span>", str);
            count++;

        }
    }
    for (int i = 0; i < 28; i++)
    {
        if(strcmp(key_case[i],str)==0)
        {
            fprintf(hfp, "<span class=\"keyword1\">%s</span>", str);
            count++;
        }
    }
    
    if(count==0)
    {
        fprintf(hfp, "<span class=\"variable\">");
        int i=0;
        while (str[i]!='\0')
        {
          fputc(str[i],hfp);
          i++;
        }
        fprintf(hfp, "</span>");
    }
}
void is_operator_symbol(char ch[],FILE *hfp)  // to check operator symbol
{
    int count=0;
    char operators[30][3] ={"+", "-", "*", "/", "%","++", "--","=", "+=", "-=", "*=", "/=", "%=",
                            "==", "!=", ">", "<", ">=", "<=","&&", "||", "!","&", "|", "^",";", ",", ".", ":", "?"};
    
    char symbols[6][2] ={"(", ")", "{", "}", "[", "]"};

    for (int i = 0; i < 30; i++)
    {
        if(strcmp(operators[i],ch)==0)
        {
            fprintf(hfp, "<span class=\"operator\">%s</span>", ch);
            count++;
        }
    }
    if(count==0)
    {
        for (int i = 0; i < 6; i++)
        {
            if(strcmp(symbols[i],ch)==0)
            {
                fprintf(hfp, "<span class=\"symbol\">%s</span>", ch);
            }
        }
        
    }
    

}
int source_to_html(FILE *fp,FILE *hfp)  // to identify C language tokens and generate HTML output.
{
    int ch;
    char buffer[1000];
    while ((ch=fgetc(fp))!=EOF)
    {
        if(ch=='/')  //to check comment and convert to html
        {
            
            if((ch=fgetc(fp))=='*' || ch=='/')
            {
                int count=0;
                fseek(fp,-2,SEEK_CUR);
                while ((ch=fgetc(fp))!='\n' && ch!=EOF)
                {
                    buffer[count]=ch;
                    count++;
                    buffer[count]='\0';
                }
                fprintf(hfp, "<span class=\"comment\">%s</span>", buffer);
            }
        }
        else if(ch=='"') // to check string and convert html
        {
            fprintf(hfp,"<span class=\"string\">");
            fputc(ch,hfp);
            while ((ch=fgetc(fp))!=EOF)
            {
                fputc(ch,hfp);
                if(ch=='"')
                break;
            }
            fprintf(hfp,"</span>");
            continue;
        }
        else if(isalpha(ch))  // to check alphabate / keywords and convert html
        {
            int count=0;
            buffer[0]='\0';
            buffer[count]=ch;
            count++;
            buffer[count]='\0';
            while ((ch=fgetc(fp))!=EOF)
            {
                if(isalnum(ch) || ch=='_')
                {
                    buffer[count]=ch;
                    count++;
                    buffer[count]='\0';
                }
                else
                break;
            }
            buffer[count]='\0';
            fseek(fp,-1,SEEK_CUR);
            is_keyword(buffer,hfp);
            continue;

        }
        else if(ch=='#') // to check preprocessor directory and convert html
        {
            fprintf(hfp,"<span class=\"preprocessor\">");
            fputc(ch,hfp);
            while (isalpha(ch=fgetc(fp)))
            {
               fputc(ch,hfp);
            }
            fprintf(hfp,"</span>");
            fseek(fp,-1,SEEK_CUR);
           continue;
        }
        else if(ch=='<')  // to check header and convert html
        {
            if(fgetc(fp)==' ')
            {
                fprintf(hfp, "<span class=\"operator\">%c</span>", ch);
                fseek(fp,-1,SEEK_CUR);
                continue;;
            }
            fseek(fp,-1,SEEK_CUR);
            char buffer[100];
            int count=0,found=0;
            buffer[count++]='&';
            buffer[count++]='l';
            buffer[count++]='t';
            buffer[count]='\0';
            while ((ch=fgetc(fp))!=EOF)
            {
               if(ch=='>')
                 {
                    buffer[count++]='&';
                    buffer[count++]='g';
                    buffer[count++]='t';
                    buffer[count]='\0';
                    found++;
                    break;
                 }
                  buffer[count]=ch;
                  count++;
                  buffer[count]='\0'; 
            }
            if(found!=0)
            {
                fprintf(hfp,"<span class=\"header\">%s</span>",buffer);
                continue;
            }
            else
            {
              int num=count-1;
              fseek(fp,count,SEEK_CUR); 
              ch=fgetc(fp);
              fputc(ch,hfp);

            } 
        }
        else if(isdigit(ch))  // to check digit and convert html
        {
            int count=0;
            buffer[count++]=ch;
            buffer[count]='\0';
            while (isdigit(ch=fgetc(fp)) || ch=='.')
            {
                buffer[count++]=ch;
                buffer[count]='\0';
            }
            fprintf(hfp,"<span class=\"digits\">%s</span>",buffer);
            fseek(fp,-1,SEEK_CUR);
        }
        else if(ch=='\n' || ch==' ')
        {
           fputc(ch,hfp);
        }
        else if(ch=='\'')  // to check single character and convert html
        {
            int count=0;
            buffer[count++]=ch;
            buffer[count++]=fgetc(fp);
            buffer[count++]=fgetc(fp);
            buffer[count]='\0';
            fprintf(hfp,"<span class=\"single_char\">%s</span>",buffer);

        }
        else 
        {
            int count=0;
            buffer[count++]=ch;
            buffer[count]='\0';
            is_operator_symbol(buffer,hfp);
        } 
    }
}