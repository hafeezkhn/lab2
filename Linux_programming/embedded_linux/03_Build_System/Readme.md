| Phase | Core Focus | System Component | Primary Inputs | Primary Outputs | Key Technologies |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **1. Toolchain** | Environment Prep | Host Build System | Arch specifications, C-library selection | Cross-Compiler, Linker, Assembler | Yocto, Buildroot, crosstool-NG |
| **2. Bootloader** | Hardware Wakeup | Low-level Firmware | Source code, Board config, Cross-Toolchain | `u-boot.bin`, `SPL` | U-Boot, Barebox, TF-A |
| **3. Kernel** | HW Management | OS Core | Kernel source, **`.dts` files**, `.config` | `zImage`/`Image`, **`.dtb` blob**, `.ko` modules | Linux Kernel, Device Tree Compiler |
| **4. Rootfs** | User Environment | User-Space Workspace | Toolchain runtimes, Base skeleton, App source | Compiled `/bin`, `/lib`, `/etc` directories | BusyBox, **Systemd**, SysVinit |
| **5. Deployment** | Packaging / Flashing | Target Storage Media | Bootloader, Kernel, `.dtb`, Populated rootfs | `sdcard.img`, `rootfs.ext4`, `rootfs.ubifs` | `genimage`, `wic`, `dd`, `bmaptool` |