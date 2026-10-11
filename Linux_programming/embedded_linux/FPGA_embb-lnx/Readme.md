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

                             /[peripheral 0X40000]
|CPU| - {interconnect[Axi]}  -[peripheral 0X40001]
                             \[peripheral .......]

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

    


     






