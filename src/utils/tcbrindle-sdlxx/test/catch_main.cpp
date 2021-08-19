
#include "SDL.h"

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

extern "C" int main(int argc, char** argv) {
    return Catch::Session().run(argc, argv);
}
