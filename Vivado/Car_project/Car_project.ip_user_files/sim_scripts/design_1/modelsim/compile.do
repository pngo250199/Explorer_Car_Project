vlib modelsim_lib/work
vlib modelsim_lib/msim

vlib modelsim_lib/msim/xilinx_vip
vlib modelsim_lib/msim/xpm
vlib modelsim_lib/msim/axi_infrastructure_v1_1_0
vlib modelsim_lib/msim/axi_vip_v1_1_23
vlib modelsim_lib/msim/processing_system7_vip_v1_0_25
vlib modelsim_lib/msim/xil_defaultlib
vlib modelsim_lib/msim/smartconnect_v1_0
vlib modelsim_lib/msim/proc_sys_reset_v5_0_17
vlib modelsim_lib/msim/axi_register_slice_v2_1_37

vmap xilinx_vip modelsim_lib/msim/xilinx_vip
vmap xpm modelsim_lib/msim/xpm
vmap axi_infrastructure_v1_1_0 modelsim_lib/msim/axi_infrastructure_v1_1_0
vmap axi_vip_v1_1_23 modelsim_lib/msim/axi_vip_v1_1_23
vmap processing_system7_vip_v1_0_25 modelsim_lib/msim/processing_system7_vip_v1_0_25
vmap xil_defaultlib modelsim_lib/msim/xil_defaultlib
vmap smartconnect_v1_0 modelsim_lib/msim/smartconnect_v1_0
vmap proc_sys_reset_v5_0_17 modelsim_lib/msim/proc_sys_reset_v5_0_17
vmap axi_register_slice_v2_1_37 modelsim_lib/msim/axi_register_slice_v2_1_37

vlog -work xilinx_vip -64 -incr -mfcu  -sv -L axi_vip_v1_1_23 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_25 -L xilinx_vip "+incdir+/home/henry/xilinx/2026.1/data/xilinx_vip/include" \
"/home/henry/xilinx/2026.1/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"/home/henry/xilinx/2026.1/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"/home/henry/xilinx/2026.1/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"/home/henry/xilinx/2026.1/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"/home/henry/xilinx/2026.1/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"/home/henry/xilinx/2026.1/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"/home/henry/xilinx/2026.1/data/xilinx_vip/hdl/axi_vip_if.sv" \
"/home/henry/xilinx/2026.1/data/xilinx_vip/hdl/clk_vip_if.sv" \
"/home/henry/xilinx/2026.1/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xpm -64 -incr -mfcu  -sv -L axi_vip_v1_1_23 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_25 -L xilinx_vip "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/df05/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/00fe/hdl/verilog" "+incdir+../../../../../../../xilinx/2026.1/data/rsb/busdef" "+incdir+/home/henry/xilinx/2026.1/data/xilinx_vip/include" \
"/home/henry/xilinx/2026.1/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"/home/henry/xilinx/2026.1/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"/home/henry/xilinx/2026.1/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -64 -93  \
"/home/henry/xilinx/2026.1/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work axi_infrastructure_v1_1_0 -64 -incr -mfcu  "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/df05/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/00fe/hdl/verilog" "+incdir+../../../../../../../xilinx/2026.1/data/rsb/busdef" "+incdir+/home/henry/xilinx/2026.1/data/xilinx_vip/include" \
"../../../../Car_project.gen/sources_1/bd/design_1/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_vip_v1_1_23 -64 -incr -mfcu  -sv -L axi_vip_v1_1_23 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_25 -L xilinx_vip "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/df05/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/00fe/hdl/verilog" "+incdir+../../../../../../../xilinx/2026.1/data/rsb/busdef" "+incdir+/home/henry/xilinx/2026.1/data/xilinx_vip/include" \
"../../../../Car_project.gen/sources_1/bd/design_1/ipshared/4d28/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work processing_system7_vip_v1_0_25 -64 -incr -mfcu  -sv -L axi_vip_v1_1_23 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_25 -L xilinx_vip "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/df05/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/00fe/hdl/verilog" "+incdir+../../../../../../../xilinx/2026.1/data/rsb/busdef" "+incdir+/home/henry/xilinx/2026.1/data/xilinx_vip/include" \
"../../../../Car_project.gen/sources_1/bd/design_1/ipshared/df05/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib -64 -incr -mfcu  "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/df05/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/00fe/hdl/verilog" "+incdir+../../../../../../../xilinx/2026.1/data/rsb/busdef" "+incdir+/home/henry/xilinx/2026.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_processing_system7_0_0/sim/design_1_processing_system7_0_0.v" \
"../../../bd/design_1/ipshared/a4b8/hdl/customIP_slave_lite_v1_0_S00_AXI.v" \
"../../../bd/design_1/ipshared/a4b8/hdl/customIP.v" \
"../../../bd/design_1/ip/design_1_customIP_0_0/sim/design_1_customIP_0_0.v" \
"../../../bd/design_1/ip/design_1_axi_smc_0/bd_0/sim/bd_afc3.v" \

vlog -work smartconnect_v1_0 -64 -incr -mfcu  -sv -L axi_vip_v1_1_23 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_25 -L xilinx_vip "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/df05/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/00fe/hdl/verilog" "+incdir+../../../../../../../xilinx/2026.1/data/rsb/busdef" "+incdir+/home/henry/xilinx/2026.1/data/xilinx_vip/include" \
"../../../../Car_project.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/sc_util_v1_0_vl_rfs.sv" \

vcom -work proc_sys_reset_v5_0_17 -64 -93  \
"../../../../Car_project.gen/sources_1/bd/design_1/ipshared/9438/hdl/proc_sys_reset_v5_0_rfs.vhd" \

vcom -work smartconnect_v1_0 -64 -93  \
"../../../../Car_project.gen/sources_1/bd/design_1/ipshared/21d5/hdl/sc_ultralite_v1_0_rfs.vhd" \

vlog -work smartconnect_v1_0 -64 -incr -mfcu  -sv -L axi_vip_v1_1_23 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_25 -L xilinx_vip "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/df05/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/00fe/hdl/verilog" "+incdir+../../../../../../../xilinx/2026.1/data/rsb/busdef" "+incdir+/home/henry/xilinx/2026.1/data/xilinx_vip/include" \
"../../../../Car_project.gen/sources_1/bd/design_1/ipshared/21d5/hdl/sc_ultralite_v1_0_rfs.sv" \

vlog -work xil_defaultlib -64 -incr -mfcu  -sv -L axi_vip_v1_1_23 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_25 -L xilinx_vip "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/df05/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/00fe/hdl/verilog" "+incdir+../../../../../../../xilinx/2026.1/data/rsb/busdef" "+incdir+/home/henry/xilinx/2026.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_axi_smc_0/bd_0/ip/ip_0/sim/bd_afc3_sc_ul_0.sv" \

vlog -work smartconnect_v1_0 -64 -incr -mfcu  -sv -L axi_vip_v1_1_23 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_25 -L xilinx_vip "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/df05/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/00fe/hdl/verilog" "+incdir+../../../../../../../xilinx/2026.1/data/rsb/busdef" "+incdir+/home/henry/xilinx/2026.1/data/xilinx_vip/include" \
"../../../../Car_project.gen/sources_1/bd/design_1/ipshared/3d9a/hdl/sc_mmu_v1_0_vl_rfs.sv" \
"../../../../Car_project.gen/sources_1/bd/design_1/ipshared/7785/hdl/sc_transaction_regulator_v1_0_vl_rfs.sv" \
"../../../../Car_project.gen/sources_1/bd/design_1/ipshared/3051/hdl/sc_si_converter_v1_0_vl_rfs.sv" \
"../../../../Car_project.gen/sources_1/bd/design_1/ipshared/00fe/hdl/sc_node_v1_0_vl_rfs.sv" \
"../../../../Car_project.gen/sources_1/bd/design_1/ipshared/0848/hdl/sc_switchboard_v1_0_vl_rfs.sv" \
"../../../../Car_project.gen/sources_1/bd/design_1/ipshared/852f/hdl/sc_axi2sc_v1_0_vl_rfs.sv" \
"../../../../Car_project.gen/sources_1/bd/design_1/ipshared/fca9/hdl/sc_sc2axi_v1_0_vl_rfs.sv" \
"../../../../Car_project.gen/sources_1/bd/design_1/ipshared/c7d2/hdl/sc_exit_v1_0_vl_rfs.sv" \

vlog -work axi_register_slice_v2_1_37 -64 -incr -mfcu  "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/df05/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/00fe/hdl/verilog" "+incdir+../../../../../../../xilinx/2026.1/data/rsb/busdef" "+incdir+/home/henry/xilinx/2026.1/data/xilinx_vip/include" \
"../../../../Car_project.gen/sources_1/bd/design_1/ipshared/8c55/hdl/axi_register_slice_v2_1_rfs.v" \

vlog -work xil_defaultlib -64 -incr -mfcu  -sv -L axi_vip_v1_1_23 -L smartconnect_v1_0 -L processing_system7_vip_v1_0_25 -L xilinx_vip "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/df05/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/00fe/hdl/verilog" "+incdir+../../../../../../../xilinx/2026.1/data/rsb/busdef" "+incdir+/home/henry/xilinx/2026.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_axi_smc_0/sim/design_1_axi_smc_0.sv" \

vcom -work xil_defaultlib -64 -93  \
"../../../bd/design_1/ip/design_1_rst_ps7_0_50M_0/sim/design_1_rst_ps7_0_50M_0.vhd" \

vlog -work xil_defaultlib -64 -incr -mfcu  "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/df05/hdl" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../Car_project.gen/sources_1/bd/design_1/ipshared/00fe/hdl/verilog" "+incdir+../../../../../../../xilinx/2026.1/data/rsb/busdef" "+incdir+/home/henry/xilinx/2026.1/data/xilinx_vip/include" \
"../../../bd/design_1/sim/design_1.v" \

vlog -work xil_defaultlib \
"glbl.v"

