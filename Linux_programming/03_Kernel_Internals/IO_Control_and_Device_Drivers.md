## I/O Architecture
- Communication with peripherals is usually referred to as input and output
-  The kernel must deal with three problem areas when implementing I/O for peripherals.
    - Firstly, the hardware must be addressed using a variety of methods depending on the specific device type and model.
    - Secondly, the kernel must provide user applications and system tools with ways of accessing the various devices.
    -  Thirdly, userspace needs to know which devices are available in the kernel.

- To make a computer work properly, data paths must be provided that let
information flow between CPU(s), RAM, and the score of I/O devices that can be
connected to a personal computer. These data paths, which are denoted as the
buses , act as the primary communication channels inside the computer.
- Any computer has a system bus that connects most of the internal hardware
devices. A typical system bus is the PCI (Peripheral Component Interconnect) bus.
Several other types of buses, such as ISA, EISA, MCA, SCSI, and USB, are
currently in use. Typically, the same computer includes several buses of different
types, linked together by hardware devices called bridges .

## Modules 
Despite being “monolithic,” in the sense that the whole kernel runs in a single address
space, the Linux kernel is modular, supporting the dynamic insertion and removal of code
from itself at runtime. Related subroutines, data, and entry and exit points are grouped
together in a single binary image, a loadable kernel object, called a module. Support for
modules allows systems to have only a minimal base kernel image, with optional features
and drivers supplied via loadable, separate objects. Modules also enable the removal and
reloading of kernel code, facilitate debugging, and allow for the loading of new drivers on
demand in response to the hot plugging of new devices

- To Access Specific Hardware devices  the kernel uses kernel modules as drivers
- To access these modules some main ``kernel generic interfaces``are used
  - virtual memory for addressing memory
  - Virtual file system for addressing file system
  - Device Mapper for addressing several types of block devices
  - TCp/IP for addressing network devices
- System calls provide access to these generic interfaces, which makes device usage possible by addressing the devices fromusers space
- The Sysfs and procfs pseudo filesystems are used to tweak the generic interfaces
```mermaid
flowchart TD
    %% User Space
    subgraph UserSpace["User Space"]
        direction LR
        P1["Process (Storage)"]
        P2["Process (Network)"]
    end

    %% Syscall Boundary
    subgraph SyscallBoundary["System Call Layer"]
        direction LR
        SC1["syscall"]
        SC2["syscall"]
    end

    %% Kernel Space
    subgraph Kernel["Kernel Space"]
        subgraph StorageStack["Storage Subsystem"]
            FD["File Descriptor"]
            VFS["VFS"]
            FS["XFS"]
            BD["Block Device"]
        end

        subgraph VirtualFS["Virtual Filesystems"]
            SYSFS["sysfs"]
            PROCFS["procfs"]
        end

        subgraph NetworkStack["Network Subsystem"]
            SOCK["Socket"]
            TCPIP["TCP / IP"]
            NWDEV["nw. device"]
        end
    end

    %% Hardware Layer
    subgraph Hardware["Hardware"]
        direction LR
        STORAGE[("Storage (Disk)")]
        NETWORK["Network"]
    end

    %% User to Syscall Connections
    P1 -->|write / read| SC1
    P2 -->|sendmsg / recvmsg| SC2

    %% Syscall to Kernel Stacks
    SC1 --> FD
    SC2 --> SOCK

    %% Storage Data Path
    FD --> VFS
    VFS --> FS
    FS --> BD
    BD --> STORAGE

    %% Network Data Path
    SOCK --> TCPIP
    TCPIP --> NWDEV
    NWDEV --> NETWORK

    %% Virtual Filesystem Connections (Observability & Control)
    SYSFS -.-> FD
    SYSFS -.-> SOCK
    PROCFS -.-> VFS
    PROCFS -.-> FS
    PROCFS -.-> BD
    PROCFS -.-> TCPIP
    PROCFS -.-> NWDEV
  ```

- kernel modules are loaded in different ways
  - Through the initramfs/initrd
  - through systemd-udevd
  - manually using modprobe
- some kernel modules take parameters
  - use modinfo command
- some kernel module have options
  - /etc/modprobe.d,reflecting the name of the module
  - in this file use options modulename name=value, for instance:options cdrom debug=true

- to manually load kernel module parameters, add paramname=value to commandline while loading module

- some kernel modules keep thier current parameter values in /sys/module/modulename/parameters/*

- use modprobe -c|grep modulename to print module configuration

```bash
lspci -k #look for ethernet controller
modinfo e1000
modprobe -r e1000
modprobe e1000 debug=4
modprobe -c e1000
echo options e1000 debug=4 > /etc/modprobe.d/e1000.conf
Notice that this parameter doesn't show in /sys/module/e1000/parameters/
```

## Psudo filesystems
- /proc is a pseudo filesystem that provides an interface to kernal data structure

- Being a pseudo filesystem , /proc doesn't give access to disk device, but provides access to a kernel interface.

- the Kernel uses other pseudo filesystems , like sysfs and debugfs

- /proc 3 main types of info
  - /proc/nnn: this is where the kernel keeps information about every running process.thses directories are referred to as the PID directories
  - /proc/sys here youll find kernel tunable organized by different kernel interfaces.
  - /proc/* here youll find many files that contains status information about a running process

```bash
mount | grep proc
less cpuinfo
lscpu
less meminfo
cat cmdline
less vmstat #vertual memory
less modules 
lsmod
cat filessystems # nodev is psudofilesystem
less  devices
less swaps
swapon -a
less mount
lsof
```







## Devices
In Linux, as with all Unix systems, devices are classified into one of three types:
- Block devices
- Character devices
- Network devices

- kernel drivers are used to load drivers for devices.
- to access these drivers,a representaion in user space is needed
- this representation is made by device nodes in /dev
- the "everything is a file" statement applies here,by using device files users can easily access block as well as charecter devices
