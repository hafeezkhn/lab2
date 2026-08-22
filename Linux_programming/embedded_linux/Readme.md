# Embedded Linux

---

<details>
<summary>🔹 Four Elements of Embedded Linux</summary>

1) **Toolchain**: The compiler and other tools needed to create code for your target device. Everything else depends on the toolchain.  

2) **Bootloader**: The program that initializes the board and loads the Linux kernel.  

3) **Kernel**: This is the heart of the system, managing system resources and interfacing with hardware.  

4) **Root filesystem**: Contains the libraries and programs that are run once the kernel has completed its initialization.  

---

**➕ One more element**  
A collection of programs specific to your embedded application which make the device do whatever it is supposed to do — be it weigh groceries, display movies, control a robot, or fly a drone.

</details>

---

<details>
<summary>🔹 Board Support Package (BSP)</summary>

- Board-specific **bootloader and initialization code**  
- **Device drivers**, **device tree**, and **configuration files**  
- Hardware-abstraction routines and static initialization scripts  

These BSP components are typically integrated into the kernel and root filesystem.

</details>

---

<details>
<summary>🔹 ARM SoC Comparison</summary>

| Feature | **TI AM3358 (BeagleBone Black)** | **Broadcom BCM2711 (Raspberry Pi 4)** |
|----------|----------------------------------|---------------------------------------|
| **Cortex Core** | Cortex-A8 | Cortex-A72 |
| **ARM Architecture** | ARMv7-A (32-bit) | ARMv8-A (64-bit, backward compatible with ARMv7) |
| **CPU Cores** | Single-core | Quad-core |
| **Clock Speed** | Up to 1 GHz | Up to 1.5 GHz |
| **Pipeline** | In-order, 13-stage | Out-of-order, superscalar |
| **NEON SIMD** | Supported | Supported (improved) |
| **Target Domain** | Embedded/industrial applications | General-purpose computing, multimedia, education |
| **GPU** | PowerVR SGX530 | Broadcom VideoCore VI (dual-core, 500 MHz) |
| **Memory** | 512 MB DDR3L | 1 GB / 2 GB / 4 GB / 8 GB LPDDR4 |
| **Storage** | microSD, 4 GB eMMC (on some models) | microSD slot |
| **Networking** | 10/100 Ethernet | Gigabit Ethernet, Wi-Fi 802.11ac, Bluetooth 5.0 |
| **USB** | USB 2.0 | USB 2.0 & USB 3.0 |
| **HDMI / Display** | LCD controller, no native HDMI | Dual micro-HDMI (4K supported) |
| **GPIO Pins** | 65+ (2×46-pin headers) | 40-pin header |
| **I/O Interfaces** | UART, SPI, I²C, CAN, PWM, ADC, PRU (Programmable Realtime Unit) | UART, SPI, I²C, GPIO, CSI (camera), DSI (display) |
| **Real-Time Support** | Yes (via PRUs, TI-RTOS, FreeRTOS, Zephyr, QNX, VxWorks) | Limited RTOS support, mainly Linux-focused |
| **OS Support** | Debian (BeagleBone images), Ångström, Yocto, Buildroot, Android (legacy), TI-RTOS, FreeRTOS | Raspberry Pi OS (32/64-bit), Ubuntu, Fedora, Arch, Manjaro, Android, LineageOS, Windows 10/11 ARM (community), BSD |
| **Power Requirement** | 5V DC input, lower power consumption | 5V via USB-C, higher power draw |
| **Use Cases** | Robotics, industrial control, automotive, embedded projects needing precise timing | General computing, multimedia, education, IoT, edge AI |

</details>
