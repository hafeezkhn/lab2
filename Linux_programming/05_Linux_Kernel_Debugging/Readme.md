1: @ User Space
User Space Purpose
printf Useful for monitoring
gdb Source level debugger
strace strace tool that shows all the system calls issued by a user-space program
valgrind Memory checker like segmentation fault ERRORS.
debugfs Debug FS useful for custom debug messages.
DDT Device Driver Test cases like gpio, uart, i2c etc.
LTP Linux Test Project useful for Tracing of events in the kernel and also checks
kernel performance.
mmap() User directly communicating with hardware for register programming.
ftrace ftrace is the ability to see what is happening inside the kernel

2: @ Kernel Space
Kernel Space Purpose
printk & dmesg Useful for monitoring
Module test cases Useful for particular module test
/proc and /sys Proc file system useful for overall system information.
Sys file system useful for device hierarchy.
Probe Status Useful for to test device working condition.
KDB KDB is In built Debugger to test whenever kernel goes panic.
KGDB KGDB is Kernel GDB useful for source level debugging.
Crash dump Whenever kernel crashes, it create crash dump file for crash dump analysis.
ftrace Ftrace is the ability to see what is happening inside the kernel

3: @ u-boot (Boot loader)
Boot Loader Purpose
u-boot
gpio, i2c, sspi commands.
commands
Add commands Useful for create custom command for debugging.
Read/write
Using md, mm commands read/write device specific registers.
Device Registers

---
### оops Messages
- oops messages indicate that a fault occurred in kernel mode. Depending on the nature of the fault
that produced the oops, the fault may be fatal, serious, or inconsequential.
- If the oops occurs in process context the kernel will attempt to back out of the current task, probably
killing it. If it occurs in interrupt context the kernel can't do this and will crash, as it will if it occurs
in either the idle task (pid=0) or init (pid=1).
