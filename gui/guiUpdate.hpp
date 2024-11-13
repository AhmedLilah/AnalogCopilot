#pragma once

#include "../shared/globalStructs.hpp"

#include "tcl.h"
#include <tk.h>

auto getGuiInputVars(Tcl_Interp *interp) -> GuiInputVars {
        GuiInputVars guiInputVars;

        guiInputVars.modelName =  Tcl_GetVar(interp, "modelName", 0);

        guiInputVars.corner = Tcl_GetVar(interp, "corner", 0);
        guiInputVars.temp = Tcl_GetVar(interp, "temp", 0);
        guiInputVars.libraryIncludePath = Tcl_GetVar(interp, "libraryIncludePath", 0);

        guiInputVars.W = std::stod(Tcl_GetVar(interp, "W", 0));
        guiInputVars.L = std::stod(Tcl_GetVar(interp, "L", 0));
        guiInputVars.NFIN = std::stod(Tcl_GetVar(interp, "NFIN", 0));
        guiInputVars.NF = std::stod(Tcl_GetVar(interp, "NF", 0));
        guiInputVars.M = std::stod(Tcl_GetVar(interp, "M", 0));
        guiInputVars.VGS = std::stod(Tcl_GetVar(interp, "VGS", 0));
        guiInputVars.VDS = std::stod(Tcl_GetVar(interp, "VDS", 0));
        guiInputVars.VSB = std::stod(Tcl_GetVar(interp, "VSB", 0));

        return guiInputVars;
}

auto updateGUI(Tcl_Interp *interp, VgsSweepResults vgsSweepResults) -> void {
        // Check if the lists are not empty before accessing elements
        if (!vgsSweepResults.id_vect.empty()) {
                // Get the first elements from the lists for display
                std::string id_data = std::format("{:.3e}", vgsSweepResults.id_vect[0]);;
                std::string gm_data = vgsSweepResults.gm_vect.empty() ? "" : std::format("{:.3e}", vgsSweepResults.gm_vect[0]);;
                std::string gds_data = vgsSweepResults.gds_vect.empty() ? "" : std::format("{:.3e}", vgsSweepResults.gds_vect[0]);;
                std::string vth_data = vgsSweepResults.vth_vect.empty() ? "" : std::format("{:.3e}", vgsSweepResults.vth_vect[0]);;
                std::string gm_id_data = vgsSweepResults.gm_id_vect.empty() ? "" : std::format("{:.3e}", vgsSweepResults.gm_id_vect[0]);;
                std::string gm_gds_data = vgsSweepResults.gm_gds_vect.empty() ? "" : std::format("{:.3e}", vgsSweepResults.gm_gds_vect[0]);;
                std::string id_w_data = vgsSweepResults.id_w_vect.empty() ? "" : std::format("{:.3e}", vgsSweepResults.id_w_vect[0]);;

                // Update the GUI labels using Tcl commands
                Tcl_Eval(interp, (".right.results.iddatalabel configure -text " + id_data).c_str());
                Tcl_Eval(interp, (".right.results.gmdatalabel configure -text " + gm_data).c_str());
                Tcl_Eval(interp, (".right.results.gdsdatalabel configure -text " + gds_data).c_str());
                Tcl_Eval(interp, (".right.results.vthdatalabel configure -text " + vth_data).c_str());
                Tcl_Eval(interp, (".right.results.gm_iddatalabel configure -text " + gm_id_data).c_str());
                Tcl_Eval(interp, (".right.results.gm_gdsdatalabel configure -text " + gm_gds_data).c_str());
                Tcl_Eval(interp, (".right.results.id_wdatalabel configure -text " + id_w_data).c_str());
        }
}
