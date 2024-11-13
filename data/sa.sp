
        .lib /usr/local/share/pdk/sky130A/libs.tech/combined/sky130.lib.spice tt
        .GLOBAL GND

        .param vgs=0.75 vds=1 vsb=0
        .param SA_WN=10 SA_LN=1

        VGS vgsnet GND {vgs}
        VDS vdsnet GND {vds}
        VSB vsbnet GND {vsb}
        XM1 vdsnet vgsnet vsbnet GND sky130_fd_pr__nfet_01v8 L={SA_LN} W={SA_WN} nf=1 ad='int((nf+1)/2) * W/nf * 0.29' as='int((nf+2)/2) * W/nf * 0.29' pd='2*int((nf+1)/2) * (W/nf + 0.29)' ps='2*int((nf+2)/2) * (W/nf + 0.29)' nrd='0.29 / W' nrs='0.29 / W' sa=0 sb=0 sd=0 mult=1 m=1

        .control
                save v(vgs) v(vds) v(vsb)
                save @m.xm1.msky130_fd_pr__nfet_01v8[id]
                save @m.xm1.msky130_fd_pr__nfet_01v8[gm]
                save @m.xm1.msky130_fd_pr__nfet_01v8[gds]
                save @m.xm1.msky130_fd_pr__nfet_01v8[vth]

                dc VGS 0.001 1 0.01

                let id   = @m.xm1.msky130_fd_pr__nfet_01v8[id]
                let gm   = @m.xm1.msky130_fd_pr__nfet_01v8[gm]
                let gds  = @m.xm1.msky130_fd_pr__nfet_01v8[gds]
                let vth  = @m.xm1.msky130_fd_pr__nfet_01v8[vth]

                wrdata res/sa.txt id gm gds vth
                write res/sa.raw
        .endc
        .end
        
