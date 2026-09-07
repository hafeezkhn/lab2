
# Booting
- The first time that electricity runs into a development board processor, a great 
number of hardware components need to be prepared before running a program. 
For each architecture, hardware manufacturer, and even processor, this initialization 
process is different. 
- The bootloader represents the piece of software that is first executed during system 
initialization. It is used to load, decompress, and execute one or more binary 
applications, such as a Linux kernel or a root filesystem. Its role involves adding 
the system in a state where it can execute its primary functions. This is done after 
loading and starting the correct binary applications that it receives or has already 
saved on the internal memory. Upon initializing, the hardware bootloader may need 
to initialize the phase-locked loop (PLL), set the clocks, or enable access to the RAM 
memory and other peripherals. 
- The majority of the available processors when power is applied to them go to 
a default address location, and after finding the first bytes of binary data, start 
executing them
--- 
- The bootloader is responsible 
for this; it is the component that offers the possibility to load, locate, and execute 
primary components of the operating system.
- Additionally, it can contain other 
advanced features, such as the capability to upgrade the OS image, validate an OS 
image, choose between several OS images, and even the possibility to upgrade itself.
- The difference between the traditional PC BIOS and an embedded bootloader is the 
fact that in an embedded environment, the bootloader is overwritten after the Linux 
kernel starts execution. It, in fact, ceases to exist after it offers control to the OS image.
---
- Bootloaders need to carefully initialize peripherals, such as flash or DRAM, before 
they are used

- The first executable instructions need to be at a 
predefined location in the flash memory, which is dependent of the processor and 
even hardware architecture. There is also the possibility for a number of processors 
to seek for those first executable instructions in several locations based on the 
hardware signals that are received

- The bootloader is the second element of embedded Linux. It is the part that starts
the system up and loads the operating system kernel.
- bootloader, how it passes control from itself to
the kernel using a data structure called a device tree, also known as a flattened
device tree or FDT

- When the first lines of the bootloader code are executed, following a power-on
or a reset, the system is in a very minimal state. The DRAM controller would not
have been set up, and so the main memory would not be accessible. Likewise,
other interfaces would not have been configured, so storage accessed via NAND
flash controllers, MMC controllers, and so on, would also not be usable.
- Typically, the only resources operational at the beginning are a single CPU core
and some on-chip static memory. As a result, system bootstrap consists of
several phases of code, each bringing more of the system into operation. - 
- The final act of the bootloader is to load the kernel into RAM and create an execution
environment for it. The details of the interface between the bootloader and the kernel are architecture-specific, but in each case it has to do two things. 
- First,bootloader has to pass a pointer to a structure containing information about the hardware configuration, and second it has to pass a pointer to the kernel command line. The kernel command line is a text string that controls the
behavior of Linux. 
- Once the kernel has begun executing, the bootloader is no
longer needed and all the memory it was using can be reclaimed.

- A subsidiary job of the bootloader is to provide a maintenance mode for
updating boot configurations, loading new boot images into memory, and,
maybe, running diagnostics. This is usually controlled by a simple command line user interface, commonly over a serial interface
- The second stage bootloaders usually reside next 
to the first stage ones, they contain the most number of features and do most of the 
work. They also know how to interpret various filesystem formats, mostly because 
the kernel is loaded from a filesystem.
- A NOR memory is preferred over the NAND one because it allows random address 
access. It is the place where the first stage bootloader is programmed to start the 
execution, and this doesn't make it the most practical mechanism of booting.

## Phase 1 - ROM code
- In the absence of reliable external memory, the code that runs immediately after
- a reset or power-on has to be stored on-chip in the SoC.
this is known as ROM
code. It is loaded into the chip when it is manufactured, and hence the ROM
code is proprietary and cannot be replaced by an open source equivalent.
Usually, it does not include code to initialize the memory controller, since DRAM configurations are highly device-specific, and so it can only use Static Random Access Memory (SRAM), which does not require a memory controller. Most embedded SoC designs have a small amount of SRAM on-chip, varying in
size from as little as 4 KB to several hundred KB:
- The ROM code is capable of loading a small chunk of code from one of several
pre-programmed locations into the SRAM. As an example, TI OMAP and Sitara
chips try to load code from the first few pages of NAND flash memory, or from
flash memory connected through a Serial Peripheral Interface (SPI), or from
the first sectors of an MMC device (which could be an eMMC chip or an SD
card), or from a file named MLO on the first partition of an MMC device. If
reading from all of these memory devices fails, then it tries reading a byte stream
from Ethernet, USB, or UART;
- Most embedded SoCs have a ROM code that works in a similar way.
In SoCs where the SRAM is not large enough to load a full bootloader like U-Boot, there has to be an intermediate loader called the secondary program
loader, or SPL
- At the end of the ROM code phase, the SPL is present in the SRAM and the
ROM code jumps to the beginning of that code

## Phase 2 - SPL
- The SPL must set up the memory controller and other essential parts of the
system preparatory to loading the Tertiary Program Loader (TPL) into
DRAM.
- The functionality of the SPL is limited by the size of the SRAM. It can
read a program from a list of storage devices, as can the ROM code, once again
- using pre-programmed offsets from the start of a flash device. If the SPL has file
system drivers built in, it can read well known file names, such as u-boot.img,
from a disk partition. The SPL usually doesn't allow for any user interaction, but
it may print version information and progress messages, which you can see on
the console. 
- The SPL may be open source, as is the case with the TI x-loader and Atmel
AT91Bootstrap, but it is quite common for it to contain proprietary code that is
supplied by the manufacturer as a binary blob
- At the end of the second phase, the TPL is present in DRAM, and the SPL can
make a jump to that area

## Phase 3 - TPL
- Now, at last, we are running a full bootloader, such as U-Boot or BareBox.
- TPL loads Kernel+FDT+initramfs into DRAM
Usually, there is a simple command-line user interface that lets you perform
maintenance tasks, such as loading new boot and kernel images into flash
storage, and loading and booting a kernel, and there is a way to load the kernel
automatically without user intervention.
- At the end of the third phase, there is a kernel in memory, waiting to be started.
- Embedded bootloaders usually disappear from memory once the kernel is
running, and perform no further part in the operation of the system

# Booting with UEFI firmware
- Most embedded x86/x86_64 designs, and some ARM designs, have firmware
based on the Universal Extensible Firmware Interface (UEFI) standard.
- The
boot sequence is fundamentally the same as that described in the preceding
section:
- Phase 1: The processor loads the platform initialization firmware from
flash memory. In some designs, it is loaded directly from NOR flash
memory, while in others, there is ROM code on-chip which loads the
firmware from SPI flash memory into some on-chip static RAM.
- Phase 2: The platform initialization firmware performs the role of SPL. It
initializes the DRAM controller and other system interfaces, so as to be
able to load an EFI boot manager from the EFI System Partition (ESP) on
a local disk, or from a network server via PXE boot. The ESP must be
formatted using FAT16 or FAT32 format and it should have the well-known
GUID value of C12A7328-F81F-11D2-BA4B-00A0C93EC93B. The path name of the boot
manager code must follow the naming convention
<efi_system_partition>/boot/boot<machine_type_short_name>.efi. For example, the
file path to the loader on an x86_64 system would be /efi/boot/bootx64.efi.
- Phase 3: The UEFI boot manager is the tertiary program loader. The TPL in
this case has to be a bootloader that is capable of loading a Linux kernel
and an optional RAM disk into memory. Common choices are:
systemd-boot: This used to be called gummiboot. It is a simple UEFI compatible bootloader, licensed under LGPL v2.1.
Tummiboot: This is the gummiboot with trusted boot support (Intel's Trusted
Execution Technology (TEX))

- When the bootloader passes control to the kernel it has to pass some basic
information, which may include some of the following:
The machine number, which is used on PowerPC, and ARM platforms
without support for a device tree, to identify the type of the SoC
- Basic details of the hardware detected so far, including at least the size and
location of the physical RAM, and the CPU clock speed
- The kernel command line
Optionally, the location and size of a device tree binary
- Optionally, the location and size of an initial RAM disk, called the initial
RAM file system (initramfs)

---
- BIOS is the legacy way of booting
- BIOS (Basic input output system) , which was present in the boot ROM in PCs
- UEFI(unified extensible firmware interface) was introduced in the late 2000s , to deal with modern system needs capable of booting from disc which are bigger than two terabytes with a GUID partition table (GPT)
- in linux virtual machines BIOS is still widely used reason being its simpler and advanced UEFI features are not needed   
- UEFI can be configured with secure boot , secure boot prevent the  loading of an OS that is not signed with a known digital signature
- Booting from UEFI is different as OS register themselves with UEFI firmware.
  - Unlike BIOS booting , there is no longer need to scan for bootable devices
-  

---
## Linux Boot Procrdure
- Through the firmware (either uefi or BIOS) the bootloader is activated.
- the purpose of bootloader is to load the linux kernel and related initramfs
- Also , a boot menu can be presented to specify boot options 
- GRUB2 and lilo are common bootloders
- Uboot is used on embedded linux 
- in cloud instances , normally provide thier own bootloader 
- in BIOS disc, the first 512 bytes on disk are the boot sector,in this 446 bytes are used for Grub code , and 64bytes are used for partition table , 2bytes are magic code
- use hexdecimal utilities like xxd and hexdump to investigate 
- on UEFI systems, the UEFI info is on the EFI system partition 
- this vfat formatted partition is mounted on /boot/efi
- Use ls and cat to see file contents directly from OS itself, or from a rescue disk.
- configuring grub.cfg configuration filr for booting.
- initramfs:
  - the linux kernel is modular 
  - to keep the kernel file small  on installation an initramfs(aka initrd) that contains all essential kernel modules is generated.
  - kernel modules which requires for the boot
  - the initramfs is also responsible for loading the root filesystem
  - As last step initramfs loads the root filesystem(not yet systemd)
  - initramfs is updated when hardware changes where new drivers need to be provided
  - After Kernel upgrads(happens automatically)
  - To add drivers not currently included
  - After any other changes that involve the early boot stage(rare)
    - to update initramfs, use the following
    - dracut -f (Red Hat family)
    - Update-initramfs -u (ubuntu and related)
    ```bash 
    lsinitrd | grep ext4
    vim /etc/dracut.conf.d/ext4.conf
    add_drivers+="ext4"
    dracut -f
    lsinitrd # will show current content
    ```
- Service manager takes care of loading everything aftre the kernel and initrd have been loaded, and the root file system has been mounted 
- This consist of a few stages 
  - initializing remainig hardware devices
  - Mounting filesystems
  - Starting services
  - itll start the shell
- systemd is the most common service manager used on all the leading linux distros
- Alternatives are init and upstart, which are still used on some Linux distros
  

- Early access Boot shell 
  - Use Systemd.unit=emergency.target or systemd.uint=rescue.target as a GRUB Kernel startup parameter to enter a systemd troubleshooting mode
  - rd.braak or init=/bin/bash as a GRUB kernel startup parameter to enter a troubleshooting environment before systemd is started.
  - Enable debug-shell.service and access through /dev/tty9 while booting
- boot order :  normally starts from hard disk if no hard disk is found itll start from istallation disk, if not found theer itll try with network