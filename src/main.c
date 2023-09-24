#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MYSTD_IMPLEMENTATION
#include "../libs/mystd.h"

#define APPNAME "Cider"
#define VERSION "0.0.1-beta"
#define DEBUG 1

#define SRCFOLDER "src/"
#define MAINFILE "main.c"

int cla_help() {
    static char* help = 
        APPNAME
        VERSION
        " Project Manager For C\n"
        "Copyright 2023 - 2024 Under MIT license\n"
        "usage:\n"
        "Cider <Command> [options] args\n"
        "init                      initiation of the project\n"
        "  -b      | --binary      init for a binary project\n"
        "  -l      | --library     init for a library project\n"
        "global options:\n"
        "  help    | --help        help\n"
        "  version | --version     version\n";
    return fprintf(stdout, "%s",help);
}

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

void cla_init(int index, int args, char **argv) {
    if (index >= args) {
        set_binary_template("./");
        return;
    }
    if (strcmp(argv[index], "--binary") == 0 | strcmp(argv[index], "-b") == 0) {
        index++;
        if (index >= args) return;
        set_binary_template(argv[index]);
    } else if (strcmp(argv[index], "--library") == 0 | strcmp(argv[index], "-l") == 0) {
        printf("TODO: setup library template!\n");
        index++;
        // if (index >= args) return;
        // set_binary_template(argv[index]);
    }else {
        if (index >= args) return;
        set_binary_template(argv[index]);
    }
}

void cla(int args, char **argv) {
    int index = 1;
    if(args > 1) {
        if(strcmp(argv[index],"init") == 0) {
            cla_init(++index, args, argv);
        }
    } else {
        cla_help();
    }
}

int main(int args, char **argv) {
    cla(args,argv);
    return 0;
}
