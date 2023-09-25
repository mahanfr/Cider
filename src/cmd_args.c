#include "templates.h"
#include "cmd_args.h"
#include "../libs/mystd.h"

#define APPNAME "Cider"
#define VERSION "0.0.1-beta"
#define DEBUG 1

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
