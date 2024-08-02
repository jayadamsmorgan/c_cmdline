#include "cmdline.h"
#include "tests.h"

int main(void) {
    bool holder = false;
    int argc = 2;
    char *argv[2] = {"test", "-c"};
    ASSERT_TRUE(cmdline_register_arg("-c", NULL, TOGGLE, VALUE(false),
                                     HOLDER(holder), NULL));
    ASSERT_TRUE(cmdline_digest(argc, argv));
    ASSERT_TRUE(holder);
}
