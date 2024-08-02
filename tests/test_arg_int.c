#include "cmdline.h"
#include "tests.h"

int main(void) {
    int holder;
    int argc = 3;
    char *argv[3] = {"test", "-c", "2"};
    ASSERT_TRUE(
        cmdline_register_arg("-c", NULL, INT, VALUE(3), HOLDER(holder), NULL));
    ASSERT_TRUE(cmdline_digest(argc, argv));
    ASSERT(holder == 2);

    argv[2] = "0";
    ASSERT_TRUE(cmdline_digest(argc, argv));
    ASSERT(holder == 0);

    argv[2] = "-123";
    ASSERT_TRUE(cmdline_digest(argc, argv));
    ASSERT(holder == -123);
}
