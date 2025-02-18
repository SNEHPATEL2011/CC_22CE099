%{
#include <stdio.h>
int char_count = 0, word_count = 0, line_count = 0;
%}

%%
.       { char_count++; }
\n      { char_count++; line_count++; }
[ \t]+  { /* Ignore spaces and tabs */ }
[A-Za-z0-9]+ { word_count++; char_count += yyleng; }
%%

int main() {
    yylex();
    printf("Characters : %d\n", char_count);
    printf("Words : %d\n", word_count);
    printf("Lines : %d\n", line_count);
    return 0;
}

int yywrap() {
    return 1;
}
