#include "cmdline.h"
#include <stdio.h>

int main(int argc, char **argv) {
    char *holder = NULL;
    cmdline_set_usage("main [options]");
    cmdline_set_overview("Test cmdline app.");
    cmdline_register_arg(
        "-c", "--config", STR, VALUE("DEFAULT CONFIG"), HOLDER(holder),
        "This is some text for help about the '--config' argument. Some text "
        "some text some text some text some text some text some text some text "
        "some text some text some text some text some text ");
    cmdline_register_arg(
        "-s", "--somefile", INT, VALUE(123), HOLDER(holder),
        "This is some text for help about the '--config' argument. Some text "
        "some text some text some text some text some text some text some text "
        "some text some text some text some text some text ");
    cmdline_digest(argc, argv);
    if (holder)
        printf("%s\n", holder);
}
