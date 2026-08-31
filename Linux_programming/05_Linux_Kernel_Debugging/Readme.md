### оops Messages
- oops messages indicate that a fault occurred in kernel mode. Depending on the nature of the fault
that produced the oops, the fault may be fatal, serious, or inconsequential.
- If the oops occurs in process context the kernel will attempt to back out of the current task, probably
killing it. If it occurs in interrupt context the kernel can't do this and will crash, as it will if it occurs
in either the idle task (pid=0) or init (pid=1).
