#pragma once

#include <expected>
#include <print>
#include <iostream>
#include <tcl.h>


auto initTclInterp() -> std::expected<Tcl_Interp *, std::string> {
        char *pstr;
        FILE *infile;
        int retval;
        int rc;
        size_t filesize;

        Tcl_Interp * tclInterpPtr = Tcl_CreateInterp();

        if (tclInterpPtr == nullptr) {
                return std::unexpected("Could not create interpreter.");
        }

        return tclInterpPtr;
}

auto executeTclScript(std::string tclScript) -> bool {
        auto optionalTclInterpPtr = initTclInterp();

        if (not optionalTclInterpPtr) {
                std::println(std::cerr, "{}", optionalTclInterpPtr.error());
        }

        Tcl_Interp * tclInterpPtr = optionalTclInterpPtr.value();
        return Tcl_Eval(tclInterpPtr, tclScript.c_str()) == TCL_OK;
}
