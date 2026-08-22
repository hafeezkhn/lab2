> Hardware support is offered by the drivers 
> Drivers operate in kernel space , users connot access kernel space thats why device nodes are coming in.
> many devices only send bytes to peripharal on the computer , or recive bytes from the peripheral, such devices work as pipes for that reason,  they work well as charechter devices these are stream of devices 

> network devices are bit more complex as they work with packets instead of streams of bytes, these devices are controlled by `ioctl()` system call, which permits for more advanced operations, and for that reason dont find any network device in /dev directory 
> 