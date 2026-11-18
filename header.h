#ifndef SOURCE_TO_HTML
#define SOURCE_TO_HTML

#include <stdio.h>
#include <string.h>

// Function declarations
void html_initialize(FILE *fhp);
void html_end(FILE *hfp);
int source_to_html(FILE *fp,FILE *hfp);
void is_keyword(char *,FILE *);
void is_operator_symbol(char ch[],FILE *hfp);
#endif