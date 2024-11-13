#include <print>

#include "misc/types.hpp"
#include "gui/programEntry.hpp"
#include "testing/runtimeRequirements.hpp"

auto main() -> s32 {
        CommonPaths commonPaths;
        testRuntimeRequirements(commonPaths);
        runApplication();
        return 0;
}
