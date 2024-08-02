#include "cmdline.h"
#include "tests.h"

int main(void) {
    char *holder;
    int argc = 3;
    char *argv[3] = {"test", "-c", "test"};
    ASSERT_TRUE(
        cmdline_register_arg("-c", NULL, STR, VALUE(""), HOLDER(holder), NULL));
    ASSERT_TRUE(cmdline_digest(argc, argv));
    ASSERT(strcmp(holder, "test") == 0);
}
