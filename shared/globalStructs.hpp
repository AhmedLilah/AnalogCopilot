#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <cstdlib>

static std::filesystem::path userHome = std::getenv("HOME");
static std::filesystem::path programHome = userHome/".Abstract/SA";

struct CommonPaths {
        std::filesystem::path programHomePath = programHome;
        std::filesystem::path netlistDirectoryPath = programHome/"Netlist";
        std::filesystem::path logOutputDirectoryPath = programHome/"Log";
        std::filesystem::path simulationDirectoryPath = programHome/"Simulation";
        std::filesystem::path logOutputFilePath = programHome/"Log/simulator.log";
        std::filesystem::path netlistFilePath = programHome/"Netlist/netlist.sp";
        std::filesystem::path simulationFilePath = programHome/"Simulation/simulationResults.txt";
};

enum class DOFMode {
        VGS,
        GmId,
};

struct GuiInputVars {
        std::string modelName {};
        std::string corner {};
        std::string temp {};
        std::string libraryIncludePath {};
        double W {};
        double L {};
        double NFIN {};
        double NF {};
        double M {};
        double VGS {};
        double VDS {};
        double VSB {};
};

struct NormalDOF {
        double W {};
        double L {};
        double NFIN {};
        double NF {};
        double M {};
        double VGS {};
        double VDS {};
        double VSB {};
};

struct GmIdDOF {
        double W {};
        double L {};
        double NFIN {};
        double NF {};
        double M {};
        double GmId {};
        double VDS {};
        double VSB {};
};


struct VgsSweepResults {
        std::vector<double> vgs_vect {};
        std::vector<double> id_vect {};
        std::vector<double> gm_vect {};
        std::vector<double> gds_vect {};
        std::vector<double> vth_vect {};
        std::vector<double> gm_id_vect {};
        std::vector<double> gm_gds_vect {};
        std::vector<double> id_w_vect {};
};

struct DeviceInstanceData {
        std::string modelName {};
        double W {};
        double L {};
        double NFIN {};
        double NF {};
        double M {};
};

struct NetlistInstanceData {
        std::string libraryIncludePath {};
        std::string corner {};
        double VGS {};
        double VDS {};
        double VSB {};
        std::string deviceInstance {};
        std::string deviceSaveModel{};
        std::string analysis {};
        std::string simulationPath {};
};

struct DeviceInstancePatterns {
        std::string const modelName {"__DEVICEMODELNAME__"};
        std::string const W {"__W__"};
        std::string const L {"__L__"};
        std::string const NFIN {"__NFIN__"};
        std::string const NF {"__NF__"};
        std::string const M {"__M__"};
};

struct NetlistPatterns {
        std::string const libraryIncludePath {"__LIBRARYINCLUDEPATH__"};
        std::string const corner {"__CORNER__"};
        std::string const VGS {"__VGS__"};
        std::string const VDS {"__VDS__"};
        std::string const VSB {"__VSB__"};
        std::string const deviceInstance {"__DEVICEINSTANCE__"};
        std::string const deviceSaveModel{"__DEVICESAVEMODEL__"};
        std::string const analysis {"__ANALYSIS__"};
        std::string const simulationPath {"__SIMULATOINFILEPATH__"};
};

struct DeviceSweepNetlistData {
        DeviceInstancePatterns deviceInstancePatterns;

        std::string const deviceInstanceTemplate = "XM1 dnet gnet snet bnet sky130_fd_pr____DEVICEMODELNAME__ L=__L__ W=__W__ nf=__NF__ ad='int((nf+1)/2) * W/nf * 0.29' as='int((nf+2)/2) * W/nf * 0.29' pd='2*int((nf+1)/2) * (W/nf + 0.29)' ps='2*int((nf+2)/2) * (W/nf + 0.29)' nrd='0.29 / W' nrs='0.29 / W' sa=0 sb=0 sd=0 mult=__M__ m=__M__";

        NetlistPatterns const netlistPatterns;

        std::string const netlistTemplate = 
                ".lib __LIBRARYINCLUDEPATH__ __CORNER__\n"
                ".GLOBAL GND\n"
                "\n"
                ".param vgs=__VGS__ vds=__VDS__ vsb=__VSB__\n"
                "\n"
                "VGS gnet snet {vgs}\n"
                "VDS dnet snet {vds}\n"
                "VSB snet bnet {vsb}\n"
                "VBG bnet GND 0\n"
                "\n"
                "__DEVICEINSTANCE__\n"
                "\n"
                ".control\n"
                "        save v(vgs) v(vds) v(vsb)\n"
                "        save @__DEVICESAVEMODEL__[id]\n"
                "        save @__DEVICESAVEMODEL__[gm]\n"
                "        save @__DEVICESAVEMODEL__[gds]\n"
                "        save @__DEVICESAVEMODEL__[vth]\n"
                "\n"
                "        __ANALYSIS__\n"
                "\n"
                "        let id   = @__DEVICESAVEMODEL__[id]\n"
                "        let gm   = @__DEVICESAVEMODEL__[gm]\n"
                "        let gds  = @__DEVICESAVEMODEL__[gds]\n"
                "        let vth  = @__DEVICESAVEMODEL__[vth]\n"
                "\n"
                "        wrdata __SIMULATOINFILEPATH__/simulationResults.txt id gm gds vth\n"
                "        write  __SIMULATOINFILEPATH__/simulationResults.raw\n"
                ".endc\n"
                "\n"
                ".end\n" ;
};

struct LUTNetlistPatterns {
        std::string const libraryIncludePath {"__LIBRARYINCLUDEPATH__"};
        std::string const corner {"__CORNER__"};
        std::string const VGS {"__VGS__"};
        std::string const VGSStart {"__VGS_START__"};
        std::string const VGSStep {"__VGS_STEP__"};
        std::string const VGSStop {"__VGS_STOP__"};
        std::string const VDS {"__VDS__"};
        std::string const VDSStart {"__VDS_START__"};
        std::string const VDSStep {"__VDS_STEP__"};
        std::string const VDSStop {"__VDS_STOP__"};
        std::string const VSB {"__VSB__"};
        std::string const VSBStart {"__VSB_START__"};
        std::string const VSBStep {"__VSB_STEP__"};
        std::string const VSBStop {"__VSB_STOP__"};
        std::string const deviceInstance {"__DEVICEINSTANCE__"};
        std::string const deviceSaveModel{"__DEVICESAVEMODEL__"};
        std::string const analysis {"__ANALYSIS__"};
        std::string const simulationPath {"__SIMULATOINFILEPATH__"};
};

struct LUTNetlistData {
        DeviceInstancePatterns deviceInstancePatterns;

        std::string const deviceInstanceTemplate = "XM1 dnet gnet snet bnet sky130_fd_pr____DEVICEMODELNAME__ L=__L__ W=__W__ nf=__NF__ ad='int((nf+1)/2) * W/nf * 0.29' as='int((nf+2)/2) * W/nf * 0.29' pd='2*int((nf+1)/2) * (W/nf + 0.29)' ps='2*int((nf+2)/2) * (W/nf + 0.29)' nrd='0.29 / W' nrs='0.29 / W' sa=0 sb=0 sd=0 mult=__M__ m=__M__";

        NetlistPatterns const netlistPatterns;

        std::string const netlistTemplate = 
		".lib __LIBRARYINCLUDEPATH__ __CORNER__\n"
		".GLOBAL GND\n"
		"\n"
		".param vgsparam=__VGS__ vdsparam=__VDS__ vsbparam=__VSB__\n"
		".param lparam=__LPARAM__\n"
		"\n"
		"VGSSource gnet snet 0\n"
		"VDSSource dnet snet 0\n"
		"VSBSource snet bnet 0\n"
		"VBGSource bnet GND  0\n"
		"\n"
                "__DEVICEINSTANCE__\n"
		"\n"
		".control\n"
		"\n"
		"        set wr_singlescale\n"
		"\n"
		"        let L_START = __L_START__\n"
		"        let L_STOP  = __L_STOP__\n"
		"        let L_STEP  = __L_STEP__\n"
		"        let L       =   L_START\n"
		"\n"
		"        while L le L_STOP\n"
		"\n"
		"                alterparam lparam=L\n"
		"\n"
		"                let VSB_START = __VSB_START__\n"
		"                let VSB_STOP  = __VSB_STOP__\n"
		"                let VSB_STEP  = __VSB_STEP__\n"
		"                let VSB       =   VSB_START\n"
		"\n"
		"                while VSB le VSB_STOP\n"
		"\n"
		"                        alter VSBSource VSB\n"
		"\n"
		"                        let VDS_START = __VDS_START__\n"
		"                        let VDS_STOP  = __VDS_STOP__\n"
		"                        let VDS_STEP  = __VDS_STEP__\n"
		"                        let VDS       =   VDS_START\n"
		"\n"
		"                        while VDS le VDS_STOP\n"
		"\n"
		"                                alter VDSSource VDS\n"
		"\n"
		"                                save v(vgs) v(vds) v(vsb)\n"
		"                                save @__DEVICESAVEMODEL__[id]\n"
		"                                save @__DEVICESAVEMODEL__[gm]\n"
		"                                save @__DEVICESAVEMODEL__[gds]\n"
		"                                save @__DEVICESAVEMODEL__[vth]\n"
		"\n"
		"                                dc VGSSource __VGS_START__ __VGS_STOP__ __VGS_STEP__\n"
		"\n"
		"                                let id   = @__DEVICESAVEMODEL__[id]\n"
		"                                let gm   = @__DEVICESAVEMODEL__[gm]\n"
		"                                let gds  = @__DEVICESAVEMODEL__[gds]\n"
		"                                let vth  = @__DEVICESAVEMODEL__[vth]\n"
		"\n"
		"                                let cgs  = @__DEVICESAVEMODEL__[cgs]\n"
		"                                let cgd  = @__DEVICESAVEMODEL__[cgd]\n"
		"                                let csb  = @__DEVICESAVEMODEL__[csb]\n"
		"\n"
		"                                wrdata __SIMULATOINFILEPATH__/simulationResults.txt id gm gds vth cgs cgd csb\n"
		"\n"
		"                                let VDS = VDS + VDS_STEP\n"
		"\n"
		"                        end\n"
		"\n"
		"                        let VSB = VSB + VSB_STEP\n"
		"\n"
		"                end\n"
		"\n"
		"                if (L le (__L_STOP__ * 0.1))\n"
		"                        let L = L + L_STEP\n"
		"                elseif (L le (__L_STOP__ * 0.25))\n"
		"                        let L = L + (2.5*L_STEP)\n"
		"                elseif (L le (__L_STOP__ * 0.5))\n"
		"                        let L = L + (5*L_STEP)\n"
		"                else\n"
		"                        let L = L + (10*L_STEP)\n"
		"                endif\n"
		"\n"
		"        end\n"
		"\n"
		".endc\n"
		"\n"
		".end\n";
};
