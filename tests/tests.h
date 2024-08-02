#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT(X) assert(X)
#define ASSERT_TRUE(X) ASSERT(X == true)
#define ASSERT_FALSE(X) ASSERT(X == false)
