%{
    int num_lines = 0;
    int num_words = 0;
%}

%%
^[ \t]*\n                        /* empty line */
[ \t]+$                          /* one or more at the end of the line */
^[ \t]+                          /* at the beginning */
[ \t]+                           { putchar(' '); }
[a-zA-Z0-9]+                     { ++num_words; ECHO; }
\n                               { ++num_lines; ECHO; }
.                                { ECHO; } /* just copy the rest */
%%

int main(int argc, char** argv) {
    
    if ( argc < 2 ) {
        printf("Insufficient number of arguments! 1. input 2. output\n");
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    if ( !fp ) {
        printf("Couldn't open a file! :(\n");
        exit(1);
    }

    yyin = fp;

    while(yylex());

    printf("Number of lines: %d\nNumber of words: %d\n", num_lines, num_words);

    fclose(fp);
    return 0;
}
