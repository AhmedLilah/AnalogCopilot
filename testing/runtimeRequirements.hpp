#pragma once

#include <filesystem>
#include "../shared/globalStructs.hpp"

auto testRuntimeRequirements(CommonPaths commonPaths) -> void {
        if (not std::filesystem::exists(commonPaths.abstractHomePath)) {
		std::filesystem::create_directory(commonPaths.abstractHomePath);
	}

        if (not std::filesystem::exists(commonPaths.programHomePath)) {
		std::filesystem::create_directory(commonPaths.programHomePath);
	}

        if (not std::filesystem::exists(commonPaths.netlistDirectoryPath)) {
		std::filesystem::create_directory(commonPaths.netlistDirectoryPath);
	}
        
        if (not std::filesystem::exists(commonPaths.simulationDirectoryPath)) {
		std::filesystem::create_directory(commonPaths.simulationDirectoryPath);
	}

        if (not std::filesystem::exists(commonPaths.logOutputDirectoryPath)) {
		std::filesystem::create_directory(commonPaths.logOutputDirectoryPath);
	}
}
