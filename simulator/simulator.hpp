#pragma once

#include <format>
#include <cstdlib>
#include <filesystem>

#include <tcl.h>

#include "../parser/dataParsing.hpp"
#include "../netlist/netlist.hpp"
#include "../misc/shell.hpp"
#include "../gui/guiUpdate.hpp"


auto runSimulation(ClientData clientData, Tcl_Interp* interp, int objc, Tcl_Obj *const objv[]) -> int {
        CommonPaths commonPaths;
        DeviceSweepNetlistData const globalNetlistData;

        auto const guiInputVars = getGuiInputVars(interp);

        DeviceInstanceData deviceInstanceData{
                .modelName = guiInputVars.modelName,
                .W = guiInputVars.W,
                .L = guiInputVars.L,
                .NFIN = guiInputVars.NFIN,
                .NF = guiInputVars.NF,
                .M = guiInputVars.M,
        };

        auto deviceInstance = generateDeviceInstance(globalNetlistData, deviceInstanceData);

        NetlistInstanceData netlistInstanceData{
                .libraryIncludePath = guiInputVars.libraryIncludePath,
                .corner = guiInputVars.corner,
                .VGS = guiInputVars.VGS,
                .VDS = guiInputVars.VDS,
                .VSB = guiInputVars.VSB,
                .deviceInstance = deviceInstance,
                .deviceSaveModel = std::string("m.xm1.msky130_fd_pr__") + guiInputVars.modelName,
                .analysis = "op",
                .simulationPath = commonPaths.simulationDirectoryPath.string()
        };

        // generating the netlist.
        auto netlist = generateNetlist(globalNetlistData, netlistInstanceData);

        // writing the netlist to a file.
        writeNetlistToFile(netlist, commonPaths);

        // running the simulation.
        std::string simulationCommand = std::format("ngspice -b {} -o {}", commonPaths.netlistFilePath.c_str(), commonPaths.logOutputFilePath.c_str());
        executeShellCommand(simulationCommand);

        // parsing data.
        auto vgsSweepResultsOption = parseData(commonPaths);

        VgsSweepResults vgsSweepResults;
        if (vgsSweepResultsOption.has_value()) {
                vgsSweepResults = vgsSweepResultsOption.value();
        }

        updateGUI(interp, vgsSweepResults);

        return TCL_OK;
}
