#ifndef CMDLINE_H
#define CMDLINE_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdbool.h>

#ifndef MAX_ARGS
#define MAX_ARGS 100
#endif // MAX_ARGS

#ifndef BOOL_TRUE_ARG
#define BOOL_TRUE_ARG "true"
#endif // BOOL_TRUE_ARG

#ifndef BOOL_FALSE_ARG
#define BOOL_FALSE_ARG "false"
#endif // BOOL_FALSE_ARG

#define HOLDER(X) (const void **)&(X)
#define VALUE(X) (const void *)(X)

typedef enum { STR, INT, BOOL, TOGGLE } arg_t;

void cmdline_print_help();

bool cmdline_register_arg(const char *short_name, const char *long_name,
                          arg_t type, const void *default_value,
                          const void **holder, const char *help);

bool cmdline_digest(int argc, char **argv);

void cmdline_set_usage(const char *usage);

void cmdline_set_overview(const char *overview);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // CMDLINE_H
