# Memory_Management

## Memory Addresses: 
- memory address as the way to access the contents of
a memory cell. But when dealing with 80 × 86 microprocessors, we have to distinguish three kinds of addresses:
   - `Physical address` Used to address memory cells in memory chips. They correspond to the electrical signals sent along the address pins of the microprocessor to the memory bus. Physical addresses are represented as 32-bit or 36-bit unsigned integers.
   - `Linear address` (also known as virtual address) A single 32-bit unsigned integer that can be used to address up to 4 GB—that is, up to 4,294,967,296 memory cells. Linear addresses are usually represented in hexadecimal notation; their values range from 0x00000000 to 0xffffffff.
   - `Logical address`: Included in the machine language instructions to specify the address of an operand or of an instruction. This type of address embodies the well-known 80 × 86 segmented architecture that forces MS-DOS and Windows programmers to divide their programs into segments. Each logical address consists of a segment and an offset (or displacement) that denotes the distance from the start of the segment to the actual address.

   `The Memory Management Unit (MMU) transforms a logical address into a linear address by means of a hardware circuit called a segmentation unit; subsequently, a second hardware circuit called a paging unit transforms the linear address into a physical address`

   - In multiprocessor systems, all CPUs usually share the same memory;
   - this means that RAM chips may be accessed concurrently by independent CPUs Because read or
write operations on a RAM chip must be performed serially, a hardware circuit called
a memory arbiter is inserted between the bus and every RAM chip. Its role is to grant
access to a CPU if the chip is free and to delay it if the chip is busy servicing a request
by another processor
- Even uniprocessor systems use memory arbiters, because they
include specialized processors called DMA controllers that operate concurrently with
the CPU ,In the case
of multiprocessor systems, the structure of the arbiter is more complex because it has
more input ports. The dual Pentium, for instance, maintains a two-port arbiter at
each chip entrance and requires that the two CPUs exchange synchronization messages before attempting to use the common bus. From the programming point of
view, the arbiter is hidden because it is managed by hardware circuits.

### Segmentation in Hardware
- Starting with the 80286 model, Intel microprocessors perform address translation in
two different ways called real mode and protected mode. We’ll focus in the next sections on address translation when protected mode is enabled. Real mode exists
mostly to maintain processor compatibility with older models and to allow the operating system to bootstrap
### Segment Selectors and Segmentation Registers
- A logical address consists of two parts: a segment identifier and an offset that specifies the relative address within the segment.
-  The segment identifier is a 16-bit field
called the Segment Selector (see Figure 2-2), while the offset is a 32-bit field. We’ll
describe the fields of Segment Selectors in the section “Fast Access to Segment
Descriptors
- To make it easy to retrieve segment selectors quickly, the processor provides segmentation registers whose only purpose is to hold Segment Selectors;
- these registers are
called cs, ss, ds, es, fs, and gs. Although there are only six of them, a program can
reuse the same segmentation register for different purposes by saving its content in
memory and then restoring it later.

- Segment Descriptors
Each segment is represented by an 8-byte Segment Descriptor that describes the segment characteristics. Segment Descriptors are stored either in the Global Descriptor
Table (GDT) or in the Local Descriptor Table (LDT).
Usually only one GDT is defined, while each process is permitted to have its own LDT if
it needs to create additional segments besides those stored in the GDT. The address and
size of the GDT in main memory are contained in the gdtr control register, while the
address and size of the currently used LDT are contained in the ldtr control register.

- There are several types of segments, and thus several types of Segment Descriptors.
The following list shows the types that are widely used in Linux.
   - Code Segment Descriptor
Indicates that the Segment Descriptor refers to a code segment; it may be
included either in the GDT or in the LDT. The descriptor has the S flag set (nonsystem segment).
   - Data Segment Descriptor
Indicates that the Segment Descriptor refers to a data segment; it may be
included either in the GDT or in the LDT. The descriptor has the S flag set.
Stack segments are implemented by means of generic data segments.
   - Task State Segment Descriptor (TSSD)
Indicates that the Segment Descriptor refers to a Task State Segment (TSS)—
that is, a segment used to save the contents of the processor registers (see the
section “Task State Segment” in Chapter 3); it can appear only in the GDT. The
corresponding Type field has the value 11 or 9, depending on whether the corresponding process is currently executing on a CPU. The S flag of such descriptors
is set to 0.

### Paging in Hardware:
- The paging unit translates linear addresses into physical ones. 
-  One key task in the
unit is to check the requested access type against the access rights of the linear
address.
-  If the memory access is not valid, it generates a Page Fault exception 
- For the sake of efficiency, linear addresses are grouped in fixed-length intervals called
pages
- contiguous linear addresses within a page are mapped into contiguous physical addresses. In this way, the kernel can specify the physical address and the access
rights of a page instead of those of all the linear addresses included in it
- The paging unit thinks of all RAM as partitioned into fixed-length page frames
(sometimes referred to as physical pages). Each page frame contains a page—that is,
the length of a page frame coincides with that of a page. 
-  A page frame is a constituent of main memory, and hence it is a storage area. It is important to distinguish a
page from a page frame; the former is just a block of data, which may be stored in
any page frame or on disk.
- The data structures that map linear to physical addresses are called page tables; they
are stored in main memory and must be properly initialized by the kernel before
enabling the paging unit.
- The translation of linear addresses is accomplished in two steps, each based on a
type of translation table. The first translation table is called the Page Directory, and
the second is called the Page Table.
- The aim of this two-level scheme is to reduce the amount of RAM required for perprocess Page Tables. If a simple one-level Page Table was used, then it would require
- up to 220 entries (i.e., at 4 bytes per entry, 4 MB of RAM) to represent the Page Table
for each process (if the process used a full 4 GB linear address space), even though a
process does not use all addresses in that range. The two-level scheme reduces the
memory by requiring Page Tables only for those virtual memory regions actually
used by a process.
- Each active process must have a Page Directory assigned to it. However, there is no
need to allocate RAM for all Page Tables of a process at once; it is more efficient to
allocate RAM for a Page Table only when the process effectively needs it.

- `Hardware cache memories` were introduced to reduce the speed mismatch between
CPU and RAM. 

- `Translation Lookaside Buffers (TLB)`
Besides general-purpose hardware caches, 80 × 86 processors include another cache
called Translation Lookaside Buffers (TLB) to speed up linear address translation.
When a linear address is used for the first time, the corresponding physical address is
computed through slow accesses to the Page Tables in RAM. The physical address is
then stored in a TLB entry so that further references to the same linear address can
be quickly translated.
In a multiprocessor system, each CPU has its own TLB, called the local TLB of the
CPU. Contrary to the hardware cache, the corresponding entries of the TLB need not
be synchronized, because processes running on the existing CPUs may associate the
same linear address with different physical ones.
When the cr3 control register of a CPU is modified, the hardware automatically
invalidates all entries of the local TLB, because a new set of page tables is in use and
the TLBs are pointing to old data.

### Virtual Process memory: