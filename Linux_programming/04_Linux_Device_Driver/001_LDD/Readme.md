Privalge levels

KERNEL VS USER SPACE

Constructor distructor - insmod/rmmod

kernel log buffer -dmesg


   read1     read2         (userspace)
-----\---------/------------------------
        ldd                (kernelspace)



VFS /proc not stored just an listing , 
https://elixir.bootlin.com/linux/v6.8/source/include/linux/proc_fs.h#L29  --> proc_fs.h

o/p:
>> insmod ldd.ko
>> cat /proc/ldd_1
>> rmmod ldd

>> insmod ldd.ko
>> python ./user_app.py
