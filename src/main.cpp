#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdio>
#include "tests/tests_all.h"

int get_seed(int argc, char **argv)
{
    for (int i=1; i<argc; i++)
    {
        if (strncmp("--seed=", argv[i], 7) == 0)
            return atoi(argv[i]+7);
    }

    return time(NULL);
}

int main(int argc, char **argv)
{
    int seed = get_seed(argc, argv);
    printf("SEED: %d\n\n", seed);
    srand(seed);

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}