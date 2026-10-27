# Virtualization
- virtualization Allows a physical computer to run multiple independent computing environments. 

-  The physical system that runs the virtualization software (hypervisor or Virtual Machine Monitor) is called a host and the virtual machines installed on top of the hypervisor are called guests.

- `hypervisor` is a software layer that created and maanges virtual machines.It controls how physical hardware resources such as the processor,memory,storage and network devices are shared between multiple virtual systems

-  the hypervisor allows each virtual machine to operate as if it has its own computer

### Types of Hypervisors

`Type-1 Hypervisor` runs directly on physical hardware. it does not require a traditional operating system underneath it.

```text
        Physical H/W
             |
      Type-1 Hypervisor
            /|\
           / | \
        VM1 VM2 VM3

```
- Because the hypervisor communicates directly with hardware, Type-1 system usually provide strong performance.

`Type-2 Hypervisor`runs on top of an existing operating system

```text
        Physical H/W
             |
    Host Operating system
             |
      Type-2 Hypervisor
            /|\
           / | \
        VM1 VM2 VM3

```


