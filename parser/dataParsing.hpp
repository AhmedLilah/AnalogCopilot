#pragma once

#include <filesystem>
#include <fstream>
#include <ranges>
#include <print>
#include <iostream>
#include <optional>

#include "../shared/globalStructs.hpp"
#include "../misc/misc.hpp"

auto parseData(CommonPaths const commonPaths) -> std::optional<VgsSweepResults> {
        std::ifstream resultsFile(commonPaths.simulationFilePath);

        VgsSweepResults vgsSweepResults{};

        if (!resultsFile.is_open()) {
                std::println(std::cerr, "Error: Could not open file: {}", commonPaths.simulationFilePath.string());
        } else {
                std::string line;
                while (std::getline(resultsFile, line)) {
                        auto trimmedLine = trimLeadingAndTraillingSpaces(line);

                        auto values = trimmedLine 
                                | std::views::split(std::string_view("  "))
                                | std::views::transform([](auto&& subrange) { return std::string(subrange.begin(), subrange.end()); })
                                // | std::views::filter([](auto && str) {return str.length();})
                                | std::views::transform([](const std::string& numStr) { return std::stod(numStr); })
                                | std::ranges::to<std::vector<double>>();

                        vgsSweepResults.vgs_vect.push_back(values[0]);
                        vgsSweepResults.id_vect.push_back(values[1]);
                        vgsSweepResults.gm_vect.push_back(values[3]);
                        vgsSweepResults.gds_vect.push_back(values[5]);
                        vgsSweepResults.vth_vect.push_back(values[7]);
                        vgsSweepResults.gm_id_vect.push_back(values[3]/values[1]);
                        vgsSweepResults.gm_gds_vect.push_back(values[3]/values[5]);
                        vgsSweepResults.id_w_vect.push_back(values[1] * 10e6);
                }

                resultsFile.close();
                return vgsSweepResults;
        }

        return std::nullopt;
}
