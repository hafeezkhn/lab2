[![Next Section](https://img.shields.io/badge/<-Prev-2EA043?style=for-the-badge)](./001.md)

[Device_Nodes](#device_nodes), how to [create](#dynamic-allocation-of-major-numbers) them, [access](#аcсessing_the_device_node) them, and [register](#registering-the-device) them with the kernel, [methods of managing](#managing-device-nodes) device nodes

## Device_Nodes
- `Character and block devices have filesystem entries associated with them`.These nodes can be usedby user-level programs to communicate with the device.
  - device nodes are made with cmdline or or from the mknod() system call: 

    ```bash 
    mknod -m 666 /dev/mycdrv c 254 1 
    ```
# Major and Minor Numbers
- `The major and minor numbers identify the driver associated with the device`. Generally speaking,
all device nodes of the same type (block or character) with the same `major number` use the same
driver.
- The `minor number` is used only by the device driver to differentiate between the different devices
it may control.These may either be different instances of the same kind of device, (such as the first
and second sound card, or hard disk partition) or different modes of operation of a given device (such
as different density floppy drive media.)

- The major and minor numbers are stored together in a variable of type dev_t, which has 32 bits,
with 12 bits reserved for the major number, and 20 bits for the minor number.

- The internal bit layout is complicated for historical reasons, and one is not guaranteed that it will
not change in future kernel versions. Thus one should always use the following macros to construct
(or deconstruct) major and minor numbers from a dev_t structure:

    ```C
   MAJOR(dev_t dev);
   MINOR(dev_t dev);
   MKDEV(int major, int minor);
   unsigned iminor (struct inode *inode); /* = MINOR(inode->i_rdev) */
   unsigned imajor(struct inode *inode); /* = MAJOR(inode->i_rdev) */
    ```
- A list of the major and minor numbers pre-associated with devices can be found in/usr/src/linux /Documentation/devices.txt. (Note the major numbers 42, 120-127 and 240-254 are reserved
for local and experimental use.)

- Symbolic names for assigned major numbers can be found in
/usr/src/linux/include/linux/major.h. Requesting further device number reservations is probably prohibited, as more modern methods use dynamical allocation.
```bash
$stat vmlinuz-2.6.26-rc5
File: 'vmlinuz-2.6.26-rc5
Size: 2849808 Blocks: 5592
Device: 805h/2053d Inode: 22090
Access: (0644/-rw-r--r-) Uid: ( 0/
Access: 2008-06-07 13:20:51.000000000-0500
Modify: 2008-06-07 13:20:51.000000000-0500
Change: 2008-06-07 13:20:51.000000000-0500
10 Block: 1024 regular file
Links:
root) Gid: ( 0/ root)
```
shows the file resides on the disk partition with major number 8 and minor number 5 (/dev/sda5),
which is listed at 805h (hexadecimal) or 2053d (decimal).

- Adding a new driver to the system (i.e., registering it) means assigning a major number to it.
 ```C
//usually during the device's initialization routine. For a character driver one calls:
#include <linux/fs.h>
int register_chrdev_region (dev_t first, unsigned int count, char *name);
```
- where first is the first device number being requested, of a range of count contiguous numbers;
usually the minor number part of first would be 0, but that is not required.
- name is the device name, as it will appear when examining/proc/devices. Note it is not the same
as the node name in /dev that your driver will use. (The kernel decides which driver to invoke based
on the major/minor number combination, not the name.)
- A return value of 0 indicates success; negative values indicate failure and the requested region of device
numbers will not be available. Note that mknod will still have to be run to create the appropriate
device node(s).
```C 
// It is important when undoing the registration to remove the association with device numbers, once they are no longer needed. This is most often done in the device cleanup function with:
#include <linux/fs.h>
void unregister_chrdev_region (dev_t first, unsigned int count);
//Note that this will not remove the node itself.If you fail to unregister a device, you'll get a segmentation fault the next time you do cat /proc/devices. It is pretty hard (although not impossiblc) to recover from this kind of error without a system reboot.
```
### Dynamic Allocation of Major Numbers
- Choosing a unique major number may be difficult: dynamic allocation of the device numbers is the
proper method for all new drivers and can be used to avoid collisions. This is accomplished with the
function:
```C 
#include <linux/fs.h>
int alloc_chrdev_region (dev_t *first, unsigned int firstminor, unsigned int count,
char *name);
```
- where first is now passed by address as it will be filled in by the function. The new argument,
firstminor is obviously the first requested minor number, (usually 0.) The de-registration of the device numbers is the same with this method.

- The disadvantage of dynamic allocation is that the proper node can not be made until the driver is
loaded. Furthermore, onc usually needs to remove the node upon unloading of the driver module.

## Аcсessing_the_Device_Node
- with the everything is a file
philosophy. For example, listening to a sound would involve reading from the device node associated
with the sound card (generally /dev/audio).
- There are a limited number of entry points into device drivers, and in most cases there is a one
to one mapping of the system calls applications make and the entry point in the driver which is
exercised when the call is made.
- The following are the main operations that can be performed on character device nodes by programs
in user-space:
```C
int close (int fd);
int open (const char *pathname, int flags);
ssize_t read (int fd, void *buf, size_t count);
ssize_t write (int fd, const void *buf, size_t count);
int ioctl (int fd, int request, ...);
off_t lseek (int fd, off_t offset, int whence);
void *mmap (void *start, size_t length, int prot, int flags, int fd, off_t offset);
int poll (struct pollfd *fds, nfds_t nfds, int timeout);
```
The device driver has entry points corresponding to these functions; however names and arguments
may differ. In the above list, for example, the system call close() will lead to the entry point
release().

## Registering the Device
- So far all we have done is reserve a range of device numbers for the exclusive use of our driver. still work to be done before device can be used.
- Character devices are associated with a cdev structure, as defined in /usr/src/linux/include /linux/cdev.h:
```C
struct cdev {
struct kobject kobj;
struct module *owner;
struct file_operations *ops;
struct list_head list;
dev_t dev;
unsigned int count;
};
```
- Normally you won't work directly with the internals of this structure, but reach it through various
utility functions.
- In particular we want to know how the owner and ops pointers are used.
```C
//A number of related functions which are needed to work with character devices are:
#include <linux/cdev.h>
struct cdev *cdev_alloc (void);
void cdev_init (struct cdev *p, struct file_operations *fops);
void cdev_put (struct cdev *p);
struct kobject *cdev_get (struct cdev *p);
int cdev_add (struct cdev *p, dev_t first, unsigned count);
void cdev_del (struct cdev *p);

```
- These structures should always be allocated dynamically, and then initialized with code like:
```C
    struct cdev *mycdev = cdev_alloс ();
    cdev_init (mycdev, &fops);
    /*This code allocates memory for the structure, initializes it, and sets the owner and ops fields to point to the current module, and the proper file_operations table.*/
    //The driver will go live when one calls:
    cdev_add (mycdev, first, count);
    //This function should not be called until the driver is ready to handle anything that comes its way.The inverse function is
    cdev_del (mycdev)
    //and after this is called the device is removed from the system and the cdev structure should never be accessed after this point.
```
### managing device nodes 
- The methods of managing device nodes became clumsy and difficult as Linux evolved. 
- Ideally, one would like to register devices by name, However, major and minor numbers can not be
gotten rid of altogether, as Posix requires them.
The `udev method` creates device nodes on the fly as they are needed. There is no need to maintain
a ton of device nodes that will never be used. The u in udev stands for user, and indicates that
most of the work of creating, removing, and modifying devices nodes is done in user-space.
- udev handles the dynamical generation of device nodes but it does not handle the discovery
management of them. This requires the Hardware Abstraction Layer, or HAL,
- AL uses the D-BUS (device bus) infrastructure, as provided by the HAL daemon (haldaemon).
It maintains a dynamic database of all connected hardware devices and is closely coupled to the
hotplug facility. The command 1shal will dump out all the information that HAL currently has
in its database. There are a number of configuration files on the system (in /usr/share/hal and /etc/hal) which control behaviour and set exceptions.

- The main configuration file is /etc/udev/udev.conf. It contains information such as where to place
device nodes, default permissions and ownership etc. By default rules for device naming are located
in the etc/udev/rules.d directory. By reading the man page for udev one can get a lot of specific information about how to set up rules for common situations.
- Creation and removal of a device node dynamically, from within the driver using udev, is done by
the use of the following functions defined in /usr/src/linux/include/linux/device.h:

```c
#include <linux/device.h>
struct class *class_create (struct module *owner, const char *name);
struct device *device_create (struct class *cls, struct device *parent, dev_t devt,
const char *fmt,...);
void device_destroy (struct class *cls, dev_t dev):
void class_destroy (struct class *cls);
/*Generally, the parent is NULL which means the class is created at the top level of the hierarchy. A
code fragment serves to show the use of these functions:*/
static struct class *foo_class;
/* create node in the init function */
/*
foo_class class_create (THIS_MODULE, "my_class");
device_create (foo_class, NULL, first, "%s%d", "mycdrv", 1);
remove node in the exit function */
device_destroy (foo_class,first);
class_destroy (foo_class);
```

>> The file_operations structure is defined in /usr/src/linux/include/linux/fs.h,struct file_operations {


