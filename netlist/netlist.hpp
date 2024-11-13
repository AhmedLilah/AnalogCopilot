#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <print>
#include <iostream>

#include "../shared/globalStructs.hpp"
#include "../misc/misc.hpp"


auto generateDeviceInstance(DeviceSweepNetlistData globalNetlistData, DeviceInstanceData deviceInstanceData) -> std::string {
        auto deviceInstance = globalNetlistData.deviceInstanceTemplate;

        replaceSubStr(deviceInstance, globalNetlistData.deviceInstancePatterns.modelName , deviceInstanceData.modelName);
        replaceSubStr(deviceInstance, globalNetlistData.deviceInstancePatterns.W , deviceInstanceData.W);
        replaceSubStr(deviceInstance, globalNetlistData.deviceInstancePatterns.L , deviceInstanceData.L);
        replaceSubStr(deviceInstance, globalNetlistData.deviceInstancePatterns.NFIN , deviceInstanceData.NFIN);
        replaceSubStr(deviceInstance, globalNetlistData.deviceInstancePatterns.NF , deviceInstanceData.NF);
        replaceSubStr(deviceInstance, globalNetlistData.deviceInstancePatterns.M , deviceInstanceData.M);

        return deviceInstance;
}


auto generateNetlist(DeviceSweepNetlistData globalNetlistData, NetlistInstanceData netlistInstanceData) -> std::string {
        auto netlistInstance = globalNetlistData.netlistTemplate;

        replaceSubStr(netlistInstance, globalNetlistData.netlistPatterns.libraryIncludePath, netlistInstanceData.libraryIncludePath);
        replaceSubStr(netlistInstance, globalNetlistData.netlistPatterns.corner, netlistInstanceData.corner);
        replaceSubStr(netlistInstance, globalNetlistData.netlistPatterns.VGS, netlistInstanceData.VGS);
        replaceSubStr(netlistInstance, globalNetlistData.netlistPatterns.VDS, netlistInstanceData.VDS);
        replaceSubStr(netlistInstance, globalNetlistData.netlistPatterns.VSB, netlistInstanceData.VSB);
        replaceSubStr(netlistInstance, globalNetlistData.netlistPatterns.deviceInstance, netlistInstanceData.deviceInstance);
        replaceSubStr(netlistInstance, globalNetlistData.netlistPatterns.deviceSaveModel, netlistInstanceData.deviceSaveModel);
        replaceSubStr(netlistInstance, globalNetlistData.netlistPatterns.analysis, netlistInstanceData.analysis);
        replaceSubStr(netlistInstance, globalNetlistData.netlistPatterns.simulationPath, netlistInstanceData.simulationPath);

        return netlistInstance;
}

auto writeNetlistToFile(std::string const &netlist, CommonPaths const commonPaths) -> bool {
        std::ofstream netlistFile(commonPaths.netlistFilePath);
        if (!netlistFile) {
                std::println(std::cerr, "Error: Could not open file for writing: {}", commonPaths.netlistFilePath.string()); 
                return false;
        }
        netlistFile << netlist;
        netlistFile.close();
        return true;
}
