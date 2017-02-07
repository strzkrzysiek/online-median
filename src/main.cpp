#include <cstdlib>
#include <ctime>
#include "tests/tests_all.h"

int main(int argc, char **argv)
{
    srand(time(NULL));

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}