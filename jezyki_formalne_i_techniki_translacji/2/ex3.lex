
%{
    int doxygen = 0;
%}

%x COMMENT_INIT SINGLE_LINE_REMOVE MULTI_LINE_REMOVE INCLUDE STRING

%%
<INITIAL>{
                "<"              { ECHO; BEGIN(INCLUDE); }
                "\""             { ECHO; BEGIN(STRING); }

                "//"             { BEGIN(SINGLE_LINE_REMOVE); }

                "///"|"//!"      { if ( doxygen ) {
                                        ECHO;
                                        BEGIN(INITIAL);
                                    } else {
                                        BEGIN(SINGLE_LINE_REMOVE);
                                    }
                                 }

                "/*"             { BEGIN(MULTI_LINE_REMOVE); }

                "/**"|"/*!"      { if ( doxygen ) {
                                        ECHO;
                                        BEGIN(INITIAL);
                                    } else {
                                        BEGIN(MULTI_LINE_REMOVE);
                                    } 
                                 }

                .                { ECHO; }
}

<SINGLE_LINE_REMOVE>{

                    "\n"         { BEGIN(INITIAL); }
                    .            {}
                    
}

<MULTI_LINE_REMOVE>{      

                    "*/"|"*/\n"  { BEGIN(INITIAL); }
                    .|\n         {}
}

<INCLUDE>{
                    ">"          { ECHO; BEGIN(INITIAL); }
                    .            { ECHO; }
}

<STRING>{
                    "\""         { ECHO; BEGIN(INITIAL); }
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

