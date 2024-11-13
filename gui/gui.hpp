#pragma once

#include <print>

#include <tcl.h>
#include <tk.h>

#include "../tcl/tcl.hpp"
#include "../simulator/simulator.hpp"
#include "tclDecls.h"
#include "tkDecls.h"

void generateGui(Tcl_Interp* interp) {
        // creating the tcl binding to the c++ runSimulation function
        Tcl_CreateObjCommand(interp, "runSimulation", runSimulation, nullptr, nullptr);

        // Initialize the Tk package
        Tk_MainWindow(interp);
        Tcl_Eval(interp, "package require Tk");

        // Create the main window
        Tcl_Eval(interp, "wm title . \"Analog Copilot\"");

        // Create the frame for the top controls (Tech, Device, Corner, Temp)
        Tcl_Eval(interp, "frame .top");
        Tcl_Eval(interp, "pack .top -side top -fill x");
        Tcl_SetVar(interp, "PDKDevices", "nfet_01v8_lvt nfet_01v8 nfet_03v3_nvt nfet_05v0_nvt nfet_05v0_nvt nfet_g5v0d10v5 nfet_g5v0d16v0 nfet_20v0 nfet_20v0_iso nfet_20v0_nvt nfet_20v0_zvt pfet_01v8_lvt pfet_01v8 pfet_01v8_hvt pfet_g5v0d10v5 pfet_g5v0d16v0 pfet_20v0", 0);
        Tcl_SetVar(interp, "modelName", "nfet_01v8", 0);
        Tcl_SetVar(interp, "corner", "tt", 0);
        Tcl_SetVar(interp, "temp", "27", 0);
        Tcl_SetVar(interp, "libraryIncludePath", "/usr/local/share/pdk/sky130A/libs.tech/combined/sky130.lib.spice", 0);
        Tcl_SetVar(interp, "W", "10", 0);
        Tcl_SetVar(interp, "L", "1", 0);
        Tcl_SetVar(interp, "NFIN", "1", 0);
        Tcl_SetVar(interp, "NF", "1", 0);
        Tcl_SetVar(interp, "M", "1", 0);
        Tcl_SetVar(interp, "VGS", "0.75", 0);
        Tcl_SetVar(interp, "VDS", "1", 0);
        Tcl_SetVar(interp, "VSB", "0", 0);

        Tcl_SetVar(interp, "id_data", "", 0); 
        Tcl_SetVar(interp, "gm_data", "", 0); 
        Tcl_SetVar(interp, "gds_data", "", 0); 
        Tcl_SetVar(interp, "vth_data", "", 0); 
        Tcl_SetVar(interp, "gm_id_data", "", 0); 
        Tcl_SetVar(interp, "gm_gds_data", "", 0); 
        Tcl_SetVar(interp, "id_w_data", "", 0); 

        // Create the frame for the first row (PDK)
        Tcl_Eval(interp, "frame .top.row1");
        Tcl_Eval(interp, "pack .top.row1 -side top -fill x");

        // Device dropdown menu
        Tcl_Eval(interp, "label .top.row1.deviceLabel -text \"Model Name\"");
        Tcl_Eval(interp, "pack .top.row1.deviceLabel -side left");

        // Create a combobox for device selection
        Tcl_Eval(interp, "ttk::combobox .top.row1.deviceEntry -width 20 -textvariable modelName");
        Tcl_Eval(interp, ".top.row1.deviceEntry configure -values $PDKDevices");
        Tcl_Eval(interp, "pack .top.row1.deviceEntry -side left -fill x");

        // Corner dropdown menu
        Tcl_Eval(interp, "label .top.row1.cornerLabel -text \"Corner\"");
        Tcl_Eval(interp, "entry .top.row1.cornerEntry -width 5 -textvariable corner");
        Tcl_Eval(interp, "pack .top.row1.cornerLabel -side left");
        Tcl_Eval(interp, "pack .top.row1.cornerEntry -side left -fill x");

        // Temp input
        Tcl_Eval(interp, "label .top.row1.tempLabel -text \"Temp\"");
        Tcl_Eval(interp, "entry .top.row1.tempEntry -width 5 -textvariable temp");
        Tcl_Eval(interp, "pack .top.row1.tempLabel -side left");
        Tcl_Eval(interp, "pack .top.row1.tempEntry -side left -fill x");

        // Frame for the second row (Library Path)
        Tcl_Eval(interp, "frame .top.row2");
        Tcl_Eval(interp, "pack .top.row2 -side top -fill x");

        Tcl_Eval(interp, "label .top.row2.libraryPathLabel -text \"Library Include Path\"");
        Tcl_Eval(interp, "entry .top.row2.libraryPathEntry -width 20 -textvariable libraryIncludePath");
        Tcl_Eval(interp, "pack .top.row2.libraryPathLabel -side left");
        Tcl_Eval(interp, "pack .top.row2.libraryPathEntry -side left -fill x -expand true");

        // Add a horizontal line using a canvas
        Tcl_Eval(interp, "canvas .top.line -height 1 -bg \"gray\" -width 500");
        Tcl_Eval(interp, "pack .top.line -side top -fill x");

        // Create the frame for the results and plot
        Tcl_Eval(interp, "frame .bottom");
        Tcl_Eval(interp, "pack .bottom -side top -fill both -expand true");

        // Create the frame for the parameters and input fields
        Tcl_Eval(interp, "frame .left");
        Tcl_Eval(interp, "pack .left -side left -fill y");

        // Frame for each parameter
        std::vector<std::string> params = {"W", "L", "NFIN", "NF", "M", "VGS", "VDS", "VSB"};
        for (const auto& param : params) {
                std::string command;
                command += "frame .left.row" + param;
                Tcl_Eval(interp, command.c_str());
                command = "label .left.row" + param + ".label" + param + " -text " + param;
                Tcl_Eval(interp, command.c_str());
                command = "entry .left.row" + param + ".entry" + param + " -width 10 -textvariable " + param;
                Tcl_Eval(interp, command.c_str());
                Tcl_Eval(interp, ("pack .left.row" + param + ".label" + param + " -side left").c_str());
                Tcl_Eval(interp, ("pack .left.row" + param + ".entry" + param + " -side right").c_str());
                Tcl_Eval(interp, ("pack .left.row" + param + " -side top -anchor w -fill x").c_str());
        }

        // Create the frame for the Run button
        Tcl_Eval(interp, "frame .left.runFrame");
        Tcl_Eval(interp, "pack .left.runFrame -side top -fill x");

        // Run button
        Tcl_Eval(interp, "button .left.runFrame.run -text \"Run\" -width 10 -command {runSimulation}");
        Tcl_Eval(interp, "pack .left.runFrame.run -side top -pady 10 -fill both");

        // Create the frame for the results
        Tcl_Eval(interp, "frame .right");
        Tcl_Eval(interp, "pack .right -side right -fill both -expand true");

        // Create the frame for the results
        Tcl_Eval(interp, "frame .right.results");
        Tcl_Eval(interp, "pack .right.results -side top -fill x");

        // Placeholder for result labels
        Tcl_Eval(interp, "label .right.results.idlabel -text \"ID =\"");
        Tcl_Eval(interp, "label .right.results.iddatalabel -text $id_data");
        Tcl_Eval(interp, "grid .right.results.idlabel -row 0 -column 0 -sticky e");
        Tcl_Eval(interp, "grid .right.results.iddatalabel -row 0 -column 1 -sticky w");

        Tcl_Eval(interp, "label .right.results.gmlabel -text \"gm =\"");
        Tcl_Eval(interp, "label .right.results.gmdatalabel -text $gm_data");
        Tcl_Eval(interp, "grid .right.results.gmlabel -row 1 -column 0 -sticky e");
        Tcl_Eval(interp, "grid .right.results.gmdatalabel -row 1 -column 1 -sticky w");

        Tcl_Eval(interp, "label .right.results.gdslabel -text \"gds =\"");
        Tcl_Eval(interp, "label .right.results.gdsdatalabel -text $gds_data");
        Tcl_Eval(interp, "grid .right.results.gdslabel -row 2 -column 0 -sticky e");
        Tcl_Eval(interp, "grid .right.results.gdsdatalabel -row 2 -column 1 -sticky w");

        Tcl_Eval(interp, "label .right.results.vthlabel -text \"Vth =\"");
        Tcl_Eval(interp, "label .right.results.vthdatalabel -text $vth_data");
        Tcl_Eval(interp, "grid .right.results.vthlabel -row 3 -column 0 -sticky e");
        Tcl_Eval(interp, "grid .right.results.vthdatalabel -row 3 -column 1 -sticky w");


        Tcl_Eval(interp, "label .right.results.gm_idlabel -text \"gm/Id =\"");
        Tcl_Eval(interp, "label .right.results.gm_iddatalabel -text $gm_id_data");
        Tcl_Eval(interp, "grid .right.results.gm_idlabel -row 4 -column 0 -sticky e");
        Tcl_Eval(interp, "grid .right.results.gm_iddatalabel -row 4 -column 1 -sticky w");

        Tcl_Eval(interp, "label .right.results.gm_gdslabel -text \"gm/gds =\"");
        Tcl_Eval(interp, "label .right.results.gm_gdsdatalabel -text $gm_gds_data");
        Tcl_Eval(interp, "grid .right.results.gm_gdslabel -row 5 -column 0 -sticky e");
        Tcl_Eval(interp, "grid .right.results.gm_gdsdatalabel -row 5 -column 1 -sticky w");

        Tcl_Eval(interp, "label .right.results.id_wlabel -text \"Id/W =\"");
        Tcl_Eval(interp, "label .right.results.id_wdatalabel -text $id_w_data");
        Tcl_Eval(interp, "grid .right.results.id_wlabel -row 6 -column 0 -sticky e");
        Tcl_Eval(interp, "grid .right.results.id_wdatalabel -row 6 -column 1 -sticky w");

	Tcl_Eval(interp, "grid columnconfigure .right.results 0 -weight 1");
	Tcl_Eval(interp, "grid columnconfigure .right.results 1 -weight 1");

        // Start the Tk main event loop
        Tcl_Eval(interp, "tkwait window .");
}

