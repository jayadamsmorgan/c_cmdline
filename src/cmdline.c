#include "cmdline.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *short_names[MAX_ARGS] = {"-h"};
static char *long_names[MAX_ARGS] = {"--help"};
static void *default_values[MAX_ARGS];
static void **holders[MAX_ARGS];
static char *helps[MAX_ARGS] = {"Display help menu."};
static arg_t types[MAX_ARGS] = {TOGGLE};

static int arg_count = 1;

static char *_overview;
static char *_usage;

void cmdline_set_usage(const char *usage) { _usage = (char *)usage; }
void cmdline_set_overview(const char *overview) {
    _overview = (char *)overview;
}

bool cmdline_register_arg(const char *short_name, const char *long_name,
                          arg_t type, const void *default_value,
                          const void **holder, const char *help) {
    if (arg_count >= MAX_ARGS) {
        printf("\nReached the limit of registering arguments, redefine "
               "`MAX_ARGS` for more arguments.\n\n");
        return false;
    }
    if (short_name == NULL && long_name == NULL) {
        printf("\nArgument needs to have either short_name, long_name or "
               "both.\n\n");
        return false;
    }

    int i;
    for (i = 0; i < arg_count; ++i) {
        int cmp_result = 0;
        if (short_name && short_names[i]) {
            cmp_result = strcmp(short_name, short_names[i]);
        } else if (long_name && long_names[i]) {
            cmp_result = strcmp(long_name, long_names[i]);
        }

        if (cmp_result < 0) {
            break;
        }
    }

    for (int j = arg_count; j > i; --j) {
        short_names[j] = short_names[j - 1];
        long_names[j] = long_names[j - 1];
        default_values[j] = default_values[j - 1];
        holders[j] = holders[j - 1];
        types[j] = types[j - 1];
        helps[j] = helps[j - 1];
    }

    short_names[i] = (char *)short_name;
    long_names[i] = (char *)long_name;
    default_values[i] = (void *)default_value;
    holders[i] = (void *)holder;
    types[i] = type;
    helps[i] = (char *)help;
    arg_count++;

    return true;
}

void cmdline_print_help() {
    if (_overview != NULL)
        printf("OVERVIEW: %s\n\n", _overview);
    if (_usage != NULL)
        printf("USAGE: %s\n\n", _usage);
    printf("OPTIONS:\n");
    for (int i = 0; i < arg_count; i++) {
        printf("  ");
        int len = 2;
        if (short_names[i] == NULL) {
            printf("%s", long_names[i]);
            len += strlen(long_names[i]);
        } else if (long_names[i] == NULL) {
            printf("%s", short_names[i]);
            len += strlen(long_names[i]);
        } else {
            printf("%s, %s", short_names[i], long_names[i]);
            len += strlen(short_names[i]) + strlen(long_names[i]) + 2;
        }
        switch (types[i]) {
        case STR:
            printf(" <string>");
            len += 9;
            break;
        case INT:
            printf(" <int>");
            len += 6;
            break;
        case BOOL:
            printf(" <bool>");
            len += 7;
            break;
        case TOGGLE:
            break;
        }
        if (helps[i] == NULL) {
            printf("\n");
            return;
        }
        if (len > 25)
            printf("\n                          %s", helps[i]);
        else {
            int spaces = 26 - len;
            for (int j = 0; j < spaces; j++) {
                printf(" ");
            }
            printf("%s", helps[i]);
        }
        if (default_values[i] == NULL) {
            printf("\n");
            continue;
        }
        printf(" Default value: ");
        switch (types[i]) {
        case STR:
            printf("%s", (char *)default_values[i]);
            break;
        case INT:
            printf("%d", *(int *)&default_values[i]);
            break;
        case BOOL:;
            bool val = *(bool *)&default_values[i];
            if (val) {
                printf("%s", "true");
            } else {
                printf("%s", "false");
            }
            break;
        case TOGGLE:
            break;
        }
        printf("\n");
    }
}

bool cmdline_digest(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        bool arg_found = false;
        for (int j = 0; j < arg_count; j++) {
            if (strcmp("-h", argv[i]) == 0 || strcmp("--help", argv[i]) == 0) {
                cmdline_print_help();
                exit(EXIT_SUCCESS);
            }
            if (strcmp(short_names[j], argv[i]) != 0 &&
                strcmp(long_names[j], argv[i]) != 0) {
                continue;
            }
            arg_found = true;
            if (types[j] == TOGGLE) {
                bool val = !((bool)default_values[j]);
                *holders[j] = (void *)val;
                break;
            }
            if (i >= argc - 1) {
                printf("\n  Expected value for the argument '%s'. Use '-h' or "
                       "'--help' for help.\n\n",
                       argv[i]);
                return false;
            }
            i++;
            switch (types[j]) {
            case STR:
                *holders[j] = argv[i];
                break;
            case BOOL:
                if (strcmp(argv[i], BOOL_TRUE_ARG) == 0) {
                    *holders[j] = (void *)true;
                    break;
                } else if (strcmp(argv[i], BOOL_FALSE_ARG) == 0) {
                    *holders[j] = (void *)false;
                    break;
                } else {
                    printf(
                        "\n  Expected true\\false\\on\\off\\y\\n\\yes\\no for "
                        "boolean argument '%s', got '%s'.\n\n",
                        argv[i - 1], argv[i]);
                    return false;
                }
            case INT:
                // TODO: handle a non-int value since atoi() returns 0
                *holders[j] = (void *)(uintptr_t)atoi(argv[i]);
                break;
            default:
                printf("\n  Error: Unhandled argument type.\n\n");
                return false;
            }
        }
        if (!arg_found) {
            printf(
                "\n  Unknown argument '%s'. Use '-h' or '--help' for help.\n\n",
                argv[i]);
            return false;
        }
    }
    return true;
}
