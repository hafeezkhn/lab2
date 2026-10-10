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
- 