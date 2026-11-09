
## Open-Source VDMA/HDMI Reference Validation on Linux

Before integrating the video subsystem into the main autonomous car project, an open-source Zybo Z7 HDMI reference design was tested separately on Linux. The purpose of this step was to verify that the VDMA, HDMI pipeline, Vivado project, and Vitis software could still operate correctly with the current 2026.1 development tools.

This created a known-good video baseline before modifying the main project.

---

### 1. Clone the Reference Project

The Digilent Zybo Z7 HDMI reference design was cloned into a separate directory from the main car project.

The reference repository was intentionally kept separate:

```text
Documents/
├── Explorer_Car_Project/
└── Zybo_Z7_HDMI_Reference/
```

This prevents third-party source code and generated files from being mixed directly into the main project.

The repository was initialized with all required Git submodules:

```bash
git submodule update --init --recursive
```

The cloned project contained separate hardware and software sections:

```text
Zybo_Z7_HDMI_Reference/
├── hw/
├── sw/
└── os/
```

---

### 2. Inspect the Hardware Repository

The hardware folder initially did not contain a generated Vivado `.xpr` project.

This was verified using:

```bash
find ./hw -name "*.xpr"
```

The `hw` directory contained:

```text
hw/
├── hw_handoff/
├── proj/
├── repo/
├── scripts/
├── src/
└── project_info.tcl
```

The empty `proj/` directory indicated that the Vivado project needed to be reconstructed from the provided sources and Tcl scripts.

---

### 3. Configure the Vivado 2026.1 Linux Environment

The Vivado environment was loaded using:

```bash
source /home/henry/xilinx/2026.1/Vivado/settings64.sh
```

The active Vivado executable was confirmed with:

```bash
which vivado
```

which returned:

```text
/home/henry/xilinx/2026.1/Vivado/bin/vivado
```

This verified that Vivado 2026.1 was the version being used.

---

### 4. Resolve Linux Library Compatibility

Vivado initially failed to start because the current Linux installation did not provide the legacy library:

```text
libncurses.so.5
```

A local compatibility directory was created:

```bash
mkdir -p ~/vivado-compat
```

Legacy `libncurses5` and `libtinfo5` packages were extracted locally without replacing the system libraries.

The extracted files included:

```text
~/vivado-compat/lib/x86_64-linux-gnu/libncurses.so.5
~/vivado-compat/lib/x86_64-linux-gnu/libtinfo.so.5
```

The local compatibility directory was then added to the runtime library search path:

```bash
export LD_LIBRARY_PATH="$HOME/vivado-compat/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH"
```

After loading this environment, Vivado 2026.1 successfully launched.

This approach allowed the FPGA tools to use the required legacy libraries without modifying the Linux system globally.

---

### 5. Reconstruct the Open-Source Vivado Project

The reference design provided a Tcl-based project reconstruction script.

Inside the Vivado Tcl Console, the following commands were used:

```tcl
set argv ""
source /home/henry/Documents/Zybo_Z7_HDMI_Reference/hw/scripts/checkout.tcl
```

The script reconstructed the complete Vivado project from the version-controlled source files.

After reconstruction, the generated project was located under:

```text
hw/proj/
```

This demonstrated an important source-control practice: only the design sources and scripts are stored in Git, while generated Vivado projects can be recreated when needed.

---

### 6. Upgrade and Validate the Reference Design

Because the open-source project was created for an earlier Vivado release, the IP blocks were checked and upgraded for Vivado 2026.1 when required.

The design was then validated and processed through the normal FPGA build flow:

```text
Block Design
    ↓
IP Validation
    ↓
Synthesis
    ↓
Implementation
    ↓
Bitstream Generation
```

The bitstream generated successfully.

This confirmed that the Digilent VDMA/HDMI hardware architecture could be rebuilt using the current Vivado 2026.1 environment.

---

### 7. Export the Hardware Platform

After the bitstream was generated, the hardware design was exported as an XSA file with the bitstream included.

This XSA contains the information required by Vitis, including:

- Zynq Processing System configuration
- FPGA bitstream
- Memory addresses
- Connected hardware IP
- Processor configuration

A new Vitis platform was then created using this newly generated 2026.1 XSA rather than relying on the older platform included with the original reference design.

---

### 8. Inspect the Open-Source Vitis Software

The software repository was inspected using terminal commands such as:

```bash
find sw -maxdepth 4 -type f | head -80
```

and:

```bash
find sw -iname "*.c" -o -iname "*.h"
```

The reference application contained:

```text
video_demo.c
video_demo.h

display_ctrl/
├── display_ctrl.c
├── display_ctrl.h
└── vga_modes.h

video_capture/
├── video_capture.c
└── video_capture.h

dynclk/
├── dynclk.c
└── dynclk.h

intc/
├── intc.c
└── intc.h

timer_ps/
├── timer_ps.c
└── timer_ps.h
```

It also contained modern Vitis/CMake project files:

```text
CMakeLists.txt
UserConfig.cmake
lscript.ld
```

This confirmed that the reference software could be reused with the current Vitis workflow.

---

### 9. Build the HDMI/VDMA Application

A new Vitis application component was created using the newly generated Linux platform.

The Digilent source directory was used as the application source.

The software successfully compiled and linked using the ARM cross-compiler.

The final executable was:

```text
Zybo-Z7-10-HDMI.elf
```

The successful build confirmed:

```text
Source Code
    ↓
CMake
    ↓
arm-none-eabi-gcc
    ↓
Linker
    ↓
Zybo-Z7-10-HDMI.elf
```

---

### 10. Configure Hardware Execution

A Vitis hardware launch configuration was then created for:

```text
Processor:
ps7_cortexa9_0
```

The launch configuration used:

```text
Target Setup Mode: Baremetal Debug
Board Initialization: FSBL
Program Device: Enabled
```

The generated First Stage Boot Loader was located using:

```bash
find ~/Documents/Zybo_Z7_HDMI_Reference -iname "*fsbl*.elf"
```

The exported FSBL was selected:

```text
.../export/linux_VDMA_platform/sw/boot/fsbl.elf
```

This initializes the Zynq Processing System, DDR, clocks, and other hardware before running the application.

---

### 11. Fix the ELF Launch Path

The Vitis component was named:

```text
linux_VDMA_software
```

but the CMake project generated the executable:

```text
Zybo-Z7-10-HDMI.elf
```

The launch configuration initially attempted to run:

```text
linux_VDMA_software.elf
```

which did not exist.

The application field was corrected to point to:

```text
Zybo-Z7-10-HDMI.elf
```

After correcting the executable path, the application successfully launched on the Cortex-A9.

---

## Result

The open-source VDMA/HDMI reference design successfully passed the complete Linux validation flow:

```text
Open-source source code
        ↓
Vivado 2026.1
        ↓
Project reconstruction
        ↓
IP compatibility update
        ↓
Synthesis
        ↓
Implementation
        ↓
Bitstream
        ↓
2026.1 XSA
        ↓
Vitis platform
        ↓
CMake application build
        ↓
FSBL initialization
        ↓
Zybo-Z7-10-HDMI.elf
        ↓
Cortex-A9 hardware execution
```

This verified that the VDMA and video architecture can operate with the current Linux, Vivado 2026.1, Vitis 2026.1, CMake, and ARM GNU development environment.

---

## Why This Test Was Performed Before Integration

The VDMA/HDMI subsystem was intentionally validated separately before being added to the autonomous car project.

The existing car project already contains a known-working system:

```text
Cortex-A9
    ↓
AXI4-Lite
    ↓
Custom FPGA IP
    ↓
GPIO
```

Adding VDMA, DDR access, AXI4-Stream, video timing, HDMI interfaces, and multiple clock domains directly into this working project would introduce many new possible failure points at the same time.

Testing the reference design separately provides a known-good baseline:

```text
Reference VDMA/HDMI system
        ↓
Verify hardware
        ↓
Verify software
        ↓
Understand architecture
        ↓
Reuse required subsystems
        ↓
Integrate into car project
```

This reduces debugging risk and makes it easier to determine whether future problems come from the reference video infrastructure or from the custom image-processing logic.

The next step is to identify which parts of the validated reference design should be reused in the main project, particularly:

- VDMA
- DDR framebuffer access
- AXI high-performance interface
- AXI4-Stream video path
- Video timing
- HDMI input/output infrastructure

Custom grayscale, edge-detection, and image-processing IP will then be integrated into this known-working video architecture.
