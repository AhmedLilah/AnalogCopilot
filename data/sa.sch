v {xschem version=3.4.5 file_version=1.2
}
G {}
K {}
V {}
S {}
E {}
N 180 240 180 260 {
lab=GND}
N 180 150 180 180 {
lab=#net1}
N 350 40 350 120 {
lab=#net2}
N 180 40 350 40 {
lab=#net2}
N 180 40 180 90 {
lab=#net2}
N 50 120 50 160 {
lab=#net3}
N 50 120 140 120 {
lab=#net3}
N 50 220 50 250 {
lab=GND}
N 50 250 180 250 {
lab=GND}
N 350 180 350 250 {
lab=GND}
N 180 250 350 250 {
lab=GND}
N 180 120 260 120 {
lab=GND}
N 260 120 260 250 {
lab=GND}
C {vsource.sym} 50 190 0 0 {name=VGS value=\{vgs\} savecurrent=false}
C {vsource.sym} 350 150 0 0 {name=VDS value=\{vds\} savecurrent=false}
C {vsource.sym} 180 210 0 0 {name=VSB value=\{vsb\} savecurrent=false}
C {gnd.sym} 180 260 0 0 {name=l1 lab=GND}
C {sky130_fd_pr/nfet_01v8.sym} 160 120 0 0 {name=M1
W=\{SA_W\}
L=\{SA_L\}
nf=\{SA_NF\}
mult=\{SA_M\}
ad="'int((nf+1)/2) * W/nf * 0.29'" 
pd="'2*int((nf+1)/2) * (W/nf + 0.29)'"
as="'int((nf+2)/2) * W/nf * 0.29'" 
ps="'2*int((nf+2)/2) * (W/nf + 0.29)'"
nrd="'0.29 / W'" nrs="'0.29 / W'"
sa=0 sb=0 sd=0
model=nfet_01v8
spiceprefix=X
}
C {code_shown.sym} 460 160 0 0 {name=AnalysisAndSave 
only_toplevel=false
spice_ignore=flase
value="
.param vgs=0.75 vds=1 vsb=0
.param SA_W=10 SA_L=1 SA_NF=1 SA_M=1
.control
	save v(vgs) v(vds) v(vsb)
	save @m.xm1.msky130_fd_pr__nfet_01v8[id]
	save @m.xm1.msky130_fd_pr__nfet_01v8[gm]
	save @m.xm1.msky130_fd_pr__nfet_01v8[gds]
	
	OP
	let idn	 = @m.xm1.msky130_fd_pr__nfet_01v8[id]
	let gmn	 = @m.xm1.msky130_fd_pr__nfet_01v8[gm]
	let gdsn = @m.xm1.msky130_fd_pr__nfet_01v8[gds]
	let vthn = @m.xm1.msky130_fd_pr__nfet_01v8[vth]
	
	write sa.raw
.endc
"}
C {code_shown.sym} 460 60 0 0 {name=TechnologyFiles 
only_toplevel=false 
format="tcleval( @value )"
value="
.lib $::SKYWATER_MODELS/sky130.lib.spice tt
"}
