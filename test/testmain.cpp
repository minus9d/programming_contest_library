#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(int argc, char* const argv[])
{
    FILE *fh = fopen("aaa", "wb");
    fprintf(fh, "aa");

    int result = Catch::Session().run(argc, argv);
    return result;
}
