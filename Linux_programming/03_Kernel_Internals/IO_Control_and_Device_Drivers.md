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
  
## Devices
In Linux, as with all Unix systems, devices are classified into one of three types:
- Block devices
- Character devices
- Network devices