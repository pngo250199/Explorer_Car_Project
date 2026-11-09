## Technical Development Environment

The project is developed and tested on both Linux and Windows. The purpose of maintaining two development environments is to compare workflow differences, tool compatibility, build configuration, and debugging experience when working with Vivado, Vitis, CMake, Git, and the ARM GNU toolchain.

---

# 1. Linux OS Environment and Terminal Techniques

Linux is used as one of the primary development environments because FPGA and embedded-software development often requires direct control over compilers, environment variables, libraries, build systems, and command-line tools.

For this project, Ubuntu Linux is used for:

- Vivado FPGA development
- Vitis bare-metal software development
- ARM cross-compilation
- CMake-based builds
- Git and GitHub version control
- Toolchain troubleshooting
- File and dependency inspection
- Reference-project testing

The terminal is especially useful because it exposes the development environment directly instead of hiding tool paths and dependencies behind a graphical interface.

---

## Loading the Vivado/Vitis Environment

AMD development tools are not always automatically added to the Linux system path.

Before using Vivado from the terminal, the Vivado environment can be loaded with:

```bash
source /home/henry/xilinx/2026.1/Vivado/settings64.sh
```

This modifies the current shell environment so commands such as:

```bash
vivado
```

can be located and executed.

The result can be verified using:

```bash
which vivado
```

Example:

```text
/home/henry/xilinx/2026.1/Vivado/bin/vivado
```

This technique is useful for verifying exactly which version of a development tool is currently being used.

---

## Environment Variables

Linux environment variables are used extensively by development tools.

For example, a compatibility library directory was temporarily added to the runtime library search path using:

```bash
export LD_LIBRARY_PATH="$HOME/vivado-compat/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH"
```

This allows Vivado to locate additional shared libraries without modifying the system-wide Linux installation.

The general pattern is:

```bash
export VARIABLE_NAME=value
```

Environment variables are useful for:

- Toolchain paths
- Runtime libraries
- Compiler configuration
- SDK configuration
- Custom build environments

Because the variable is applied only to the current shell session, the system configuration can remain unchanged.

---

## Locating Tools

The `which` command is useful for determining which executable will run when a command is entered.

Example:

```bash
which vivado
```

or:

```bash
which arm-none-eabi-gcc
```

This is especially important when several versions of the same tool may be installed.

For example:

```text
Vivado 2025.1
Vivado 2026.1
Different ARM GCC versions
```

Checking the executable path helps prevent accidentally building a project with the wrong toolchain.

---

## Searching for Files

The `find` command is frequently used when Vivado or Vitis generates files inside deeply nested project directories.

Example:

```bash
find ~/Documents/Zybo_Z7_HDMI_Reference -name "*.xpr"
```

This searches for Vivado project files.

Another example:

```bash
find ~/Documents/Zybo_Z7_HDMI_Reference -iname "*fsbl*.elf"
```

This was used to locate the generated Zynq First Stage Boot Loader.

The result identified both the build artifact and exported platform artifact:

```text
.../export/linux_VDMA_platform/sw/boot/fsbl.elf
.../zynq_fsbl/build/fsbl.elf
```

This is useful because FPGA and embedded development environments often generate hundreds of files across multiple directories.

---

## Inspecting Directory Structure

The `ls` command is used to inspect the contents of directories.

```bash
ls
```

A more detailed view is provided by:

```bash
ls -la
```

This displays:

- Hidden files
- File permissions
- Owners
- File sizes
- Modification times

For example, the Digilent reference project was inspected using:

```bash
ls -la hw
ls -la hw/proj
```

This helped determine that the Git repository contained the hardware source and reconstruction scripts but did not initially contain a generated `.xpr` Vivado project.

---

## Inspecting Source Trees

The `find` command can also be used to understand the structure of an unfamiliar open-source project.

For example:

```bash
find sw -maxdepth 4 -type f | head -80
```

This exposed the major files in the Digilent Vitis software project:

```text
video_demo.c
video_demo.h
CMakeLists.txt
UserConfig.cmake
display_ctrl/
video_capture/
dynclk/
intc/
timer_ps/
```

This is useful when evaluating an external reference design because it allows the project architecture to be understood before importing or modifying the code.

---

## Git Repository Inspection

Git commands are also used directly from the Linux terminal.

Examples include:

```bash
git status
```

to view modified files,

```bash
git branch --show-current
```

to identify the active branch,

and:

```bash
git submodule update --init --recursive
```

to retrieve submodules required by open-source FPGA projects.

This was necessary for the Digilent Zybo Z7 HDMI reference design because the project separates hardware and software components into Git submodules.

---

## Cross-Platform Git Workflow

Because the same project is developed on both Linux and Windows, Git is used to synchronize source code.

Before beginning work:

```bash
git pull --rebase origin main
```

After completing and testing changes:

```bash
git add <modified files>
git commit -m "description"
git push origin main
```

Only source files are tracked.

Generated files such as:

```text
build/
.gen/
.runs/
.cache/
_ide/
```

are excluded because they can be regenerated separately on each operating system.

This prevents Linux-specific absolute paths from interfering with Windows builds and vice versa.

---

## ARM Cross-Compiler Verification

The project software targets the ARM Cortex-A9 rather than the x86 processor in the development computer.

The ARM compiler can be verified using:

```bash
arm-none-eabi-gcc --version
```

Unlike normal desktop GCC:

```text
gcc
```

the command:

```text
arm-none-eabi-gcc
```

generates bare-metal ARM code for processors such as the Cortex-A9.

This distinction is important in embedded development because the build computer and the target processor use different architectures.

---

## CMake-Based Development

Vitis 2026.1 uses a CMake-based software-development workflow.

Important project files include:

```text
CMakeLists.txt
UserConfig.cmake
lscript.ld
```

The source is compiled using the ARM cross-compiler and then linked into an ELF executable.

The general flow is:

```text
C source
   ↓
CMake configuration
   ↓
ARM GNU compiler
   ↓
Linker
   ↓
Application ELF
```

The resulting ELF is downloaded to the Cortex-A9 through Vitis/JTAG.

---

## Shared-Library Troubleshooting

Linux provides direct visibility into runtime dependencies.

For example, Vivado initially failed to launch because it required:

```text
libncurses.so.5
```

The installed system contained a newer library version instead.

The available libraries were inspected using:

```bash
ldconfig -p | grep -E "libncurses.so.5|libtinfo.so.5"
```

Rather than modifying the entire operating system, a local compatibility directory was created and added through `LD_LIBRARY_PATH`.

This demonstrates one advantage of Linux development: tool dependencies and runtime behavior can be inspected and controlled directly from the terminal.

---

## Why Linux Is Useful for This Project

Linux provides strong control over the development environment.

Advantages include:

- Direct access to compilers and build tools
- Easy inspection of paths and generated files
- Powerful command-line search tools
- Simple environment-variable configuration
- Strong Git integration
- Easier debugging of CMake and compiler issues
- Transparent dependency management
- Efficient automation through shell scripts

The main disadvantage is that compatibility issues may require manual debugging, especially when FPGA tools expect older Linux libraries.

For this project, the Linux environment provides a flexible environment for FPGA, embedded C, toolchain, and open-source development while also exposing the lower-level build process that is often hidden by graphical development tools.
