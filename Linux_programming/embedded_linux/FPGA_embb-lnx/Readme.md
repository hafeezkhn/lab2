# Embedded Linux and FPGAs
-  Memory-mapped I/O and AXI -lite register based Bus interface
- how part of peripheral interacts with OS (Linux Kernel and driver)
- Map FPGA hardware into Linux via Device Tree
- Build complete Hardware-Software intigration with inturrupts 
    - `Hardware interface` Registers,AXI-lite bus , Memory map IO
    - `Software interface` kernel cooncepts,driver,performance (DMA,inturrupts)

## Memory Mapped IO
- CPU uses Loads/stores to MMIO address ranges
- Interconnect(partial decoding - AXI ,...) routes transactions to peripherals
- Each peripheral exposes a small `register bank`

```text
                             /[peripheral 0X40000]
|CPU| - {interconnect[Axi]}  -[peripheral 0X40001]
                             \[peripheral .......]
```

### MMIO Fundamentals
- Memory vs MMIO: similar access, different side-effects
- Alignment and width:assume 32-b data width
- caches: MMIO is typically uncached/strongly ordered instruction.
    - Details of cache architectures : external memory blocks is slow , potentially becoz of  large size , large amount of data stored, time required to read/write given location in memory could be 100s of CPU clock cycle , to speed things up a smaller or more frequent memory we can cache.
    - L1 faster than L2 faster than L3 faster than main memory

`>> NOTE: MMIO(takes reads from sensor,Random number generator,ADC etc.. ) , every time i read value back i may potentially get different data, where as when we read memory ill get same data,so if im using memory i can use cache but if im using sensor i dont want it to be cached, we can say like addresses in range of peripherals should not be cached`

### AXI Bus Protocol
- protocol for data transfer;Transaction;scalability
- channel Architechture : communication between two devices
   - Manager can initiate/start traansaction in the bus 
   - Subortinate it gets transaction info from manager and has to respond based on what it got. 

  Manager[hw-unit] <-------> Subordinate[hw-unit]
  (CPU,DMA)                  (timer,memory block)

  - channels handshaking methods (write:addr+data->response,reads:address->data+response)
  - `AXI Handshake` : Source/destination depends on type of transfer
      - valid/ready logical way of signal which says how can i transfer data between two blocks of digital gates. (refer: Handshake Mechanics in ARM doc[AXI specs](https://documentation-service.arm.com/static/5f915920f86e16515cdc3342) ) 

```text
        |  (valid)       | 
  Souce | -------------> |Destination
        | <------------- |
        |    (Ready)     |
```

- transfer: single exchange of information with one Valid/Ready handshake
- transaction: Entire burst/sequence of address transfer,one or more data transfers,and response transfer(for writes)

- Why Register Banks?
    - Software control of hardware blocks via MMIO
    - Small ,discoverable API:address map + documentated side-effects
    - Decouples datapath timings from software transactions
    - Enables debu/observability with status bits and counter
    - `DataSheet` has: [↗](https://support.arm.com/documentation/ddi0183/g/)
        1. Functional Description: What does it do(when would you use it.)
        2. Programmers model:How do you go about using it.


`_________________`
---

### System Power-ON
 Any digital circuit (sequential circuit) there is a concept called reset (reset says there are storage elements present inside your circuit(flipflops hold info about state) program counter and state of some internal registers those are directly related to the state of the processor, `infact` it directly influence whats going to happen when processor switches on ,when clock starts ticking).

- System Power on reset: PC Loaded with default value
    - Fetches instructions - usually JMP to space with more code
    - Flash memory , load from disk etc...
    - BIOS - Basic innput /output system
    - Bootstrapping/Boot-up

- Embedded Microcontrollers - may not have OS : bare metal
    - Limitations of Bare Metal
        - All Functionality in basic system
        - No multi-tasking/time multiplexing
        - Need Full control over every step of process
- Operating System:First program that runs after reset
    - Take over System function
    - provide facilities to other program
        - process scheduling:which program can run
        - memory management:virtual memory,protection,paging
        - storage & filesystem:files,directories,permissions
        - I/O stack:drivers,DMA,inturrupts,power
        - Networking:sockets,routing,offloadss
        - Security:isolation,capabilities,namesapce/containers
    

>> Note: Registers and MMIO  Hw-Sw
- peripherals present a register map
- software reads/writes via MMIO(AXI-lite on SOC)
- In Linux, drivers map MMIO with interface `ioremap()` and use `readl/writel`
    - take that register model and convert it some thing which look like use it as files (dealing with files which have names which has hirearchy of directories/folder is easier in OS)
>> kernel vs user
- User Space: apps,limited privileges,uses syscalls
- kerneel space: OS core and drivers,full access
- Boundry: files,ioctl,mmap,sysfs,netlink...
- Design goal:safe and simple interfaces for users


>> Privileged operations
- Access MMIO
- Configure inturrupts
- control DMA/IOMMU
- Manage page table
- Power management

>> Note: power mgmt ,sleep mode CPU tells all the peripherls to kind of suspend themself going to mode that can recover from it , basically all the devices to ultra low power mode 

### Virtual Memory 
- Why
    - per process;stable view;connot see physical
    - processes should be isolated from each other, one process should not read or right the data corresponding to another process
    - multi- tasking, Security:if someone uses pointer and someone else should not be able to guess what physical memory that pointer it corresponds to (every pointer i use should be given a fake name ,and also OS will block access to portion of memory)
    - virtualization happens at runtime
- How 
    - Each process sees a virtual memory space - addresses that are different from other processes
    - OS Kernel translates virtual --> physical and back

- Each process sees its own virtual address space
- page tables translate virtual --> physical frames
- MMIO regions live in physical address space (not directly visible to apps)

```text

peripheral
physical:0x4000_0000
size:4KB
    |ioremap
    |
Kernel virtual Addr
void __iomem *base = ioremap(0x4000_0000X1000);
write(EN,base+CTRL_OFF);
u32 st = read(base+STATUS_OFF);
    |syscalls
    |
user Space
open("\dev\..")
read/write/octl
sysfs:/sys/class/

```


### Linux Device Model
- Devices(physical/virtual) attach to busses (platform,PCI,i2c...)
- Drivers bind to devices and expose interfaces(that can user space program can use to talk)
- common user-facing surfaces:
    - character devices under /dev/*(open/read/write/ioctl)
    - Sysfs attributes under /sys/*(text knobs,RO/RW)
    - debugfs for debugging , not for production




### Hardware Inturrupts

- processor runs faster than the peripherals some MHz.
- polling: CPU busy-waits in loops,good for very fast ops(<1mc), wastes power and cycles

```c
//the polling problem
//CPU is stuck in a loop,burning cycles
while(!(readl(STATUS) & DONE_BIT)){
    //can't do other work
    //wastes power
}
process_result();
```

- alternative to polling is Interrupts
- CPU does other work
- Event - driven (responsive)
- good for infrequent/slow events
- requires handler setup
>> The Inturrrupt solution:
  - CPU registers a handler(func) once: register in OS or inturrupt controller which has inturrupt table which tells if particular kind of inturrput occurs then go and call that particular func
  - Goes off to do other work
  - Hardware notifies CPU when event occurs
  - Handler runs, processes event , return


  >>NOTE: when to use what: fast operations:polling,slow/unpridictible:inturrupts,Infrequent events:inturrupts

### Types of Inturupt 

- `Level Triggered`: IRQ(signal) is asserted(could be keyboard,or any peripheral)  that causes inturrupt signal to go high until its explicitly cleared by the software(Handler acknolegde) its not gonna clear on its own, software has to acknoledge the fact that it saw the inturrupt this makes it safe ie, you cant miss an inturrupt, so most MMIO peripherals prefer to use Level triggered inturrupts.

```text
IRQ Signal
       ______________
______|              |_______
      ^              ^
    Assert          clear
    (event)         (sw Ack) 
```

- `Edge Triggered`: in this IRQ(signal basically comes as a pulse) the hardware basically looks for the transition, the pulse goes back down on its own , it does not wait for software acknoledgement,can miss if not handled fast(camera that ditects flash it captures, so lightning not gonna stay till u capture its edge triggered)

```text
IRQ signal
     __
____|  |____________
    ^
   Edge pulse
   (event) 
```

### ARM Generic Inturrupt Controller

- Route interrupts from many sources to cpu cores
    1. `Distributor(GICD):` Rec. all INT signals,handles priority/routing
    2. `CPU Interface(GICC):` One per core,delivers interrupts to cpu

- Interrupt Types:
    1.  SGI (0-15)  : sw-generated (inter-processor)
    2.  PPI(16-31)  : Per-CPU private(local timers)
    3.  SPI(32-1019): shared peripherals

```dts 

gic:inturrupt-controller@8000000{
    compatible = "arm,cortex-a9-gic"
    #inturrupt-cells = <3>;
    inturrupt-controller;
    reg = <0x8000000 0x1000>,<0x8001000 0x1000>;
};

smarttimer:smarttimer@70000000{
compatiblle = "acme,smartttimer-irq-v1";
reg = <0x70000000  0x1000>;
interrupts = <GIC_SPI 33 IRQ_TYPE_LEVEL_HIGH>;
inturrupt-parent =<&gic>;
};

```

