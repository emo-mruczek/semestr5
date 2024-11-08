
%x COMMENT


%%
<INITIAL>{ 
                "--"            { BEGIN(COMMENT); }
                "\""([^"]|"\"\"")*"\""            {ECHO;}
               /* ^[ \t]*\n       {}                empty line */
                .               { ECHO; }
}

<COMMENT>{
                "\n"            { ECHO; BEGIN(INITIAL); }
                .               {}
}
%%

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Insufficient number of arguments! 1. input 2. output\n");
        exit(1);
    }

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

