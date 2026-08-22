# The Virtual Filesystem
-  Virtual Filesystem : is the subsystem of the kernel that implements the file and filesystem-related
interfaces provided to user-space programs.All filesystems rely on the VFS to enable them
not only to coexist, but also to interoperate

- The VFS is the glue that enables system calls such as open(), read(), and write()to
work regardless of the filesystem or underlying physical medium
- To support various native filesystems and, at the same time, to allow access to files of other operating systems, the Linux kernel includes a layer between user processes (or the standard library)
and the filesystem implementation. This layer is known as the Virtual File System.

Filesystems may be grouped into three general classes:
1. `Disk-based filesystems` are the classic way of storing files on nonvolatile media to retain
their contents between sessions. In fact, most filesystems have evolved from this category.
Some well-known examples are Ext2/3, Reiserfs, FAT, and iso9660. All make use of blockoriented media and must therefore answer the question, how to store file contents and structure information on the directory hierarchies. Of no interest to us here is the way in which
communication takes place with the underlying block device — the corresponding device
drivers in the kernel provide a uniform interface for this purpose. From the filesystem point
of view, the underlying devices are nothing more than a list of storage blocks for which an
appropriate organization scheme must be adopted.
2. `Virtual filesystems` are generated in the kernel itself and are a simple way of enabling
userspace programs to communicate with users. The proc filesystem is the best example of
this class. It requires no storage space on any kind of hardware device; instead, the kernel
creates a hierarchical file structure whose entries contain information on a particular part
of the system. The file /proc/version, for example, has a nominal length of 0 bytes when
viewed with the ls command.
wolfgang@meitner> ls -l /proc/version
-r--r--r-- 1 root root 0 May 27 00:36 /proc/version
However, if the file contents are output with cat, the kernel generates a list of information on the system processor; this list is extracted from the data structures in kernel
memory.
wolfgang@meitner> cat /proc/version
Linux version 2.6.24 (wolfgang@schroedinger) (gcc version 4.2.1 (SUSE Linux))
#1 Tue Jan 29 03:58:03 GMT 2008
3. `Network filesystems` are a Halfway House between disk-based and virtual filesystems. They
permit access to data on a computer attached to the local computer via a network. In this
case, the data are, in fact, stored on a hardware device on a different system. This means
that the kernel need not be concerned with the details of file access, data organization, and
hardware communication — this is taken care of by the kernel of the remote computer. All
operations on files in this filesystem are carried out over a network connection. When a process writes data to a file, the data are sent to the remote computer using a specific protocol

4. `Special filesystems`
These do not manage disk space, either locally or remotely. The /proc
filesystem is a typical example of a special filesystem. While network and disk-based filesystems enable the user to handle information
stored outside the kernel, special filesystems may provide an easy way for system
programs and administrators to manipulate the data structures of the kernel and to
implement special features of the operating system. like, shm,pipefs,rootfs,sockfs,sysfs,bdev,mqueue...

- The Virtual Filesystem (also known as Virtual Filesystem Switch or VFS) is a
kernel software layer that handles all system calls related to a standard Unix
filesystem. Its main strength is providing a common interface to several kinds of
filesystems.
