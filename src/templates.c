#include "../libs/mystd.h"

#define SRCFOLDER "src/"
#define MAINFILE "main.c"

#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include "templates.h"

void set_binary_template(char* path) {
    FILE* src_file = NULL;
    static char* mftemplate = 
        "#include <stdio.h>\n\n"
        "int main(void) {\n"
        "\tprintf(\"Hello World!\\n\");\n"
        "\treturn 0;\n"
        "}\n";
    mkdir(path, 0755);
    if(errno == EEXIST) {
        fprintf(stdout, "[Warning]: folder already exists\n");
    } else if (errno != 0) {
        fprintf(stderr, "[Error]: can not create a folder!\n");
        exit(-1);
    }
    errno = 0;
    char* npath = mystd_strcat(path,SRCFOLDER);
    mkdir(npath, 0755);
    if(errno == EEXIST) {
        fprintf(stdout, "[Warning]: folder already exists\n");
    } else if (errno != 0) {
        fprintf(stderr, "[Error]: can not create a folder!\n");
        exit(-1);
    }
    errno = 0;
    free(npath);

    char* ncmd = mystd_strcat("git init -q ",path);
    if(system(ncmd) < 0) {
        fprintf(stdout, "[Warning]: Git is not installed!\n");
    }
    free(ncmd);

    char* srpath = mystd_strcat(path,SRCFOLDER,MAINFILE);
    if((src_file = fopen(srpath, "w")) < 0) {
        fprintf(stderr, "[Error]: can not create the main file!\n");
        exit(-1);
    }
    fprintf(src_file, "%s", mftemplate);
    fclose(src_file);
    free(srpath);
}
