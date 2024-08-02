#include "cmdline.h"
#include "tests.h"

int main(void) {
    bool holder = true;
    int argc = 3;
    char *argv[3] = {"test", "-c", BOOL_FALSE_ARG};
    ASSERT_TRUE(cmdline_register_arg("-c", NULL, BOOL, VALUE(true),
                                     HOLDER(holder), NULL));
    ASSERT_TRUE(cmdline_digest(argc, argv));
    ASSERT_FALSE(holder);

    argv[2] = BOOL_TRUE_ARG;
    ASSERT_TRUE(cmdline_digest(argc, argv));
    ASSERT_TRUE(holder);
}
