#pragma once

#include <print>
#include <iostream>

#include <tcl.h>
#include <tk.h>

#include "gui.hpp"
#include "tclDecls.h"
#include "tkDecls.h"

auto runApplication() -> void {
        // Initialize Tcl and Tk
        Tcl_Interp *interp = Tcl_CreateInterp();
        if (Tcl_Init(interp) == TCL_ERROR) {
                std::cerr << "Tcl_Init failed: " << Tcl_GetStringResult(interp) << std::endl;
                return;
        }

        if (Tk_Init(interp) == TCL_ERROR) {
                std::cerr << "Tk_Init failed: " << Tcl_GetStringResult(interp) << std::endl;
                return;
        }

        // Create a Tk main window
        Tk_Window mainWindow = Tk_CreateWindow(interp, nullptr, "My Tk Window", nullptr);
        if (!mainWindow) {
                std::cerr << "Failed to create main window: " << Tcl_GetStringResult(interp) << std::endl;
                return;
        }

        Tk_GeometryRequest(mainWindow, 400, 300);

        // draws the Gui elements
        generateGui(interp);

        // Run tk event loop
        Tk_MainLoop();

        // Cleanup
        Tcl_DeleteInterp(interp);
}
