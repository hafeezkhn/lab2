`Kernel Synchronization`  You could think of the kernel as a server that answers requests; these requests can
come either from a process running on a CPU or an external device issuing an
interrupt request.We make this analogy to underscore that parts of the kernel are
not run serially, but in an interleaved way. Thus, they can give rise to race
conditions, which must be controlled through proper synchronization techniques.

`How the Kernel Services Requests`:
To get a better grasp of how kernel's code is executed, we will look at the kernel as
a waiter who must satisfy two types of requests: those issued by customers and
those issued by a limited number of different bosses. The policy adopted by the
waiter is the following:
1. If a boss calls while the waiter is idle, the waiter starts servicing the boss.
2. If a boss calls while the waiter is servicing a customer, the waiter stops
servicing the customer and starts servicing the boss.
3. If a boss calls while the waiter is servicing another boss, the waiter stops
servicing the first boss and starts servicing the second one. When he finishes
servicing the new boss, he resumes servicing the former one.
4. One of the bosses may induce the waiter to leave the customer being
currently serviced. After servicing the last request of the bosses, the waiter
may decide to drop temporarily his customer and to pick up a new one.
The services performed by the waiter correspond to the code executed when the
CPU is in Kernel Mode. If the CPU is executing in User Mode, the waiter is
considered idle.
Boss requests correspond to interrupts, while customer requests correspond to
system calls or exceptions raised by User Mode processes

- User Mode processes that want to request a service from the kernel
must issue an appropriate instruction >> Such instructions raise an exception that forces the CPU to switch
from User Mode to Kernel Mode. 

` kernel preemption`:
- Both in preemptive and nonpreemptive kernels, a process running in Kernel
Mode can voluntarily relinquish the CPU, for instance because it has to sleep
waiting for some resource. We will call this kind of process switch a `planned process switch`. However, a preemptive kernel differs from a nonpreemptive
kernel on the way a process running in Kernel Mode reacts to asynchronous
events that could induce a process switch—for instance, an interrupt handler
that awakes a higher priority process. We will call this kind of process switch a
`forced process switch`.
- All process switches are performed by the switch_to macro. In both
preemptive and nonpreemptive kernels, a process switch occurs when a process
has finished some thread of kernel activity and the scheduler is invoked.
However, in nonpreemptive kernels, the current process cannot be replaced
unless it is about to switch to User Mode
- Therefore, the main characteristic of a preemptive kernel is that a process running
in Kernel Mode can be replaced by another process while in the middle of a kernel
function
> Example:  While process A executes an exception handler (necessarily in Kernel Mode), a
higher priority process B becomes runnable. This could happen, for instance, if an
IRQ occurs and the corresponding handler awakens process B. If the kernel is
preemptive, a forced process switch replaces process A with B. The exception
handler is left unfinished and will be resumed only when the scheduler selects
again process A for execution. Conversely, if the kernel is nonpreemptive, no
process switch occurs until process A either finishes handling the exception handler
or voluntarily relinquishes the CPU.

- The main motivation for making a kernel preemptive is to reduce the dispatch
latency of the User Mode processes, that is, the delay between the time they
become runnable and the time they actually begin running. Processes performing
timely scheduled tasks (such as external hardware controllers, environmental
monitors, movie players, and so on) really benefit from kernel preemption, because
it reduces the risk of being delayed by another process running in Kernel Mode.

-  `Syncronization is necessary`: concepts of race condition and critical region for
processes. The same definitions apply to kernel control paths.
- a
race condition can occur when the outcome of a computation depends on how two
or more interleaved kernel control paths are nested. A critical region is a section of
code that must be completely executed by the kernel control path that enters it
before another kernel control path can enter it.
- `Sync not necessary`:Interrupt handlers and tasklets need not to be coded as reentrant functions.
Per-CPU variables accessed by softirqs and tasklets only do not require
synchronization.
A data structure accessed by only one kind of tasklet does not require
synchronization.

- In user-space, the need for synchronization stems from the fact that programs are scheduled preemptively at the will of the scheduler. Because a process can be preempted at any
time and another process can be scheduled onto the processor, a process can be involuntarily preempted in the middle of accessing a critical region

- concurrency—in
which two things do not actually happen at the same time but interleave with each other
such that they might as well—is called pseudo-concurrency.
If you have a symmetrical multiprocessing machine, two processes can actually be executed in a critical region at the exact same time.That is called true concurrency

- .Although
the causes and semantics of true versus pseudo concurrency are different, they both result
in the same race conditions and require the same sort of protection.
The kernel has similar causes of concurrency:
   - Interrupts— An interrupt can occur asynchronously at almost any time, interrupting the currently executing code. 
   - Softirqs and tasklets— The kernel can raise or schedule a softirq or tasklet at almost any time, interrupting the currently executing code.
   - Kernel preemption— Because the kernel is preemptive, one task in the kernel
can preempt another.
   - Sleeping and synchronization with user-space— A task in the kernel can
sleep and thus invoke the scheduler, resulting in the running of a new process.
   - Symmetrical multiprocessing— Two or more processors can execute kernel
code at exactly the same time.

### types of synchronization techniques used by the kernel
| Technique | Description | Scope |
|---|---|---|
| **Per-CPU variables** | Duplicate a data structure among the CPUs | All CPUs |
| **Atomic operation** | Atomic read-modify-write instruction to a counter | All CPUs |
| **Memory barrier** | Avoid instruction reordering | Local CPU or All CPUs |
| **Spin lock** | Lock with busy wait | All CPUs |
| **Semaphore** | Lock with blocking wait (sleep) | All CPUs |
| **Seqlocks** | Lock based on an access counter | All CPUs |
| **Local interrupt disabling** | Forbid interrupt handling on a single CPU | Local CPU |
| **Local softirq disabling** | Forbid deferrable function handling on a single CPU | Local CPU |
| **Read-copy-update (RCU)** | Lock-free access to shared data structures through pointers | All CPUs |

- The simplest and most efficient synchronization technique consists of declaring
kernel variables as per-CPU variables . Basically, a per-CPU variable is an array of
data structures, one element per each CPU in the system.
A CPU should not access the elements of the array corresponding to the other
CPUs; on the other hand, it can freely read and modify its own element without
fear of race conditions, because it is the only CPU entitled to do so. This also
means, however, that the per-CPU variables can be used only in particular cases—
basically, when it makes sense to logically split the data across the CPUs of the
system.
- While per-CPU variables provide protection against concurrent accesses from
several CPUs, they do not provide protection against accesses from asynchronous
functions (interrupt handlers and deferrable functions). In these cases, additional
synchronization primitives are required.
Furthermore, per-CPU variables are prone to race conditions caused by kernel
preemption , both in uniprocessor and multiprocessor systems. As a general rule, a
kernel control path should access a per-CPU variable with kernel preemption
disabled. Just consider, for instance, what would happen if a kernel control path
gets the address of its local copy of a per-CPU variable, and then it is preempted
and moved to another CPU: the address still refers to the element of the previous
CPU



`Process Communication` how User Mode processes can synchronize their actions and exchange data ?
## Pipes and FIFOs (named pipes):
- Best suited to implement producer/consumer interactions among processes. Some processes fill the pipe with data, while others extract data from the pipe
- Pipes are an interprocess communication mechanism that is provided in all flavors
of Unix. A pipe is a one-way flow of data between processes: all data written by a
process to the pipe is routed by the kernel to another process, which can thus read
it.
- Pipes may be considered open files that have no corresponding image in the
mounted filesystems.
- A process creates a new pipe by means of the pipe( )
system call, which returns a pair of file descriptors ; the process may then pass
these descriptors to its descendants through fork( ) , thus sharing the pipe with
them. 
- The processes can read from the pipe by using the read( ) system call with
the first file descriptor; likewise, they can write into the pipe by using the write(
) system call with the second file descriptor.
- POSIX defines only half-duplex pipes , so even though the pipe( ) system call returns two file descriptors, each process must close one before using the other. If a
two-way flow of data is required, the processes must use two different pipes by
invoking pipe( ) twice.

- Once a pipe is created,
a process uses the read( ) and write( ) VFS system calls to access it.
Therefore, for each pipe, the kernel creates an inode object plus two file objects—
one for reading and the other for writing. When a process wants to read from or
write to the pipe, it must use the proper file descriptor.

- Besides one inode and two file objects, each pipe has its own set of pipe buffers .
Essentially, a pipe buffer is a page frame that contains data written into the pipe
and yet to be read. 
- A pipe is implemented as a set of VFS objects, which have no corresponding disk
images. In Linux 2.6, these VFS objects are organized into the pipefs special
filesystem to expedite their handling
- . Because this filesystem has no mount point in the system directory
tree, users never see it. However, thanks to pipefs, the pipes are fully integrated in
the VFS layer, and the kernel can handle them in the same way as named pipes or
FIFOs, which truly exist as files recognizable to end users 

- `FIFOs`
Although pipes are a simple, flexible, and efficient communication mechanism,
they have one main drawback—namely, that there is no way to open an already
existing pipe,This makes it impossible for two arbitrary processes to share the
same pipe, unless the pipe was created by a common ancestor process.
- Each FIFO is much like a pipe:
rather than owning disk blocks in the filesystems, an opened FIFO is associated
with a kernel buffer that temporarily stores the data exchanged by two or more
processes
- Thanks to the disk inode, however, a FIFO can be accessed by every process,
because the FIFO filename is included in the system's directory tree

-  there are only two significant differences
    -  FIFO inodes appear on the system directory tree rather than on the pipefs
special filesystem.
    - FIFOs are a bidirectional communication channel; that is, it is possible to open
a FIFO in read/write mode.

## IPC Semaphores
- IPC semaphores are quite similar to the kernel semaphores , they are counters used to provide controlled access to shared data structures for
multiple processes.

- The semaphore value is positive if the protected resource is available, and 0 if the
protected resource is currently not available

- A process that wants to access the
resource tries to decrease the semaphore value; the kernel, however, blocks the
process until the operation on the semaphore yields a positive value. 

- When a
process relinquishes a protected resource, it increases its semaphore value; in doing
so, any other process waiting for the semaphore is woken up.


## IPC Messages
- Allow processes to exchange messages (short blocks of data) by reading and writing them in predefined message queues.
- Processes can communicate with one another by means of IPC messages . Each
message generated by a process is sent to an IPC message queue, where it stays
until another process reads it.
- A message is composed of a fixed-size header and a variable-length text; it can be
labeled with an integer value (the message type), which allows a process to
selectively retrieve messages from its message queue.
[*] Once a process has read a
message from an IPC message queue,`the kernel destroys the message; therefore,only one process can receive a given message`.


## IPC Shared memory regions
- Allow processes to exchange information via a shared block of memory. In
applications that must share large amounts of data, this can be the most
efficient form of process communication. 
- The most useful IPC mechanism is shared memory , which allows two or more
processes to access some common data structures by placing them in an IPC
shared memory region. Each process that wants to access the data structures
included in an IPC shared memory region must add to its address space a new
memory region which maps the
page frames associated with the IPC shared memory region. Such page frames can
then be easily handled by the kernel through demand paging 

- 

## Sockets
- Allow processes on different computers to exchange data through a network. Sockets can also be used as a communication tool for processes located on the same host computer;