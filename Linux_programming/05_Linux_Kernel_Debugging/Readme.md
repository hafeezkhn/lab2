# Linux System Debugging Guide

This document outlines various tools and techniques used for debugging across different levels of a Linux system: User Space, Kernel Space, and the Bootloader.

## 1. User Space

| Tool / Interface | Purpose |
| :--- | :--- |
| **`printf`** | Useful for general monitoring and logging. |
| **`gdb`** | Source-level debugger. |
| **`strace`** | Tool that shows all the system calls issued by a user-space program. |
| **`valgrind`** | Memory checker used to find memory leaks and segmentation fault errors. |
| **`debugfs`** | Debug filesystem useful for custom debug messages. |
| **DDT** | Device Driver Test cases (e.g., gpio, uart, i2c, etc.). |
| **LTP** | Linux Test Project; useful for tracing events in the kernel and checking kernel performance. |
| **`mmap()`** | Allows the user to communicate directly with hardware for register programming. |
| **`ftrace`** | Provides the ability to see what is happening inside the kernel from user space. |

## 2. Kernel Space

| Tool / Interface | Purpose |
| :--- | :--- |
| **`printk` & `dmesg`** | Useful for kernel-level monitoring and viewing the kernel ring buffer. |
| **Module test cases** | Useful for testing particular kernel modules. |
| **`/proc` and `/sys`** | The `proc` file system is useful for overall system information. The `sys` file system is useful for device hierarchy. |
| **Probe Status** | Useful to test if a device is in a working condition. |
| **KDB** | Built-in kernel debugger used to test and inspect the system whenever the kernel panics. |
| **KGDB** | Kernel GDB, useful for source-level debugging of the kernel. |
| **Crash dump** | Whenever the kernel crashes, it creates a crash dump file for post-mortem analysis. |
| **`ftrace`** | The built-in tracing utility to see what is happening inside the kernel. |

## 3. U-Boot (Bootloader)

| Command / Feature | Purpose |
| :--- | :--- |
| **U-Boot Commands** | General hardware interaction commands like `gpio`, `i2c`, `sspi`. |
| **Add commands** | Useful to create custom U-Boot commands for specific debugging needs. |
| **Read/Write Device Registers** | Using `md` (memory display) and `mm` (memory modify) commands to read/write device-specific registers. |


---
### оops Messages
- oops messages indicate that a fault occurred in kernel mode. Depending on the nature of the fault
that produced the oops, the fault may be fatal, serious, or inconsequential.
- If the oops occurs in process context the kernel will attempt to back out of the current task, probably
killing it. If it occurs in interrupt context the kernel can't do this and will crash, as it will if it occurs
in either the idle task (pid=0) or init (pid=1).
