> Q. What are ioctls?
- ioctl's (input output control) are special functions which are unique to a device or class of device.
ioctl() is both a call from user-space, as well as a driver entry point (i.e., like write(), read(), etc.)
- Various commands can be implemented which either send to or receive information from a device.
One can control device driver behaviour; i.e, shutdown, reset and modify. One can send out-of-band
messages even while reads and writes are pending
- To use ioctl's, one has to first open a device using the open() system call, and then send the
appropriate ioctl() command and any necessary arguments.
```c
#include <sys/ioctl.h>
int ioctl(int fd, int command,...);
```
- The third argument is usually written as char *argp. The use of the dots usually means a variable
number of arguments. Here it indicates that type checking should not be done on the argument, so
we are utilizing a trick. You shouldn't pass more than threc arguments to the ioctl() call.
```c
// Example:
int fd= open ("/dev/mydrvr", O_RDWR);
if (ioctl( fd, MYDRVR SET, buf) < 0(
perror( "MYDRVR_SET ioctl failed" );
```

- Driver Entry point for ioctls
The entry point for ioctl() looks like:
```C
#include <linux/ioctl.h> 
static int mydrvr_ioctl (struct inode *inode, struct file *file, unsigned int cmd,
unsigned long arg);
```
- where arg can be uscd directly cither as a long or a pointer in user-space. In the latter case,
the proper way to is though the put_user(), get_user(), copy_to_user(), copy_from_user() functions.

```C
//Example:
static int mydrvr_ioctl (struct inode *inode, struct file *file, unsigned int cmd,
unsigned long arg) {
if (_IOC_TYPE (cmd) != MYDRBASE)
return (-EINVAL);
switch (cmd){
case MYDRVR_RESET
/* do something */
return 0;
case MYDRVR_OFFLINE
/* do something */
return 0;
case MYDRVR_GETSTATE :
if (copy_to_user ((void *)arg, &mydrvr_state_struct, sizeof(mydrvr_state_struct)))
return -EFAULT;
return 0;
default:
return -EINVAL;
 }
}
```
- Defining ioctls
    - Before using ioctl() one must choose the numbers corresponding to the integer command argument.
Just picking arbitrary numbers is a bad idea; they should be unique across the system.
    - There are at least two ways errors could arise:Two device nodes may have the same major number.
An application could make a mistake, opening more than one device and mixing up the file
descriptors, thereby sending the right command to the wrong device.
Results might be catastrophic and even damage hardware.


