/* "Each comment is replaced by one space character" or sth */
%{
    int doxygen = 0;
    int debug = 0;
%}

%x COMMENT_INIT SINGLE_LINE_REMOVE MULTI_LINE_REMOVE INCLUDE STRING DOXYGEN_SINGLE

%%
<INITIAL>{
                "<"              { if (debug) printf(" INCLUDE "); ECHO; BEGIN(INCLUDE); }
                "<<"             { if (debug) printf(" OPERATOR "); ECHO; } /* just an operator leave it alone */
                "\""             { if (debug) printf(" STRING " ); ECHO; BEGIN(STRING); }

                "//"             { if (debug) printf(" SINGLE "); BEGIN(SINGLE_LINE_REMOVE); }

                "///"|"//!"      { if ( doxygen ) {
                                        ECHO;
                                        BEGIN(DOXYGEN_SINGLE);
                                    } else {
                                        if (debug) printf(" DOX SINGLE ");
                                        BEGIN(SINGLE_LINE_REMOVE);
                                    }
                                 }

                "/*"             { printf(" MULTI "); BEGIN(MULTI_LINE_REMOVE); }

                "/**"|"/*!"      { if ( doxygen ) {
                                        ECHO;
                                        BEGIN(INITIAL);
                                    } else {
                                        if (debug) printf(" DOX MULTI ");
                                        BEGIN(MULTI_LINE_REMOVE);
                                    } 
                                 }

                "/**/"           { if (debug) printf(" SPECIAL "); putchar(' '); } /* that one special case... */

                "\\\n"           { if (debug) printf(" NEWLINE ESC "); putchar('\n'); }


                .                { ECHO; }
}

<SINGLE_LINE_REMOVE>{

                    "\n"         { BEGIN(INITIAL); }
                    "\\\n"       {}
                    .            {}
                    
}

<MULTI_LINE_REMOVE>{      

                    "*/"         { BEGIN(INITIAL); }
                    .            {}
}

<INCLUDE>{
                    ">"          { ECHO; BEGIN(INITIAL); }
                    .            { ECHO; }
}

<STRING>{
                    "\""         { ECHO; BEGIN(INITIAL); }
                    .            { ECHO; }          
}

<DOXYGEN_SINGLE>{
                    "\n"         { ECHO; BEGIN(INITIAL); }
                    "\\\n"       { ECHO; }
                    .            { ECHO; }
}



%%

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Insufficient number of arguments! 1. input 2. leave doxygen comments\n");
        exit(1);
    }

    if (argc > 2 ) doxygen = 1;

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Couldn't open the file! :(\n");
        exit(1);
    }

    yyin = fp;

    while (yylex());

    fclose(fp);
    return 0;
}

